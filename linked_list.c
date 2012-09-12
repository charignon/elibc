/**
 * A simple yet modular simply linked list implementation
 */
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



struct node *node_new()
{
	struct node *n = (struct node *) malloc(sizeof(struct node));
	n->next = NULL;
	return n;
}

void node_dispose(struct node *n, void (*clean_routine)(void *))
{
	clean_routine(n->data);
	free(n);
}

struct linked_list *ll_new()
{
	struct linked_list *ll = (struct linked_list *)\
				 malloc(sizeof(struct linked_list));
	ll->size = 0;
	ll->head = NULL;
	ll->tail = NULL;
	return ll;
}
void ll_dispose(struct linked_list *ll, void (*clean_routine)(void *))
{
	struct node *current = NULL;
	current = ll->head;
	struct node *next;
	while (current != NULL) {
		next = current->next;
		node_dispose(current, clean_routine);
		current = next;
	}
	ll->size = 0;
	free(ll);
}

/**
 * Returns -1 if it fails
 */
int ll_add_last(struct linked_list *ll, void *data)
{
	struct node *n = node_new();
	if (n == NULL)
		return -1;
	n->data = data;
	if (ll->tail != NULL)
		ll->tail->next = n;
	ll->size++;
	ll->tail = n;
	if (ll->head == NULL)
		ll->head = n;
	return 0;
}

void *ll_find(struct linked_list *ll, void *data, int (*cmpfn)(void *, void *))
{
	struct node *current = ll->head;
	while (current != NULL) {
		if (cmpfn(current->data,data) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void *ll_remove(struct linked_list *ll, void *data, void (*dispose)(void *), \
		int (*cmpfn)(void *, void *))
{
	struct node *current = ll->head;
	struct node *previous;
	if (ll->head == NULL) {
		return NULL;
	}
	
	if (cmpfn(ll->head->data, data) == 0){
		current = ll->head->next;
		node_dispose(ll->head, dispose);
		ll->head = current;
		ll->size--;
		return current;
	}
	previous = ll->head;
	current = ll->head->next;
	
	while (current != NULL) {
		if (cmpfn(current,data) == 0) {
			previous->next = current->next;
			node_dispose(current, dispose);
			ll->size--;
			return previous;
		}
		previous = current;
		current = current->next;
	}
	return NULL;
}









