#include <stdlib.h>
#include <stddef.h>
#include "queue.h"

/* queue_init:
 * Initializes the queue to its default values. */
void
queue_init(struct queue *s)
{
	s->head		= NULL;
	s->tail		= NULL;
	s->q_size	= 0;
}

/* queue_kill:
 * Dequeues all elements from the queue. */
void
queue_kill(struct queue *s)
{
	while (s->q_size > 0) {
		queue_deq(s, NULL);
	}
}

/* queue_enq:
 * Inserts an element after the queue's tail. It returns one of these negative
 * values on error:
 *
 * (-1): Q_MEMERRR: failed memory allocation. */
int
queue_enq(struct queue *q, unsigned value)
{
	struct queue_node *new = malloc(sizeof(struct queue_node));

	if (new == NULL) {
		return Q_MEMERR;
	}

	new->value = value;
	if (q->q_size == 0) {
		new->next	= q->head;
		q->head		= new;
		q->tail		= q->head;
	} else {
		struct queue_node *node = q->tail;
		q->tail		= new;
		new->next	= node->next;
		node->next	= new;
	}

	++q->q_size;

	return 0;
}

/* queue_deq:
 * Deletes the element the queue's head, storing it inside *store if it is not
 * NULL. Returns one of these negative values on failure:
 *
 * (-2): Q_INVQ: Empty queue/list passed as a parameter. */
int
queue_deq(struct queue *q, unsigned *store)
{
	/* Save the element for freeing. */
	struct queue_node *old;

	if (q->q_size == 0) {
		return Q_INVQ;
	}

	old	= q->head;
	q->head = q->head->next;

	/* The list will be empty after the end of this function. */
	if (q->q_size == 1) {
		q->tail = NULL;
	}

	if (store != NULL) {
		*store = old->value;
	}

	free(old);

	--q->q_size;

	return 0;
}
