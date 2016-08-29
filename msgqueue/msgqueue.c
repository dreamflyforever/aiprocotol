#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#include "msgqueue/msgqueue_api.h"

int msg_init()
{
	int msgid = -1;

	/*build message queue*/
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	return msgid;
}

int msg_send(int fd, void *buf, int size)
{
	if (buf == NULL)
		printf("hello world\n");
	printf("data: %.*s\n", size, (char *)buf);
	if (msgsnd(fd, buf, 256, 0) == -1) {
		fprintf(stderr, "msgsend failed with errno: %d\n",
			errno);
		exit(EXIT_FAILURE);
	}
	printf("receive: %s\n", (char *)buf);
	return 0;
}

int msg_recv(int fd, void *buf, int size)
{
	if (msgrcv(fd, buf, size, 0, MSG_NOERROR | IPC_NOWAIT) == -1) {
		fprintf(stderr, "msgrcv failed with errno: %d\n",
			errno);
		exit(EXIT_FAILURE);
	}
	printf("receive: %s\n", (char *)buf);
	return 0;
}

#if 0
int main()
{
	int fd = msg_init();
	msg_send(fd, "hello", 5);

	return 0;
}
#endif
