#include <stdlib.h>
#include <stddef.h>
#include "sl-list.h"

void
sl_list_init(struct sl_list *l)
{
	l->head		= NULL;
	l->tail		= NULL;
	l->sl_size	= 0;
}

void
sl_list_kill(struct sl_list *l)
{
	while (l->sl_size > 0) {
		sl_remove_after(l, NULL, NULL);
	}
}

int
sl_insert_after(struct sl_list *l, struct sl_node *n, unsigned value)
{
	struct sl_node *new = malloc(sizeof(struct sl_node));

	if (new == NULL) {
		return -1;
	}

	new->value = value;
	if (n == NULL) {
		if (l->sl_size == 0) {
			l->tail = new;
		}

		new->next = l->head;
		l->head = new;
	} else {
		if (n->next == NULL) { /* inserting after tail */
			l->tail = new;
		}

		new->next = n->next;
		n->next = new;
	}

	++l->sl_size;

	return 0;
}

int
sl_remove_after(struct sl_list *l, struct sl_node *n, unsigned *store)
{
	struct sl_node *old;

	if (l->sl_size == 0) {
		return -1;
	}

	if (n == NULL) {
		if (l->sl_size == 1) {
			l->tail = NULL;
		}

		old = l->head;
		l->head = l->head->next;
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

int
sl_insert_after_idx(struct sl_list *l, size_t idx, unsigned value)
{
	struct sl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return sl_insert_after(l, node, value);
}

int
sl_remove_after_idx(struct sl_list *l, size_t idx, unsigned *store)
{
	struct sl_node *node = l->head;

	for (size_t i = 1; i <= idx; ++i) {
		node = node->next;
	}

	return sl_remove_after(l, node, store);
}
