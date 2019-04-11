#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char **argv)
{
	int tries = 5;
	int port;

	if (argc < 2) {
		port = 8800;
		printf("Server port is not specified!\n");
		printf("Port %d will be used for connections.\n", port);
	} else {
		port = atoi(argv[1]);
	}

	while (serve(port) && --tries)
		fprintf(stderr, "Relaunching...\n");

	if (!(tries))
		fprintf(stderr, "Cannot start the server.\n");
	else
		printf("Server shutdown successfuly.\n");
	return 0;
}