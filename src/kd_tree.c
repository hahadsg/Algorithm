#include <stdio.h>
#include <stdlib.h>

#include "kd_tree.h"
#include "randomized_select.h"

#define SQUARE(x) ((x)*(x))

void assign_split(point* points, int n, int d, int* split, double* value);
void partition_points(point* points, int n, int d, int split, double value);

/********************************************************************************/
/* build */
/* O(k*n*logn) */
/********************************************************************************/
kd_node* kd_tree_build(point* points, int n, int d)
{
    kd_node *kd_root;
    int split = -1;
    double value;

    if ( n <= 0 )
        return NULL;

    kd_root = (kd_node*)malloc(sizeof(kd_node));
    assign_split(points, n, d, &split, &value);
    partition_points(points, n, d, split, value);

    kd_root->point = points[n/2];
    kd_root->split = split;
    kd_root->left = kd_tree_build(points, n/2, d);
    kd_root->right = kd_tree_build(points + n/2 + 1, n - n/2 - 1, d);

    return kd_root;
}

void assign_split(point* points, int n, int d, int* split, double* value)
{
    int i, j;
    double mean, var, max_var = -1;
    double *tmp;

    for (j = 0; j < d; j++) {
        mean = var = 0;
        /* mean */
        for (i = 0; i < n; i++) {
            mean += points[i].v[j];
        }
        mean /= n;
        /* variance */
        for (i = 0; i < n; i++) {
            var += SQUARE(points[i].v[j] - mean);
        }
        var /= n;
        /* split */
        if (max_var < var) {
            max_var = var;
            *split = j;
        }
    }

    /* value */
    tmp = (double*)malloc(n*sizeof(double));
    for (i = 0; i < n; i++) {
        tmp[i] = points[i].v[*split];
    }
    *value = randomized_select(tmp, n, n/2);
    free(tmp);
}

void partition_points(point* points, int n, int d, int split, double value)
{
    int i, j, med, p;
    point tmp;

    for (i = 0, j = -1 ; i < n; i++) {
        if (points[i].v[split] <= value) {
            j++;
            tmp = points[i];
            points[i] = points[j];
            points[j] = tmp;
            if (points[j].v[split] == value)
                p = j;
        }
    }

    tmp = points[p];
    points[p] = points[j];
    points[j] = tmp;
}

/********************************************************************************/
/* free */
/********************************************************************************/
void kd_tree_free(kd_node* kd_root)
{
    if (kd_root->left)
        kd_tree_free(kd_root->left);
    if (kd_root->right)
        kd_tree_free(kd_root->right);
    free(kd_root);
}

/********************************************************************************/
/* insert */
/* O(n) */
/********************************************************************************/
void kd_tree_insert(kd_node* kd_root, point* p, int d)
{
    kd_node *node, **turn_node;
    point *points;
    int split;
    double value;

    printf("point:(%lf, %lf), split=%d\n", kd_root->point.v[0], kd_root->point.v[1], kd_root->split);

    if ( kd_root == NULL ) { // 树为空
        kd_root = (kd_node*)malloc(sizeof(kd_node));
        kd_root->point = *p;
        kd_root->split = 0;
        kd_root->left = kd_root->right = NULL;
        return ;
    }

    split = kd_root->split;

    if (kd_root->left == NULL && kd_root->right == NULL) { // 如果是叶子节点 调整其split
        points = (point*)malloc(2 * sizeof(point));
        points[0] = kd_root->point;
        points[1] = *p;
        assign_split(points, 2, d, &split, &value);
        kd_root->split = split;
    }

    if (p->v[split] < kd_root->point.v[split]) {
        turn_node = &(kd_root->left);
    } else {
        turn_node = &(kd_root->right);
    }

    if ( (*turn_node) == NULL ) {
        node = (kd_node*)malloc(sizeof(kd_node));
        node->split = 0;
        node->point = *p;
        node->left = node->right = NULL;
        *turn_node = node;
    } else {
        kd_tree_insert(*turn_node, p, d);
    }
}

