#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int main(int argc, char **argv)
{
	node_t *list;

	if (argc == 1) {
		fprintf(stderr, "Program needs at least 1 argument.\n");
		exit(0);
	}
	list = create_list_node(argv[1]);
	int i = 1;

	while (++i < argc)
		push(list, argv[i]);

	reverse(&list);
	putlist(list);
	return 0;
}
