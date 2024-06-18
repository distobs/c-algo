#include <stddef.h>
#include <stdio.h>
#include "sl-list.h"

void display_list(struct sl_list *list);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct sl_list	my_list;

	sl_list_init(&my_list);

	action = 0;
	while (action != -1) {
		puts("Here's what the list looks like:");
		display_list(&my_list);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1)  -> insert at head\n"
		     "(2)  -> insert after index\n"
		     "(3)  -> remove at head\n"
		     "(4)  -> remove after index\n");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (sl_ins_after(&my_list, NULL, value) == SL_MEMERR) {
				sl_list_kill(&my_list);
				fputs("sl_ins_after failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index > my_list.sl_size) {
				fputs("The index is too big.\n", stdout);
				break;
			}

			if (sl_ins_after_idx(&my_list, index, value) ==
			    SL_MEMERR) {
				sl_list_kill(&my_list);
				fputs("sl_ins_after_idx failed\n", stderr);
				return 1;
			}

			break;
		case 3:
			if (sl_rmv_after(&my_list, NULL, &value)
			    == SL_INVLIST) {
				puts("The list is empty.");
			} else {
				printf("%u popped\n", value);
			}

			break;
		case 4:
			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index >= my_list.sl_size) {
				fputs("The index is too big.\n", stdout);
				break;
			}

			/* empty lists are handed by the previous if
			 * statement. */
			sl_rmv_after_idx(&my_list, index, &value);
			printf("%u popped\n", value);

			break;
		default: /* -1 will be handled by the loop condition */
			break;
		}

		putchar('\n');
	}

	sl_list_kill(&my_list);

	return 0;
}

void
display_list(struct sl_list *list)
{
	struct sl_node *node = list->head;

	while (node != NULL) {
		printf("%u -> ", node->value);
		node = node->next;
	}

	puts("NULL");
}
