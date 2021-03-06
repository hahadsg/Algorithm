#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue.h"

queue *queue_create() 
{
    queue *q;
    q = (queue*)malloc(sizeof(queue));
    q->len = 2;
    q->a = (void**)malloc( 2 * sizeof(void*) );
    q->first = q->last = 0;
    return q;
}

int queue_empty(queue *q) 
{
    return q->first == q->last;
}

void queue_push(queue *q, void *value)
{
    void **tmp;
    if ( q->last >= q->len ) {
        tmp = (void**)malloc( 2 * (q->len) * sizeof(void*) );
        memcpy(tmp, q->a, (q->len) * sizeof(void*) );
        q->len *= 2;
        free(q->a);
        q->a = tmp;
    }
    q->a[q->last++] = value;
}

void *queue_pop(queue *q)
{
    assert( !queue_empty(q) );
    return q->a[q->first++];
}

void *queue_top(queue *q)
{
    assert( !queue_empty(q) );
    return q->a[q->first];
}