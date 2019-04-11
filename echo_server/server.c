#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

char *msgrev(char *str)
{
	char *s1 = str;
	char *s2 = str;
	char c = *str;

	while (c >= 32) {
		c = *(++s2 + 1);
	}

	while (s2 > s1) {
		c = *s1;
		*s1++ = *s2;
		*s2-- = c;
	}
	return str;
}

int listener(int sockfd)
{
	char recvbuff[1024];
	char sendbuff[1024];
	int client_socket_fd;
	
	memset(recvbuff, 0, 1024);

	while (1) {
		listen(sockfd, 1);
		client_socket_fd = accept(sockfd, NULL, NULL);

		if (client_socket_fd == -1) {
			fprintf(stderr, "Cannot connect\n");
			return 1;
		}
		send(client_socket_fd, "Connection succeed.\n", 21, 0);
		printf("New connection established.\n");

		while ((recv(client_socket_fd, &recvbuff, 1024, 0) > 0)) {
			memset(sendbuff, 0, 1024);
			msgrev(recvbuff);
			strcpy(sendbuff, recvbuff);
			send(client_socket_fd, sendbuff, 1024, 0);
			memset(recvbuff, 0, 1024);
		}
		send(client_socket_fd, "Connection closed.\n", 22, 0);
		close(client_socket_fd);
	}
	return 0;
}

int serve(int port)
{
	struct sockaddr_in server_address;
	int connstate;
	int sockfd;
	int yes = 1;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1) {
		fprintf(stderr, "Socket creation error.\n");
		return 1;
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = 0;
	connstate = bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));

	if (connstate == -1) {
		fprintf(stderr, "Socket in use.\n");
		close(sockfd);
		return 1;
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		fprintf(stderr, "Error in configuring socket.\n");
		close(sockfd);
		return 1;
	}
	printf("Server started on %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(port));
	listener(sockfd);
	close(sockfd);
	return 0;
}