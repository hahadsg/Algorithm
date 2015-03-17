#include <stdio.h>
#include <stdlib.h>

#include "kd_tree.h"
#include "randomized_select.h"

#define SQUARE(x) ((x)*(x))

kd_node* init_kd_node(feature* features, int n);
void expand_kd_tree(kd_node* kd_root);
void assign_partition_key(kd_node* kd_root);
void partition_features(kd_node* kd_root);

/********************************************************************************/
/* build */
/********************************************************************************/
kd_node* kd_tree_build(feature* features, int n)
{
    kd_node *kd_root;

    if ( !features || n <= 0 )
        return NULL;

    kd_root = init_kd_node(features, n);
    expand_kd_tree(kd_root);

    return kd_root;
}

kd_node* init_kd_node(feature* features, int n)
{
    kd_node *kd_root;

    kd_root = (kd_node*)malloc(sizeof(kd_node));
    kd_root->ki = -1;
    kd_root->kv = 0;
    kd_root->leaf = 0;
    kd_root->n = n;
    kd_root->features = features;
    kd_root->right = kd_root->left = NULL;

    return kd_root;
}

void expand_kd_tree(kd_node* kd_root)
{
    if ( kd_root->n == 1 || kd_root->n == 0 ) {
        kd_root->leaf = 1;
        return ;
    }

    assign_partition_key(kd_root);
    partition_features(kd_root);

    if (kd_root->left)
        expand_kd_tree(kd_root->left);
    if (kd_root->right)
        expand_kd_tree(kd_root->right);
}

void assign_partition_key(kd_node* kd_root)
{
    int i, j, n, d;
    int ki, kv;
    double mean, var, max_var = 0;
    feature *features;
    double *tmp;

    n = kd_root->n;
    features = kd_root->features;
    d = features[0].d;

    for (j = 0; j < d; j++) {
        mean = var = 0;
        /* mean */
        for (i = 0; i < n; i++) {
            mean += features[i].descr[j];
        }
        mean /= n;
        /* variance */
        for (i = 0; i < n; i++) {
            var += SQUARE(features[i].descr[j] - mean);
        }
        var /= n;
        /* ki */
        if (max_var < var) {
            max_var = var;
            ki = j;
        }
    }

    /* kv */
    tmp = (double*)malloc(n*sizeof(double));
    for (i = 0; i < n; i++) {
        tmp[i] = features[i].descr[ki];
    }
    kv = randomized_select(tmp, n, n/2);
    free(tmp);

    kd_root->ki = ki;
    kd_root->kv = kv;
}

void partition_features(kd_node* kd_root)
{
    int i, j, n, med, ki, p;
    double kv;
    feature tmp, *features;

    features = kd_root->features;
    n = kd_root->n;
    ki = kd_root->ki;
    kv = kd_root->kv;

    for (i = 0, j = -1 ; i < n; i++) {
        if (features[i].descr[ki] <= kv) {
            j++;
            tmp = features[i];
            features[i] = features[j];
            features[j] = tmp;
            if (features[j].descr[ki] == kv)
                p = j;
        }
    }

    tmp = features[p];
    features[p] = features[j];
    features[j] = tmp;
    
    if (j)
        kd_root->left = init_kd_node(features, j);
    if (n-j-1)
        kd_root->right = init_kd_node(features+j+1, n-j-1);
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
