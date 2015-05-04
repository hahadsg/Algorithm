#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "heap.h"

heap* heap_create(int (*cmp) (const void* a, const void *b))
{
	heap *h;

	h = (heap*)malloc(sizeof(heap));
	h->ml = 2;
	h->len = 0;
	h->a = (void**)malloc( h->ml * sizeof(void*) );
	h->cmp = cmp;

	return h;
}

int heap_empty(heap *h)
{
	return h->len == 0;
}

void heap_push(heap *h, void *value) 
{
	int i;
	void *tmp;

	if ( h->len == h->ml - 1 ) {
		tmp = (void**)malloc( 2 * h->ml * sizeof(void*) );
		memcpy(tmp, h->a, h->ml * sizeof(void*) );
		h->ml *= 2;
		free(h->a);
		h->a = tmp;
	}

	h->a[++h->len] = value;
	for (i = h->len; i > 1;) {
		if ( h->cmp( h->a[i], h->a[i/2] ) > 0 ) {
			tmp = h->a[i], h->a[i] = h->a[i/2], h->a[i/2] = tmp;
			i /= 2;
		} else {
			return ;
		}
	}
}

void* heap_pop(heap *h) 
{
	int i, pos;
	void *tmp, *res;

	assert( !heap_empty(h) );

    res = h->a[1];
	h->a[1] = h->a[h->len--];
	for (i = pos = 1;; i = pos) {
		if ( 2*i+1 <= h->len ) {
			pos = h->cmp( h->a[2*i], h->a[2*i+1] ) > 0 ? 2*i : 2*i+1;
		} else if ( 2*i <= h->len ) {
			pos = 2*i;
		}
		if ( pos == i || h->cmp( h->a[pos], h->a[i] ) <= 0 ) break;
		tmp = h->a[i], h->a[i] = h->a[pos], h->a[pos] = tmp;
	}
	return res;
}

void* heap_top(heap *h)
{
	assert( !heap_empty(h) );
	return h->a[1];
}