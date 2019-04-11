#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

node_t *create_list_node(void *data)
{
	node_t *list = (node_t*)malloc(sizeof(node_t));

	if (!(list)) {
		fprintf(stderr, "Memory allocation failed.\nAborted.\n");
		exit(0);
	}
	list->data = data;
	list->next = NULL;
	return list;
}

void reverse(node_t **list)
{
	node_t *current = *list;
	node_t *previous = NULL;
	node_t *next = NULL;

	while (current) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*list = previous;
}

void push(node_t *list, void *data)
{
	node_t *current = list;

	while (current->next)
		current = current->next;
	current->next = create_list_node(data);
}


void putlist(node_t *list)
{
	node_t *current = list;

	puts((char*) current->data);
	while (current->next) {
		current = current->next;
		puts((char*) current->data);
	}
}
