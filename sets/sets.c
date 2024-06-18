#include <stdlib.h>
#include "sets.h"

void
set_init(struct set *s)
{
	s->head		= NULL;
	s->tail		= NULL;
	s->set_size	= 0;
}

void
set_kill(struct set *s)
{
	while (s->set_size > 0) {
		set_rmv(s, s->head->value);
	}
}

int
set_is_equal(struct set *s1, struct set *s2)
{
	struct set_node *node;

	if (s1->set_size != s2->set_size) {
		return 0;
	}

	return set_is_subset(s1, s2);
}

int
set_is_member(struct set *s, unsigned value)
{
	struct set_node *n = s->head;

	while (n != NULL) {
		if (n->value == value) {
			return 1;
		} else {
			n = n->next;
		}
	}

	return 0;
}

int
set_is_subset(struct set *super, struct set *sub)
{
	struct set_node *node;

	if (sub->set_size > super->set_size) {
		return 0;
	}

	for (node = sub->head; node != NULL; node = node->next) {
		if (!set_is_member(super, node->value)) {
			return 0;
		}
	}

	return 1;
}

int
set_ins(struct set *s, unsigned value)
{
	if (set_is_member(s, value)) {
		return SET_ALREADY;
	}

	struct set_node *new = malloc(sizeof(struct set_node));

	if (new == NULL) {
		return SET_MEMERR;
	}

	/* adapted from sl_ins_after, from the singly-linked list. */
	new->value = value;

	if (s->set_size == 0) {
		new->next	= s->head;
		s->head		= new;
		s->tail		= s->head;
	} else {
		new->next	= s->tail->next;
		s->tail->next	= new;
		s->tail		= new;
	}

	++s->set_size;

	return 0;
}

int
set_rmv(struct set *s, unsigned value)
{
	struct set_node *n	= s->head;
	struct set_node *prev	= NULL;
	struct set_node *old	= NULL;

	while (n != NULL) {
		if (n->value == value) {
			break;
		} else {
			prev	= n;
			n	= n->next;
		}
	}

	if (n == NULL) {
		return SET_NOMEMB;
	}

	/* imported from sl_rmv_after in the singly-linked list source. */
	if (prev == NULL) {
		old	= s->head;
		s->head = s->head->next;

		if (s->set_size == 1) {
			s->tail = NULL;
		}
	} else {
		old 		= prev->next;
		prev->next	= prev->next->next;

		if (prev->next == NULL) {
			s->tail = prev;
		}
	}

	--s->set_size;

	return 0;
}

int
set_union(struct set *target, struct set *s1, struct set *s2)
{
	struct set_node *node;

	set_init(target);

	/* first set */
	for (node = s1->head; node != NULL; node = node->next) {
		if (set_ins(target, node->value) == SET_MEMERR) {
			set_kill(target);
			return SET_MEMERR;
		}
	}
	
	/* second set */
	for (node = s2->head; node != NULL; node = node->next) {
		if (set_is_member(s1, node->value)) {
			continue;
		} else {
			if (set_ins(target, node->value) == SET_MEMERR) {
				set_kill(target);
				return SET_MEMERR;
			}
		}
	}

	return 0;
}

int
set_inter(struct set *target, struct set *s1, struct set *s2)
{
	struct set_node *node;

	set_init(target);

	for (node = s1->head; node != NULL; node = node->next) {
		if (set_is_member(s2, node->value)) {
			if (set_ins(target, node->value) == SET_MEMERR) {
				set_kill(target);
				return SET_MEMERR;
			}
		}
	}

	return 0;
}

int
set_diff(struct set *target, struct set *s1, struct set *s2)
{
	struct set_node *node;

	set_init(target);

	for (node = s1->head; node != NULL; node = node->next) {
		if (!set_is_member(s2, node->value)) {
			if (set_ins(target, node->value) == SET_MEMERR) {
				set_kill(target);
				return SET_MEMERR;
			}
		}
	}

	return 0;
}
