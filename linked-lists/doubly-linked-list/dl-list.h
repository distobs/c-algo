#ifndef DL_LIST_H
#define	DL_LIST_H

#include <stddef.h>

/* dl_node:
 * The components of a node in the list, made up of two components:
 * value: the value of that node.
 * next:  the next element to that node, or null if it's the list's tail.
 * prev:  the previous element to that node, or null if it's the list's head.
 */
struct dl_node {
	unsigned value;
	struct dl_node *next;
	struct dl_node *prev;
};

/* dl_list:
 * The list structure, made up of three components:
 * head:    the list's head, its first element.
 * tail:    the list's tail, its last element. size == 1 <=> head == tail
 * sl_size: the list's size. */
struct dl_list {
	struct dl_node *head;
	struct dl_node *tail;
	size_t dl_size;
};

enum {
	DL_MEMERR	= -1,
	DL_INVLIST	= -2,
	DL_INVNODE	= -3,
};

void	dl_list_init(struct dl_list *list);
void	dl_list_kill(struct dl_list *list);
int	dl_ins_after(struct dl_list *l, struct dl_node *n, unsigned value);
int	dl_ins_before(struct dl_list *l, struct dl_node *n, unsigned value);
int	dl_rmv_node(struct dl_list *l, struct dl_node *n, unsigned *store);
int	dl_ins_after_idx(struct dl_list *l, size_t idx, unsigned value);
int	dl_ins_before_idx(struct dl_list *l, size_t idx, unsigned value);
int	dl_rmv_idx(struct dl_list *l, size_t idx, unsigned *store);

#endif
