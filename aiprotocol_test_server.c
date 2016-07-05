#include <stdio.h>
#include <var.h>
#include <unistd.h>
#include <string.h>
#include "socket/socket_api.h"
#include "aiprotocol.h"

int cb_1(u8 argc, u8 *argv)
{
	printf("%s\n", __func__);
	return 0;
}

int main(int argc, char **argv)
{
	int socket = socket_init(0, NULL);
#if 0
	char buffer[BUFFER_SIZE];
	bzero(buffer, sizeof(buffer));
	int length = 0;
	while (length = socket_recv(socket,
				buffer,
				BUFFER_SIZE)) {
		if (length < 0) {
			printf("Recieve Data From Client Failed!\n");
			break;
		}
		printf("receive: %s\n", buffer);
		socket_send(socket, buffer, BUFFER_SIZE);
		bzero(buffer, BUFFER_SIZE);
	}
	//close(socket);
	//close(server_socket);
#endif
	protocol_init(socket, NULL, socket_recv, socket_send, NULL);
	cb_reg(cb_1, 1);
	cmd_recv();
	return 0;
}
