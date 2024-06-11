#include <stdlib.h>
#include <stddef.h>
#include "sl-list.h"

/* sl_list_init:
 * Initializes the list to its default values. */
void
sl_list_init(struct sl_list *l)
{
	l->head		= NULL;
	l->tail		= NULL;
	l->sl_size	= 0;
}

/* sl_list_kill:
 * Pops all elements from the list. */
void
sl_list_kill(struct sl_list *l)
{
	while (l->sl_size > 0) {
		sl_rmv_after(l, NULL, NULL);
	}
}

/* sl_ins_after:
 * Inserts an element after a specified node. If the specified node is NULL,
 * an element is inserted at the head. It returns one of these negative values
 * on error:
 *
 * (-1): SL_MEMERR: failed memory allocation. */
int
sl_ins_after(struct sl_list *l, struct sl_node *n, unsigned value)
{
	struct sl_node *new = malloc(sizeof(struct sl_node));

	if (new == NULL) {
		return SL_MEMERR;
	}

	new->value = value;

	if (n == NULL) {
		new->next = l->head;
		l->head = new;

		if (l->sl_size == 0) {
			l->tail = l->head;
		}
	} else {
		/* Move the tail if inserting after it. */
		if (n->next == NULL) {
			l->tail = new;
		}

		new->next = n->next;
		n->next = new;
	}

	++l->sl_size;

	return 0;
}

/* sl_rmv_after:
 * Removes the element after the specified node. If the specified node is NULL,
 * the head is removed. Store the removed value in *store, if it's not NULL, as
 * well. The function returns one of those negative values on error:
 *
 * (-2): SL_INVLIST: Invalid list passed as a parameter, a.k.a. empty list.
 * (-3): SL_INVNODE: Invalid node passed as a parameter, a.k.a. trying to
 * remove a node beyond the tail. */
int
sl_rmv_after(struct sl_list *l, struct sl_node *n, unsigned *store)
{
	/* Save the element for freeing. */
	struct sl_node *old;

	if (l->sl_size == 0) {
		return SL_INVLIST;
	}

	if (n == NULL) {
		old	= l->head;
		l->head = l->head->next;

		/* The list will be empty after the end of this function. */
		if (l->sl_size == 1) {
			l->tail = NULL;
		}
	} else {
		if (n->next == NULL) { /* can't remove from after tail */
			return -1;
		}

		old = n->next;
		n->next = n->next->next;

		if (n->next == NULL) {
			l->tail = n;
		}
	}

	if (store != NULL) {
		*store = old->value;
	}

	free(old);

	--l->sl_size;

	return 0;
}

/* sl_ins_after_idx:
 * Loops through the list until it finds the node at a certain index, then add
 * a new node with the specified value after the found node. The indexing
 * functions make the list 0-indexed, with the head being its 0th. This simply
 * returns the same values as described in the corresponding non-indexing
 * function sl_ins_after. */
int
sl_ins_after_idx(struct sl_list *l, size_t idx, unsigned value)
{
	struct sl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return sl_ins_after(l, node, value);
}

/* sl_rmv_after_idx:
 * Loops through the list until it finds the node at a certain index, then
 * delete the node after it. Store the removed value if the specified pointer
 * is not NULL. This simply returns the same values as described in the
 * corresponding non-indexing function sl_rmv_after. */
int
sl_rmv_after_idx(struct sl_list *l, size_t idx, unsigned *store)
{
	struct sl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return sl_rmv_after(l, node, store);
}
