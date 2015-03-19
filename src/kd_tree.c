#include <stdio.h>
#include <stdlib.h>

#include "kd_tree.h"
#include "randomized_select.h"

#define SQUARE(x) ((x)*(x))

void assign_split(point* points, int n, int d, int* split, double* value);
void partition_points(point* points, int n, int d, int split, double value);

/********************************************************************************/
/* build */
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
