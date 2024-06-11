#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "cl-list.h"

void
cl_list_init(struct cl_list *l)
{
	l->head		= NULL;
	l->cl_size	= 0;
}

void
cl_list_kill(struct cl_list *l)
{
	while (l->cl_size > 0) {
		cl_rmv_node(l, l->head, NULL);
	}
}

int
cl_ins_after(struct cl_list *l, struct cl_node *n, unsigned value)
{
	struct cl_node *new = malloc(sizeof(struct cl_node));

	if (new == NULL) {
		return CL_MEMERR;
	}

	if (n == NULL && l->cl_size > 0) {
		return CL_INVNODE;
	}

	new->value = value;

	if (l->cl_size == 0) {
		l->head = new;
		new->next = new->prev = new;
	} else {
		new->next	= n->next;
		new->prev	= n;
		n->next		= new;
	}

	++l->cl_size;

	return 0;
}

int
cl_ins_before(struct cl_list *l, struct cl_node *n, unsigned value)
{
	struct cl_node *new = malloc(sizeof(struct cl_node));

	if (new == NULL) {
		return CL_MEMERR;
	}

	if (n == NULL && l->cl_size > 0) {
		return CL_INVNODE;
	}

	new->value = value;

	if (l->cl_size == 0) {
		l->head		= new;
		new->next	= new->prev = new;
	} else {
		new->next = n;
		new->prev = n->prev;

		if (n == l->head) {
			l->head = new;
		} else {
			new->prev->next = new;
		}

		n->prev = new;
	}

	++l->cl_size;

	return 0;
}

int
cl_rmv_node(struct cl_list *l, struct cl_node *n, unsigned *store)
{
	if (l->cl_size == 0) {
		return CL_INVLIST;
	}

	if (n == NULL) {
		return CL_INVNODE;
	}

	if (n == l->head) {
		l->head = n->next;
	} else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}

	--l->cl_size;

	free(n);

	return 0;
}

int
cl_ins_after_idx(struct cl_list *l, size_t idx, unsigned value)
{
	struct cl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return cl_ins_after(l, node, value);
}

int
cl_ins_before_idx(struct cl_list *l, size_t idx, unsigned value)
{
	struct cl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return cl_ins_before(l, node, value);
}

int
cl_rmv_idx(struct cl_list *l, size_t idx, unsigned *store)
{
	struct cl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return cl_rmv_node(l, node, store);
}
