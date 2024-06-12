#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include "stack-ll.h"

void display_stack(struct ll_stack *stack);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct ll_stack	my_stack;

	ll_stack_init(&my_stack);

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

			if (ll_stack_push(&my_stack, value) == LL_STK_MEMERR) {
				fputs("stack_push failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			if (ll_stack_pop(&my_stack, &value) == LL_STK_INVSTK) {
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

	ll_stack_kill(&my_stack);

	return 0;
}

void
display_stack(struct ll_stack *stack)
{
	struct ll_stack_node *node = stack->head;

	while (node != NULL) {
		printf("%u ", node->value);
		node = node->next;
	}

	putchar('\n');
}
