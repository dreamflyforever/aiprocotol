/*
 * client send file name and receive file from server.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket_api.h"

int socket_init(int argc, char **argv)
{
	struct sockaddr_in client_addr;
	int client_socket;
	struct sockaddr_in server_addr;
	if (argc != 2) {
		printf("Usage: %s ServerIPAddress\n", argv[0]);
		exit(1);
	}

	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0) {
		printf("Create Socket Failed!\n");
		exit(1);
	}

	if (bind(client_socket,
		(struct sockaddr*)&client_addr,
		sizeof(client_addr))) {
		printf("Client Bind Port Failed!\n");
		exit(1);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;

	if (inet_aton(argv[1], &server_addr.sin_addr) == 0) {
		printf("Server IP Address Error!\n");
		exit(1);
	}

	server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);

	if (connect(client_socket,
			(struct sockaddr*)&server_addr,
			server_addr_length) < 0) {
		printf("Can Not Connect To %s!\n", argv[1]);
		exit(1);
	}
	return client_socket;
}

int socket_send(int fd, char *buffer, int size)
{
	/*BUFFER_SIZE*/
	int ret;
	ret = send(fd, buffer, size, 0);
	return ret;
}

int socket_recv(int fd, char *buffer, int size)
{
	int ret;
	ret = recv(fd, buffer, size, 0);
	return ret;
}

#if 0
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
	return 0;
}
#endif
