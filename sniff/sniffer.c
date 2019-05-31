#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#define FAIL (-1)
#define BUFFSIZ (1024)

void packet_dump(char *packet, int length);


int main(int arggc, char **argv)
{
	char buff[BUFFSIZ];
	int received;
	int sockfd;

	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if (sockfd == FAIL) {
		fprintf(stderr, "Fail to listen a socket\n");
		exit(FAIL);
	}

	while (1) {
		memset(buff, 0, BUFFSIZ);
		received = recv(sockfd, buff, 12000, 0);
		printf("Caught %i byte packet.\n", received);
		packet_dump(buff, received);
	}
}

void packet_dump(char *packet, int length)
{
	unsigned char byte;
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	byte = 0;

	while (i < length) {
		do {
			byte = packet[i];
			if (byte < 16)
				printf("0");
			printf("%x ", byte);
			i++;
		} while (i % 32);
		printf("|");

		do {
			byte = packet[j];
			if (byte > 32 && byte < 123)
				printf("%c", byte);
			else
				printf(".");
			j++;
		} while (j % 32);
		printf("\n");
	}
	printf("\n");
}