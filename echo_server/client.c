#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void setnull(char *str, int n)
{
	char *in = str;
	while(in - n != str)
		*in++ = 0;
}

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
	char buff[1024];

	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	// server_address.sin_addr.s_addr = 0;
	inet_aton(addr, server_address.sin_addr.s_addr);

	if (network_socket == -1)
		fprintf(stderr, "Socket creation error\n");
	connstate = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	if (connstate == -1)
		fprintf(stderr, "Connection error\n");

	printf("Connecting to %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(port));
	memset(buff, 0, 1024);
	recv(network_socket, &recvbuff, 1024, 0);
	printf("%s\n", recvbuff);

	while(read(0, buff, 1020) != -1) {
		memset(buff, 0, 1024);
		reprnl(buff);
		send(network_socket, buff, 1024, 0);
		recv(network_socket, &recvbuff, 1024, 0);
		printf("%s\n", recvbuff);
		memset(buff, 0, 1024);
	}
	close(network_socket);
	return 0;
}

int main(int argc, char **argv)
{
	int port;

	if (argc < 3) {
		port = 8800;
		addr = "127.0.0.1";
	} else {
		printf("%s\n", );
		port = atoi(argv[1]);
		addr = argv[2];
	}

	client(port);
	return 0;
}