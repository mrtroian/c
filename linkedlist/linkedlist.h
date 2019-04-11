#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct list_s {
	void *data;
	struct list_s *next;
} node_t;

node_t *create_list_node(void*);
void push(node_t*, void*);
void reverse(node_t**);
void putlist(node_t*);

#endif