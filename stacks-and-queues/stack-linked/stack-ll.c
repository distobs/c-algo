#include <stdlib.h>
#include <stddef.h>
#include "stack-ll.h"

/* ll_stack_init:
 * Initializes the stack to its default values. */
void
ll_stack_init(struct ll_stack *s)
{
	s->head		= NULL;
	s->tail		= NULL;
	s->ll_stk_size	= 0;
}

/* stack_kill:
 * Pops all elements from the stack. */
void
ll_stack_kill(struct ll_stack *s)
{
	while (s->ll_stk_size > 0) {
		ll_stack_pop(s, NULL);
	}
}

/* stack_push:
 * Inserts an element at the stack's head. It returns one of these negative
 * values on error:
 *
 * (-1): LL_STK_MEMERRR: failed memory allocation. */
int
ll_stack_push(struct ll_stack *s, unsigned value)
{
	struct ll_stack_node *new = malloc(sizeof(struct ll_stack_node));

	if (new == NULL) {
		return LL_STK_MEMERR;
	}

	new->value = value;

       	new->next = s->head;
       	s->head = new;

       	if (s->ll_stk_size == 0) {
	       	s->tail = s->head;
       	}

	++s->ll_stk_size;

	return 0;
}

/* ll_stack_pop:
 * Deletes the element at the top of the stack, storing it inside *store if
 * store is not NULL. Returns one of these negative values on failure:
 *
 * (-2): LL_LL_STK_INVSTK: Empty stack/list passed as a parameter. */
int
ll_stack_pop(struct ll_stack *s, unsigned *store)
{
	/* Save the element for freeing. */
	struct ll_stack_node *old;

	if (s->ll_stk_size == 0) {
		return LL_STK_INVSTK;
	}

       	old	= s->head;
       	s->head = s->head->next;

       	/* The list will be empty after the end of this function. */
       	if (s->ll_stk_size == 1) {
       		s->tail = NULL;
       	}

	if (store != NULL) {
		*store = old->value;
	}

	free(old);

	--s->ll_stk_size;

	return 0;
}
