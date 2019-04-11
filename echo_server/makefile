CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -Wpedantic -ansi

all: server

server: main.o server.o
	$(CC) main.o server.o server.h -o server

main.o: main.c
	$(CC) $(CFLAGS) main.c

server.o: server.c
	$(CC) $(CFLAGS) server.c

clean:
	rm -rf *.o