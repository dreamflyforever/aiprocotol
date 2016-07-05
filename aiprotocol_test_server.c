#include <stdio.h>
#include <var.h>
#include <unistd.h>
#include <string.h>
#include "socket/socket_api.h"
#include "aiprotocol.h"

int cb_test(u8 argc, u8 *argv)
{
	printf("%s\n", __func__);
	return 0;
}

int main(int argc, char **argv)
{
	int socket = socket_init(0, NULL);
	protocol_init(socket, NULL, socket_recv, socket_send, NULL);
	cb_reg(cb_test, 1);
	cmd_recv();
	return 0;
}
