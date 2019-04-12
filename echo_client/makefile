CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -Wpedantic

all: client

client: client.o
	$(CC) client.o -o client

client.o: client.c
	$(CC) -c client.c

clean:
	rm -f *.o