#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string.h>

struct node {
	struct node *next;
	void *data;
};

struct linked_list {
	struct node *tail;
	struct node *head;
	size_t size;
};

struct node *node_new();
void node_dispose(struct node *n, void (*clean_routine)(void *));
struct linked_list *ll_new();
void ll_dispose(struct linked_list *ll, void (*clean_routine)(void *));
int ll_add_last(struct linked_list *ll, void *data);
void *ll_find(struct linked_list *ll, void *data, int (*cmpfn)(void *, void *));
void *ll_remove(struct linked_list *ll, void *data, void (*dispose)(void *), \
		int (*cmpfn)(void *, void *));








#endif
