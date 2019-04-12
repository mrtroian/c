#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/* reprnl replaces newline with the null terminator */
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
	struct sockaddr_in server_address;	/* structure to store server configuration */
	char recvbuff[1024];				/* buffer for recieved message */
	char sendbuff[1024];				/* buffer for message to be sent */
	int network_socket;					/* Socket that will be used to connect to the server */
	int connstate;						/* connection state */

	/* configuring server */
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	/* setting IP address to the structure */
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
		/* each iteration both buffers will be cleared */
		memset(recvbuff, 0, 1024);
		/* to prevent double newline in response */
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

	/*
	 * Checking for command line arguments
	 * if none, default port and IP address will be set.
	 */
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