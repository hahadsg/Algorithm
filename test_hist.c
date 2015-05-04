#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"
#include "src/kd_tree.h"
#include "src/queue.h"

/* randomized select */
void test_randomized_select(int argc, char **argv);
/* kd_tree */
void test_kd_tree(int argc, char **argv);
void test_kd_tree_print(kd_node* kd_root, int level, char c);
/* queue */
void test_queue(int argc, char **argv);
void test_queue_print(queue *q);
/* stack */
void test_stack(int argc, char **argv);
void test_stack_print(stack *a);
/* heap */
void test_heap(int argc, char **argv);
void test_heap_print(heap *h);

/********************************************************************************/
/* main */
/********************************************************************************/
int main(int argc, char **argv)
{
    return 0;
}

/********************************************************************************/
/* heap */
/********************************************************************************/
void test_heap(int argc, char **argv)
{
    int a[9] = {1,2,3,4,5,6,7,8,9};
    heap *h;
    int i, n = 9;

    h = heap_create(cmp_int);
    // test_heap_print(h);
    for (i = 0; i < n; i++) {
        heap_push(h, a+i);
        // test_heap_print(h);
    }
    test_heap_print(h);
    for (i = 0; i <= n; i++) {
        printf("pop : %d\n", *(int*)(heap_pop(h)));
        test_heap_print(h);
    }
}

void test_heap_print(heap *h)
{
    int i;
    printf("len: %d ; ml: %d\n", h->len, h->ml);
    for (i = 1; i <= h->len; i++) {
        printf("%d, ", *(int*)(h->a[i]));
    }
    printf("\n");
}

/********************************************************************************/
/* stack */
/********************************************************************************/
void test_stack(int argc, char **argv)
{
    stack *s;
    int data[3] = {1,2,3};
    int n = 3, i;

    s = stack_create();
    test_stack_print(s);
    for (i = 0; i < n; i++) {
        stack_push(s, (void*)(data+i) );
        test_stack_print(s);
    }
    for (i = 0; i < n+1; i++) {
        printf("top: %d\n", *(int*)stack_top(s));
        printf("pop: %d\n", *(int*)stack_pop(s));
        test_stack_print(s);
    }
}

void test_stack_print(stack *s)
{
    int i;
    printf("pos: %d ; len: %d ; a: %p\n", s->pos, s->len, s->a);
    for (i = 0; i < s->pos; i++) {
        printf("%d, ", *(int*)(s->a[i]));
    }
    printf("\n");
}

/********************************************************************************/
/* queue */
/********************************************************************************/
void test_queue(int argc, char **argv)
{
    queue *q;
    int data[3] = {1,2,3};
    int n = 3, i;

    q = queue_create();
    test_queue_print(q);
    for (i = 0; i < n; i++) {
        queue_push(q, (void*)(data+i) );
        test_queue_print(q);
    }
    for (i = 0; i < n+1; i++) {
        printf("top: %d\n", *(int*)queue_top(q));
        printf("pop: %d\n", *(int*)queue_pop(q));
        test_queue_print(q);
    }
}

void test_queue_print(queue *q)
{
    int i;
    printf("first: %d ; last: %d ; len: %d ; a: %p\n", q->first, q->last, q->len, q->a);
    for (i = q->first; i < q->last; i++) {
        printf("%d, ", *(int*)(q->a[i]));
    }
    printf("\n");
}

/********************************************************************************/
/* kd_tree */
/********************************************************************************/
void test_kd_tree(int argc, char **argv) 
{
    int n = 6;
    double a[6][2] = {{2,3}, {5,4}, {9,6}, {4,7}, {8,1}, {7,2}};
    point *points, p, res;
    double min_dist;
    kd_node *kd_root;
    int i, j;
    int d = 2;

    points = (point*)malloc(n*sizeof(point));
    for (i = 0; i < n; i++) {
        points[i].v[0] = a[i][0];
        points[i].v[1] = a[i][1];
    }

    // build
    kd_root = kd_tree_build(points, n, 2);
    printf("----- kd_tree(a) -----\n");
    test_kd_tree_print(kd_root, 1, 'h');

    // insert
    // p.v[0] = 5;
    // p.v[1] = 3;
    // kd_tree_insert(kd_root, &p, 2);
    // printf("----- kd_tree(a) -----\n");
    // test_kd_tree_print(kd_root, 1, 'h');

    // delete
    // kd_root = kd_tree_delete(kd_root, 2);
    // printf("----- kd_tree(a) -----\n");
    // test_kd_tree_print(kd_root, 1, 'h');

    // find closest
    p.v[0] = 6;
    p.v[1] = 5;
    min_dist = -1;
    kd_tree_find_closest(kd_root, &p, &res, &min_dist);
    printf("point(%lf, %lf) -> point(%lf, %lf), min_dist=%lf\n", p.v[0], p.v[1], res.v[0], res.v[1], min_dist);

    // free
    kd_tree_free(kd_root);
}

void test_kd_tree_print(kd_node* kd_root, int level, char c) 
{
    printf("lv:%d%c, point:(%lf, %lf), split=%d\n", level, c, kd_root->point.v[0], kd_root->point.v[1], kd_root->split);
    if (kd_root->left)
        test_kd_tree_print(kd_root->left, level+1, 'l');
    if (kd_root->right)
        test_kd_tree_print(kd_root->right, level+1, 'r');
}

/********************************************************************************/
/* randomized_select */
/********************************************************************************/
void test_randomized_select(int argc, char **argv) 
{
    double a[10] = {9,8,7,6,5,4,3,2,1,0};
    double med;

    med = randomized_select(a, 10, 5);
    printf("med:%lf\n", med);
}