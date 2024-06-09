#include <stddef.h>
#include <stdio.h>
#include "dl-list.h"

void display_list(struct dl_list *list);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct dl_list	my_list;

	dl_list_init(&my_list);

	action = 0;
	while (action != -1) {
		puts("Here's what the list looks like:");
		display_list(&my_list);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1)  -> insert at head\n"
		     "(2)  -> insert after index\n"
		     "(3)  -> insert before index\n"
		     "(4)  -> remove at head\n"
		     "(5)  -> remove at index\n");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (dl_ins_before(&my_list, my_list.head, value)
			    == DL_MEMERR) {
				fputs("dl_insert_after failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index > my_list.dl_size) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			if (dl_ins_after_idx(&my_list, index, value)
			    == DL_MEMERR) {
				fputs("dl_ins_after_idx failed\n", stderr);
				return 1;
			}

			break;
		case 3:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index >= my_list.dl_size) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			if (dl_ins_before_idx(&my_list, index, value)
			    == DL_MEMERR) {
				fputs("dl_ins_after_idx failed\n", stderr);
				return 1;
			}

			break;
		case 4:
			if (dl_rmv_node(&my_list, my_list.head, &value) ==
			    DL_INVLIST) {
				fputs("The list is empty.\n", stdout);
				break;
			}

			printf("Value popped: %u\n", value);
			break;
		case 5:
			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index >= (my_list.dl_size)) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			dl_rmv_idx(&my_list, index, &value);

			printf("Value popped: %u\n", value);
			break;
		}

		putchar('\n');
	}

	dl_list_kill(&my_list);

	return 0;
}

void
display_list(struct dl_list *list)
{
	struct dl_node *node = list->head;

	if (list->dl_size != 0) {
		fputs("NULL <-> ", stdout);
	}

	while (node != NULL) {
		printf("%u <-> ", node->value);
		node = node->next;
	}

	puts("NULL");
}
