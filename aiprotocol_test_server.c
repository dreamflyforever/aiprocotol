#include <stdio.h>
#include <var.h>
#include <unistd.h>
#include <string.h>
#include "socket/socket_api.h"

int cb_1(u8 argc, u8 **argv)
{
	printf("%s\n", __func__);
	return 0;
}

int main(int argc, char **argv)
{
	int socket = socket_init(0, NULL);
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

	return 0;
	return 0;
}
