#include <stdlib.h>
#include "sl-list.h"

void
sl_list_init(struct sl_list *list)
{
	list->head	= NULL;
	list->tail	= NULL;
	list->sl_size	= 0;
}

void
sl_list_kill(struct sl_list *list)
{
	while (list->sl_size > 0) {
		sl_remove_after(list, NULL, NULL);
	}
}

int
sl_insert_after(struct sl_list *list, struct sl_node *node, unsigned value)
{
	struct sl_node *new = malloc(sizeof(struct sl_node));

	if (new == NULL) {
		return -1;
	}

	new->value = value;
	if (node == NULL) {
		if (list->sl_size == 0) {
			list->tail = new;
		}

		new->next = list->head;
		list->head = new;
	} else {
		if (node->next == NULL) { /* inserting after tail */
			list->tail = new;
		}

		new->next = node->next;
		node->next = new;
	}

	++list->sl_size;

	return 0;
}

int
sl_remove_after(struct sl_list *list, struct sl_node *node, unsigned *store)
{
	struct sl_node *old;

	if (list->sl_size == 0) {
		return -1;
	}

	if (node == NULL) {
		if (list->sl_size == 1) {
			list->tail = NULL;
		}

		old = list->head;
		list->head = list->head->next;
	} else {
		if (node->next == NULL) { /* can't remove from after tail */
			return -1;
		}

		old = node->next;
		node->next = node->next->next;

		if (node->next == NULL) {
			list->tail = node;
		}
	}

	if (store != NULL) {
		*store = old->value;
	}

	free(old);

	--list->sl_size;

	return 0;
}
