CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -Wpedantic

all: linkedlist

linkedlist: main.o linkedlist.o
	$(CC) main.o linkedlist.o linkedlist.h -o linkedlist

main.o: main.c
	$(CC) $(CFLAGS) main.c

linkedlist.o: linkedlist.c
	$(CC) $(CFLAGS) linkedlist.c

clean:
	rm -f *.o