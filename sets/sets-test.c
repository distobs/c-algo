#include <stddef.h>
#include <stdio.h>
#include "sets.h"

void display_set(struct set *s);

int
main(void)
{
	unsigned	value;
	size_t		index;
	int		action;
	struct set	my_set;
	struct set	another_set;
	struct set	victim;

	set_init(&my_set);
	set_init(&another_set);

	action = 0;
	while (action != -1) {
		puts("Here's what your two sets looks like:");
		display_set(&my_set);
		display_set(&another_set);

		puts("Choose your action:");
		puts("(-1) -> quit\n"
		     "(1)  -> insert a new element\n"
		     "(2)  -> remove an element\n"
		     "(3)  -> perform an union\n"
		     "(4)  -> perform an intersection\n"
		     "(5)  -> get the difference between 1st and 2nd");

		fputs("> ", stdout);

		scanf("%d", &action);

		switch (action) {
		case 1:
			fputs("Which set? (1 or 2): ", stdout);
			scanf("%u", &action);

			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (action == 1) {
				if (set_ins(&my_set, value) == SET_MEMERR) {
					fputs("set_ins failed\n", stderr);
					set_kill(&my_set);
					set_kill(&another_set);
					return 1;
				}
			} else if (action == 2) {
				if (set_ins(&another_set, value)
						== SET_MEMERR) {
					fputs("set_ins failed\n", stderr);
					set_kill(&my_set);
					set_kill(&another_set);
					return 1;
				}
			} else {
				fputs("wtf?\n", stdout);
			}

			break;
		case 2:
			fputs("Which set? (1 or 2): ", stdout);
			scanf("%u", &action);

			fputs("What value? ", stdout);
			scanf("%u", &value);

			if (action == 1) {
				if (set_rmv(&my_set, value) == SET_NOMEMB) {
					fputs("Set 1 has no such member.\n",
							stderr);
				}
			} else if (action == 2) {
				if (set_rmv(&another_set, value)
						== SET_NOMEMB) {
					fputs("Set 2 has no such member.\n",
							stderr);
				}
			} else {
				fputs("wtf?\n", stdout);
			}

			break;
		case 3:
			if (set_union(&victim, &my_set, &another_set)
					== SET_MEMERR) {
				fputs("set_union failed\n", stderr);
				set_kill(&my_set);
				set_kill(&another_set);
				return 1;
			}

			fputs("Here's your baby:\n", stdout);
			display_set(&victim);

			set_kill(&victim); /* poor thing */
			break;
		case 4:
			if (set_inter(&victim, &my_set, &another_set)
					== SET_MEMERR) {
				fputs("set_inter failed\n", stderr);
				set_kill(&my_set);
				set_kill(&another_set);
				return 1;
			}

			fputs("Here's your baby:\n", stdout);
			display_set(&victim);

			set_kill(&victim); /* :( */
			break;
		case 5:
			if (set_diff(&victim, &my_set, &another_set)
					== SET_MEMERR) {
				fputs("set_diff failed\n", stderr);
				set_kill(&my_set);
				set_kill(&another_set);
				return 1;
			}

			fputs("Here's your baby:\n", stdout);
			display_set(&victim);

			set_kill(&victim); /* :( */
			break;
		default: /* -1 will be handled by the loop condition */
			break;
		}

		putchar('\n');
	}

	set_kill(&my_set);

	return 0;
}

void
display_set(struct set *s)
{
	struct set_node *node = s->head;

	putchar('{');

	if (node == NULL) {
		fputs("}\n", stdout);
		return;
	}

	while (node->next != NULL) {
		printf("%u,", node->value);
		node = node->next;
	}

	printf("%u}\n", node->value);
}
