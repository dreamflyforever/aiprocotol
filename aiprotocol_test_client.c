#include <stdio.h>
#include <var.h>
#include "socket/socket_api.h"
#include <unistd.h>

int cb_1(u8 argc, u8 **argv)
{
	printf("%s\n", __func__);
	return 0;
}

int main(int argc, char **argv)
{
	int client_socket = socket_init(argc, argv);

	char buffer[BUFFER_SIZE] = "hello world\n";
	printf("send buffer: %s\n", buffer);
	socket_send(client_socket, buffer, BUFFER_SIZE);
	int len;
	len = socket_recv(client_socket, buffer, BUFFER_SIZE);
	if (len >  0)
		printf("receive data from serve : %s\n", buffer);
	while (1)
		sleep(10);
	close(client_socket);
#if 0
	protocol_init(0, NULL, socket_recv, socket_send, NULL);
	cb_reg(1, cb_1);
	cmd_send(1, 0, NULL);
	cmd_recv();
#endif
	return 0;
}
