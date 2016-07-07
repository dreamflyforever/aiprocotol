#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int msg_init();
int msg_send(int fd, void *buffer, int size);
int msg_recv(int fd, void *buffer, int size);
