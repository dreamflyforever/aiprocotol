/*
 * server be sent file
 */
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "socket_api.h"

#define HELLO_WORLD_SERVER_PORT 6666
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int socket_init(int argc, char **argv)
{
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

	int server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("Create Socket Failed!\n");
		exit(1);
	}

	if (bind(server_socket,
		(struct sockaddr*)&server_addr, sizeof(server_addr))) {
		printf("Server Bind Port: %d Failed!\n",
		HELLO_WORLD_SERVER_PORT);
		exit(1);
	}

	if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE)) {
		printf("Server Listen Failed!\n");
		exit(1);
	}

	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	int socket = accept(server_socket,
			(struct sockaddr*)&client_addr,
			&length);

	if (socket < 0) {
		printf("Server Accept Failed!\n");
	}

	return socket;

}
int socket_close()
{
	return 0;
}

int socket_send(int fd, void *buffer, int size)
{
	/*BUFFER_SIZE*/
	int ret;
	ret = send(fd, buffer, size, 0);
	return ret;
}

int socket_recv(int fd, void *buffer, int size)
{
	int ret;
	ret = recv(fd, buffer, size, 0);
	return ret;
}

#if 0
/*test case*/
int main(int argc, char **argv)
{
	int socket = socket_init();
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
	close(socket);
	close(server_socket);

	return 0;
}
#endif
