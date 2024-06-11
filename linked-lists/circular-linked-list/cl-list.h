#ifndef CL_LIST_H
#define CL_LIST_H

#include <stddef.h>

struct cl_node {
	unsigned	value;
	struct cl_node	*next;
	struct cl_node	*prev;
};

struct cl_list {
	struct cl_node	*head;
	size_t		cl_size;
};

enum {
	CL_MEMERR	= -1,
	CL_INVLIST	= -2,
	CL_INVNODE	= -3
};

void	cl_list_init(struct cl_list *l);
void	cl_list_kill(struct cl_list *l);
int	cl_ins_after(struct cl_list *l, struct cl_node *n, unsigned value);
int	cl_ins_before(struct cl_list *l, struct cl_node *n, unsigned value);
int	cl_rmv_node(struct cl_list *l, struct cl_node *n, unsigned *store);
int	cl_ins_after_idx(struct cl_list *l, size_t idx, unsigned value);
int	cl_ins_before_idx(struct cl_list *l, size_t idx, unsigned value);
int	cl_rmv_idx(struct cl_list *l, size_t idx, unsigned *store);

#endif
