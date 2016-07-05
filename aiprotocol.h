#include "var.h"

#define FRAME_HEAD (u8)0x3f
#define FRAME_TAIL (u8)0xbf
#define RECV_MAX_BUFFER 2048

typedef int (*cb)(u8 argc, u8 argv[USER_ARGC]);
#define cmd_t int

#pragma pack(1)
struct frame_info {
	u8 head;
	u8 cmd;
	u8 argc;
	u8 argv[USER_ARGC];
	u8 tail;
};
#pragma pack()

enum {
	VERSION_CHECK = 30,
	VERSION_SHOW = 31,
	ERROR = (char)-1,
	FAIL = (char)-2,
	SUCCESS = (char)0,
	WAKEUP_END = (char)-3,
	ASR_END = (char)-4
};

struct protocol_contex {
	int fd;
	cmd_t cmd;
	u8 argc;
	u8 *argv;
	u8 recv_salt;
	u8 sent_salt;
	cmd_t last_sent;
	int (*open)(unsigned char *dev, int baudrate);
	int (*send)(int fd, void *buff, int size);
	int (*recv)(int fd, void *buff, int size);
	int (*close)(int fd);

	u8 recv_buf[RECV_MAX_BUFFER];
	cb func[CMD_NUM];
};

int cmd_send(cmd_t cmd, u8 argc, u8 *argv);
int cmd_recv();
int cb_reg(cb user_func, cmd_t cmd);
int protocol_init(int fd,
		int (*open)(u8 *dev, int baudrate),
		int (*read)(int fd, void *buf, int size),
		int (*write)(int fd, void *buf, int size),
		int (*close)(int fd));
int protocol_close();
int protocol_export_fd();
