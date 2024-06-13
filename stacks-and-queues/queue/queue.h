#ifndef QUEUE_H
#define	QUEUE_H

#include <stddef.h>

/* queue_node:
 * The components of a node in the queue, made up of two components:
 * value: the value of that node.
 * next:  the next element to that node, or null if it's the queue's bottom. */
struct queue_node {
	unsigned value;
	struct queue_node *next;
};

/* queue:
 * The queue structure, made up of three components:
 * head:    the queue's head, its first element.
 * tail:    the queue's bottom, its last element. size == 1 <=> head == tail
 * queue_size: the queue's size. */
struct queue {
	struct queue_node *head;
	struct queue_node *tail;
	size_t q_size;
};

enum {
	Q_MEMERR	= -1,
	Q_INVQ		= -2,
	Q_INVNODE	= -3
};

void	queue_init(struct queue *queue);
void	queue_kill(struct queue *queue);
int	queue_enq(struct queue *q, unsigned value);
int	queue_deq(struct queue *q, unsigned *store);

#endif
