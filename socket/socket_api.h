#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define HELLO_WORLD_SERVER_PORT 6666
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int socket_init(int argc, char **argv);
int socket_send(int fd, char *buffer, int size);
int socket_recv(int fd, char *buffer, int size);
