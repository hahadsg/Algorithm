#ifndef __QUEUE_C
#define __QUEUE_C

typedef struct queue {
	void **a;
	int first, last;
    int len;
} queue;

queue *queue_create(void);
int queue_empty(queue *q);
void queue_push(queue *q, void *value);
void queue_pop(queue *q);
void *queue_top(queue *q);

#endif