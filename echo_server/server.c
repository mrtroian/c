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

	/*
	 * Finding the closest newline, end of line, or any other tabulation
	 * It will be treated as end of string
	 */
	while (c >= 32)
		c = *(++s2 + 1);

	while (s2 > s1) {
		c = *s1;
		*s1++ = *s2;
		*s2-- = c;
	}
	return str;
}

int worker(int sockfd)
{
	char recvbuff[1024];	/* buffer for recieved message */
	char sendbuff[1024];	/* buffer for message to be sent */
	int client_socket_fd;	/* client's socket descriptor */
	
	memset(recvbuff, 0, 1024);

	while (1) {
		listen(sockfd, 1);
		client_socket_fd = accept(sockfd, NULL, NULL);

		if (client_socket_fd == -1)
			return 1;
		/* sending first message to connected client */
		send(client_socket_fd, "Connection succeed.\n", 21, 0);
		printf("New connection established.\n");

		while ((recv(client_socket_fd, &recvbuff, 1024, 0) > 0)) {
			/* each iteration both buffers will be cleared */
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
	struct sockaddr_in server_address;	/* structure to store server configuration */
	int connstate;						/* connection state */
	int sockfd;							/* server's socket */
	int yes = 1;

	/* creating socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1) {
		fprintf(stderr, "Socket creation error.\n");
		return 1;
	}
	/* configuring server */
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = 0;
	connstate = bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));

	if (connstate == -1) {
		fprintf(stderr, "Socket in use.\n");
		close(sockfd);
		return 1;
	}

	/* setting additional configuration to socket */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
		fprintf(stderr, "Error in configuring socket.\n");
		close(sockfd);
		return 1;
	}
	printf("Server started on %s:%d\n", inet_ntoa(server_address.sin_addr), port);
	
	/* starting worker */
	if (worker(sockfd)) {
		fprintf(stderr, "Cannot connect\n");
		close(sockfd);
		return 1;
	}
	close(sockfd);
	return 0;
}