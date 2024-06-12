#ifndef STACK_LL_H
#define	STACK_LL_H

#include <stddef.h>

/* ll_stack_node:
 * The components of a node in the stack, made up of two components:
 * value: the value of that node.
 * next:  the next element to that node, or null if it's the stack's bottom. */
struct ll_stack_node {
	unsigned value;
	struct ll_stack_node *next;
};

/* ll_stack:
 * The linked list stack structure, made up of three components:
 * head:    the stack's head, its first element.
 * tail:    the stack's bottom, its last element. size == 1 <=> head == tail
 * stk_size: the stack's size. */
struct ll_stack {
	struct ll_stack_node *head;
	struct ll_stack_node *tail;
	size_t ll_stk_size;
};

enum {
	LL_STK_MEMERR	= -1,
	LL_STK_INVSTK	= -2,
	LL_STK_INVNODE	= -3
};

void	ll_stack_init(struct ll_stack *stack);
void	ll_stack_kill(struct ll_stack *stack);
int	ll_stack_push(struct ll_stack *l, unsigned value);
int	ll_stack_pop(struct ll_stack *l, unsigned *store);

#endif
