#include <stddef.h>
#include <stdio.h>
#include "cl-list.h"

void display_list(struct cl_list *list);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct cl_list	my_list;

	cl_list_init(&my_list);

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

			if (cl_ins_before(&my_list, my_list.head, value)
			    == CL_MEMERR) {
				fputs("cl_insert_after failed\n", stderr);
				return 1;
			}

			break;
		case 2:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index > my_list.cl_size) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			if (cl_ins_after_idx(&my_list, index, value)
			    == CL_MEMERR) {
				fputs("cl_ins_after_idx failed\n", stderr);
				return 1;
			}

			break;
		case 3:
			fputs("What value? ", stdout);
			scanf("%u", &value);

			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index >= my_list.cl_size) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			if (cl_ins_before_idx(&my_list, index, value)
			    == CL_MEMERR) {
				fputs("cl_ins_after_idx failed\n", stderr);
				return 1;
			}

			break;
		case 4:
			if (cl_rmv_node(&my_list, my_list.head, &value) ==
			    CL_INVLIST) {
				fputs("The list is empty.\n", stdout);
				break;
			}

			printf("Value popped: %u\n", value);
			break;
		case 5:
			fputs("Where? ", stdout);
			scanf("%zu", &index);

			if (index >= (my_list.cl_size)) {
				fputs("Index is too big.\n", stdout);
				break;
			}

			cl_rmv_idx(&my_list, index, &value);

			printf("Value popped: %u\n", value);
			break;
		default:
			break;
		}

		putchar('\n');
	}

	cl_list_kill(&my_list);

	return 0;
}

void
display_list(struct cl_list *list)
{
	struct cl_node *node = list->head;

	for (size_t i = 0; i < list->cl_size; ++i) {
		printf("%u <-> ", node->value);
		node = node->next;
	}

	puts("...");
}
