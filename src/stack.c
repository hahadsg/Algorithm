#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

stack *stack_create()
{
    stack *s;
    s = (stack*)malloc(sizeof(stack));
    s->pos = 0;
    s->len = 2;
    s->a = (void**)malloc( 2 * sizeof(void*) );
    return s;
}

int stack_empty(stack *s)
{
    return s->pos == 0;
}

void stack_push(stack *s, void *value)
{
    void **tmp;
    if ( s->len <= s->pos ) {
        tmp = (void**)malloc( 2 * s->len * sizeof(void*) );
        memcpy(tmp, s->a, s->len * sizeof(void*) );
        s->len *= 2;
        free(s->a);
        s->a = tmp;
    }
    s->a[s->pos++] = value;
}

void *stack_pop(stack *s)
{
    assert( !stack_empty(s) );
    return s->a[--s->pos];
}

void *stack_top(stack *s)
{
    assert( !stack_empty(s) );
    return s->a[s->pos-1];
}