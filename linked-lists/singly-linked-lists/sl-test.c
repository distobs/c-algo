#include <stdio.h>
#include "sl-list.h"

void
display_list(struct sl_list *list)
{
	struct sl_node *node = list->head;

	while (node != NULL) {
		printf("%u -> ", node->value);
		node = node->next;
	}

	fputs("NULL\n", stdout);
}

int
main(void)
{
	unsigned	value;
	int		action;
	struct sl_list	my_list;

	sl_list_init(&my_list);

	action = 0;
	while (action != -1) {
		puts("Here's what the list looks like:");
		display_list(&my_list);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1) -> insert at head\n"
		     "(2) -> remove from head");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("What value? ", stdout);
			scanf("%u", &value);
			sl_insert_after(&my_list, NULL, value);
			break;
		case 2:
			if (sl_remove_after(&my_list, NULL, &value) == -1) {
				puts("The list is empty.");
			} else {
				printf("%u popped\n", value);
			}

			break;
		default: /* -1 will be handled by the loop condition */
			break;
		}
	}

	sl_list_kill(&my_list);

	return 0;
}
