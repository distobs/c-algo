#ifndef STACK_H
#define STACK_H

#include <sys/types.h>

/* How much space to realloc if the stack is full. */
#define GROW_BY 50

struct stack {
	unsigned	*stk;	/* The stack. */
	ssize_t		sp;	/* The stack pointer. -1 if stack is empty. */
	size_t		size;	/* The size allocated for the stack. */
};

enum {
	STK_MEMERR	= -1,
	STK_INVSTK	= -2,
};

void		stack_destroy(struct stack *s);
int		stack_empty(struct stack *s);
int		stack_enough(struct stack *s, unsigned needed);
unsigned	stack_head(struct stack *s);
void		stack_init(struct stack *s);
int		stack_pop(struct stack *s, unsigned *val);
int		stack_push(struct stack *s, unsigned val);

#endif
