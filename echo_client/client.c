#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void reprnl(char *str)
{
	char *sstr = str;

	if(!(*str))
		return;

	while(*sstr != 10 && *sstr != 0)
		sstr++;
	*sstr = 0;
}

int client(int port, char *addr)
{
	struct sockaddr_in server_address;
	int connstate;
	int network_socket;
	char recvbuff[1024];
	char sendbuff[1024];

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	inet_pton(AF_INET, addr, &(server_address.sin_addr));

	if (network_socket == -1) {
		fprintf(stderr, "Socket creation error\n");
		return 1;
	}
	connstate = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	if (connstate == -1) {
		fprintf(stderr, "Cannot connect to %s:%d\n", addr, port);
		return 1;
	}
	printf("Connecting to %s:%d\n", addr, port);
	memset(sendbuff, 0, 1024);
	recv(network_socket, &recvbuff, 1024, 0);

	while(read(0, sendbuff, 1020) != -1) {
		memset(recvbuff, 0, 1024);
		reprnl(sendbuff);
		send(network_socket, sendbuff, 1024, 0);
		recv(network_socket, &recvbuff, 1024, 0);
		printf("%s\n", recvbuff);
		memset(sendbuff, 0, 1024);
	}
	close(network_socket);
	return 0;
}

int main(int argc, char **argv)
{
	char *addr;
	int port;

	if (argc < 3) {
		port = 8800;
		addr = "127.0.0.1";
	} else {
		port = atoi(argv[2]);
		addr = argv[1];
		printf("Trying to connect: %s %i\n", addr, port);
	}

	client(port, addr);
	return 0;
}