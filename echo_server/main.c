#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

int main(int argc, char **argv)
{
	int tries = 5;
	int port;

	/*
	 * Checking for command line arguments
	 * if none, default port will be set.
	 */
	if (argc < 2) {
		port = 8800;
		printf("Server port is not specified!\n");
		printf("Port %d will be used for connections.\n", port);
	} else {
		port = atoi(argv[1]);
	}

	/* 
	 * In case of error, serve returns 1 and to be called after 1 second
	 * if nomber of tries exceed 5, loop will break.
	 */
	while (serve(port) && --tries) {
		fprintf(stderr, "Relaunching...\n");
		sleep(1);
	}

	/* printing error message, in case of failure */
	if (!(tries)) {
		fprintf(stderr, "Cannot start the server.\n");
		return 1;
	}
	return 0;
}