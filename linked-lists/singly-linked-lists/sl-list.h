#ifndef SL_LIST_H
#define	SL_LIST_H

#include <stddef.h>

struct sl_node {
	unsigned value;
	struct sl_node *next;
};

struct sl_list {
	struct sl_node *head;
	struct sl_node *tail;
	size_t sl_size;
};

void	sl_list_init(struct sl_list *list);
void	sl_list_kill(struct sl_list *list);
int	sl_insert_after(struct sl_list *list, struct sl_node *node,
			unsigned value);
int	sl_remove_after(struct sl_list *list, struct sl_node *node,
			unsigned *store);

#endif
