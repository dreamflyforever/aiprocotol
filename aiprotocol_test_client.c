#include <stdio.h>
#include <var.h>
#include <unistd.h>
#include <stdlib.h>
#include "aiprotocol.h"
#include "socket/socket_api.h"

int cb_test(u8 argc, u8 *argv)
{
	printf("%s\n", __func__);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: %s ServerIPAddress\n", argv[0]);
		exit(1);
	}

	int client_socket = socket_init(argc, argv);
	protocol_init(client_socket, NULL, socket_recv, socket_send, NULL);
	cb_reg(cb_test, 1);
	cmd_send(1, 0, NULL);
	cmd_recv();
	return 0;
}
