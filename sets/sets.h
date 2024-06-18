#ifndef SETS_H
#define SETS_H

/* this implementation is highly inefficient. i'll try an rb-tree later or
 * something. */
#include <stddef.h>

struct set_node {
	unsigned	value;
	struct		set_node *next;
};

struct set {
	struct set_node *head;
	struct set_node *tail;
	size_t		set_size;
};

enum {
	SET_MEMERR	= -1,
	SET_ALREADY	= -2,
	SET_NOMEMB	= -3
};

void	set_init(struct set *s);
void	set_kill(struct set *s);
int	set_is_equal(struct set *s1, struct set *s2);
int	set_is_member(struct set *s, unsigned value);
int	set_is_subset(struct set *super, struct set *sub);
int	set_ins(struct set *s, unsigned value);
int	set_rmv(struct set *s, unsigned value);
int	set_union(struct set *target, struct set *s1, struct set *s2);
int	set_inter(struct set *target, struct set *s1, struct set *s2);
int	set_diff(struct set *target, struct set *s1, struct set *s2);

#endif
