#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include "queue.h"

void display_queue(struct queue *stack);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct queue	my_queue;

	queue_init(&my_queue);

	action = 0;
	while (action != -1) {
		puts("Here's what the list looks like:");
		display_queue(&my_queue);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1)  -> enqueue\n"
		     "(2)  -> dequeue\n");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (queue_enq(&my_queue, value) == Q_MEMERR) {
				fputs("queue_enq failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			if (queue_deq(&my_queue, &value) == Q_INVQ) {
				fputs("the queue is empty.", stdout);
			} else {
				printf("Dequeued: %u\n", value);
			}

			break;
		default: /* -1 will be handled by the loop condition */
			break;
		}

		putchar('\n');
	}

	queue_kill(&my_queue);

	return 0;
}

void
display_queue(struct queue *stack)
{
	struct queue_node *node = stack->head;

	while (node != NULL) {
		printf("%u ", node->value);
		node = node->next;
	}

	putchar('\n');
}
