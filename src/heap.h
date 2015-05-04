#ifndef __HEAP_H
#define __HEAP_H

typedef struct heap {
	void **a;
	int len; // data length
	int ml;  // memory length
	int (*cmp) (const void *a, const void *b); // cmp function
} heap;

heap* heap_create(int (*cmp) (const void* a, const void *b));
int heap_empty(heap *h);
void heap_push(heap *h, void *value);
void* heap_pop(heap *h) ;
void* heap_top(heap *h);

#endif