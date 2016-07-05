#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aiprotocol.h"

struct protocol_contex pc;

int frame_build(cmd_t cmd,
		u8 argc,
		u8 *argv,
		OUT struct frame_info *frame)
{
	frame->head = FRAME_HEAD;

	frame->cmd = cmd;
	int i;
	for (i = 0; i < argc; i++) {
		if (argv == NULL) 
			return FAIL;
		frame->argv[i] = argv[i];
	}
	frame->argc = argc;
	frame->tail = FRAME_TAIL;

	return SUCCESS;
}

int cmd_array_init(cmd_t cmd, u8 argc, u8 *argv)
{
	pc.argc = argc;
	pc.argv = argv;
	pc.cmd = cmd;
	return SUCCESS;
}

int protocol_init(int fd,
		int (*open)(u8 *dev, int baudrate),
		int (*read)(int fd, void *buf, int size),
		int (*write)(int fd, void *buf, int size),
		int (*close)(int fd))
{
	int i;
	for (i = 0; i < CMD_NUM; i++) {
		pc.func[i] = NULL;
	}
	
	pc.fd = fd;
	pc.open = open;
	pc.send = write;
	pc.recv = read;
	pc.close = close;

	return SUCCESS;
}

int cb_reg(cb user_func, int cmd)
{
	if ((user_func == NULL) && (cmd >= CMD_NUM))
		return ERROR;

	pc.func[cmd] = user_func;

	return SUCCESS;
}

int cmd_send(cmd_t cmd, u8 argc, u8 *argv)
{
	int ret;
	struct frame_info frame;
	memset(&frame, 0, sizeof(struct frame_info));

	cmd_array_init(cmd, argc, argv);

	ret = frame_build(cmd, argc, argv, &frame);
	if (ret == FAIL)
		return FAIL;

	/*frame send*/
	ret = pc.send(pc.fd, &frame, sizeof(struct frame_info));
	if (ret <= 0) {
		printf("%s %s %d: SEND ERROR\n", __FILE__, __func__, __LINE__);
		return ERROR;
	}

	if ((frame.cmd < CMD_NUM)
		&& (frame.head == FRAME_HEAD)
		&& (frame.tail == FRAME_TAIL)) {
		/*callback user's function*/
		if (pc.func[frame.cmd] != NULL) {
			pc.func[frame.cmd](pc.argc, pc.argv);
		}
	}
	return SUCCESS;
}

int _parse_recv(struct frame_info *frame)
{
	if ((frame->head == FRAME_HEAD) &&
		(frame->tail == FRAME_TAIL) &&
		(frame->cmd <= CMD_NUM)) {
		if (pc.func[frame->cmd] != NULL)
			pc.func[frame->cmd](frame->argc, frame->argv);
	}

	return frame->cmd;
}

int cmd_recv()
{
	int count;
	count = pc.recv(pc.fd, pc.recv_buf, sizeof(struct frame_info));
	if (count != sizeof(struct frame_info)) {
		return ERROR;
	}

	struct frame_info frame_cp;
	memcpy(&frame_cp, pc.recv_buf, sizeof(struct frame_info));
	
	if ((frame_cp.head == FRAME_HEAD) &&
		(frame_cp.tail == FRAME_TAIL) &&
		(frame_cp.cmd <= CMD_NUM)) {
		if (pc.func[frame_cp.cmd] != NULL)
			pc.func[frame_cp.cmd](frame_cp.argc, frame_cp.argv);
	}

	return frame_cp.cmd;
}

int protocol_close()
{
	pc.close(pc.fd);
	return 0;
}

int protocol_export_fd()
{
	return pc.fd;
}
