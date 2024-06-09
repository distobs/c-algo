#include <stdlib.h>
#include <stddef.h>
#include "dl-list.h"

/* dl_list_init:
 * Initializes the list to its default values. */
void
dl_list_init(struct dl_list *l)
{
	l->head		= NULL;
	l->tail		= NULL;
	l->dl_size	= 0;
}

/* dl_list_kill:
 * Pops all elements from the list. */
void
dl_list_kill(struct dl_list *l)
{
	while (l->dl_size > 0) {
		dl_rmv_node(l, l->head, NULL);
	}
}

/* dl_ins_after:
 * Inserts an element after a specified node. If the specified node is NULL,
 * and the specified list is not empty, the function assumes the user is
 * trying to put an element before the head, which they could easily do using
 * the corresponding dl_ins_before function, and returns an error. If the list
 * is empty and the specified node is NULL, the function goes on normally,
 * filling the list with the new node. It returns one of these negative values
 * on error:
 *
 * (-1): DL_MEMERR: failed memory allocation.
 * (-2): DL_INVNODE: n == NULL && size == 0. */
int
dl_ins_after(struct dl_list *l, struct dl_node *n, unsigned value)
{
	struct dl_node *new;

	/* The user is trying to ins after:
	 *
	 * NULL <-> head0 <-> n1 <-> n2 <-> tail3 <-> NULL
	 *  ^
	 * here
	 *
	 * If they wanted to insert at the head, they'd use dl_ins_before. */
	if (n == NULL && l->dl_size != 0) {
		return DL_INVNODE;
	}

	new = malloc(sizeof(struct dl_node));

	if (new == NULL) {
		return DL_MEMERR;
	}

	new->value = value;

	if (l->dl_size == 0) {
		l->head		= new;
		l->tail		= l->head;
		l->head->prev	= NULL;
		l->tail->next	= NULL;
	} else {
		new->next = n->next;
		new->prev = n;
		n->next = new;

		/* inserting after the tail */
		if (n->next == NULL) {
			l->tail = new;
		} else {
			n->next->prev = new;
		}
	}

	++l->dl_size;

	return 0;
}

/* dl_ins_before:
 * Inserts an element before a specified node. If the specified node is NULL,
 * and the specified list is not empty, the function assumes the user is
 * trying to put an element before the head's prev pointer. and returns an
 * error. If the list is empty and the specified node is NULL, the function
 * goes on normally, filling the list with the new node. It returns one of
 * these negative values on error:
 *
 * (-1): DL_MEMERR: failed memory allocation.
 * (-2): DL_INVNODE: n == NULL && size == 0. */
int
dl_ins_before(struct dl_list *l, struct dl_node *n, unsigned value)
{
	struct dl_node *new;

	/* See comment in dl_ins_after */
	if (n == NULL && l->dl_size != 0) {
		return DL_INVNODE;
	}

	new = malloc(sizeof(struct dl_node));

	if (new == NULL) {
		return DL_MEMERR;
	}

	new->value = value;

	if (l->dl_size == 0) {
		l->head		= new;
		l->tail		= l->head;
		l->head->prev	= NULL;
		l->tail->next	= NULL;
	} else {
		new->next = n;
		new->prev = n->prev;

		/* Inserting before/at the head */
		if (n->prev == NULL) {
			l->head = new;
		} else {
			n->prev->next = new;
		}

		n->prev = new;
	}

	++l->dl_size;

	return 0;
}

/* dl_rmv_node:
 * Removes the specified node. If the specified node is NULL, an error is
 * returned. Store the removed value in *store, if it's not NULL, The function
 * returns one of those negative values on error:
 *
 * (-2): DL_INVLIST: Invalid list passed as a parameter, a.k.a. empty list.
 * (-3): DL_INVNODE: Invalid node passed as a parameter, a.k.a. trying to
 * remove a node before or after the head or the tail, or simply trying to
 * remove a NULL node. */
int
dl_rmv_node(struct dl_list *l, struct dl_node *n, unsigned *store)
{
	if (l->dl_size == 0) {
		return DL_INVLIST;
	}

	if (n == NULL) {
		return DL_INVNODE;
	}

	if (n == l->head) {
		l->head = l->head->next;

		if (l->head == NULL) {
			l->tail = NULL;
		} else {
			l->head->prev = NULL;;
		}
	} else {
		n->prev->next = n->next;

		if (n->prev->next == NULL) {
			l->tail = n->prev;
		} else {
			n->next->prev = n->prev;
		}
	}

	if (store != NULL) {
		*store = n->value;
	}

	free(n);

	--l->dl_size;

	return 0;
}

/* dl_ins_after_idx:
 * Loops through the list until it finds the node at a certain index, then add
 * a new node with the specified value after the found node. The indexing
 * functions make the list 0-indexed, with the head being its 0th. This simply
 * returns the same values as described in the corresponding non-indexing
 * function dl_ins_after. */
int
dl_ins_after_idx(struct dl_list *l, size_t idx, unsigned value)
{
	struct dl_node *node = l->head;

	for (size_t i = 1; i < idx; ++i) {
		node = node->next;
	}

	return dl_ins_after(l, node, value);
}

/* dl_ins_before_idx:
 * Loops through the list until it finds the node at a certain index, then add
 * a new node with the specified value before the found node. This simply
 * returns the same values as described in the corresponding non-indexing
 * function dl_ins_after. */
int
dl_ins_before_idx(struct dl_list *l, size_t idx, unsigned value)
{
	struct dl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return dl_ins_before(l, node, value);
}

/* dl_rmv__idx:
 * Loops through the list until it finds the node at a certain index, then
 * delete the node. Store the removed value if the specified pointer is not
 * NULL. This simply returns the same values as described in the corresponding
 * non-indexing function dl_rmv_node. */
int
dl_rmv_idx(struct dl_list *l, size_t idx, unsigned *store)
{
	struct dl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return dl_rmv_node(l, node, store);
}
