#ifndef SL_LIST_H
#define	SL_LIST_H

#include <stddef.h>

/* sl_node:
 * The components of a node in the list, made up of two components:
 * value: the value of that node.
 * next:  the next element to that node, or null if it's the list's tail. */
struct sl_node {
	unsigned value;
	struct sl_node *next;
};

/* sl_list:
 * The list structure, made up of three components:
 * head:    the list's head, its first element.
 * tail:    the list's tail, its last element. size == 1 <=> head == tail
 * sl_size: the list's size. */
struct sl_list {
	struct sl_node *head;
	struct sl_node *tail;
	size_t sl_size;
};

enum {
	SL_MEMERR	= -1,
	SL_INVLIST	= -2,
	SL_INVNODE	= -3
};

void	sl_list_init(struct sl_list *list);
void	sl_list_kill(struct sl_list *list);
int	sl_ins_after(struct sl_list *l, struct sl_node *n, unsigned value);
int	sl_rmv_after(struct sl_list *l, struct sl_node *n, unsigned *store);
int	sl_ins_after_idx(struct sl_list *l, size_t idx, unsigned value);
int	sl_rmv_after_idx(struct sl_list *l, size_t idx, unsigned *store);

#endif
