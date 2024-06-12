#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include "stack.h"

void display_stack(struct stack *stack);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct stack	my_stack;

	stack_init(&my_stack);

	action = 0;
	while (action != -1) {
		puts("Here's what the list looks like:");
		display_stack(&my_stack);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1)  -> push\n"
		     "(2)  -> pop\n");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (stack_push(&my_stack, value) == STK_MEMERR) {
				fputs("stack_push failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			if (stack_pop(&my_stack, &value) == STK_INVSTK) {
				fputs("the stack is empty.", stdout);
			} else {
				printf("Popped: %u\n", value);
			}

			break;
		default: /* -1 will be handled by the loop condition */
			break;
		}

		putchar('\n');
	}

	stack_destroy(&my_stack);

	return 0;
}

void
display_stack(struct stack *stack)
{
	for (ssize_t i = stack->sp; i >= 0; --i) {
		printf("%u ", stack->stk[i]);
	}

	putchar('\n');
}
