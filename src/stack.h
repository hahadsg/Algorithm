#ifndef __STACK_H
#define __STACK_H

typedef struct stack {
    void **a;
    int pos;
    int len;
} stack;

stack *stack_create(void);
int stack_empty(stack *s);
void stack_push(stack *s, void *value);
void *stack_pop(stack *s);
void *stack_top(stack *s);

#endif