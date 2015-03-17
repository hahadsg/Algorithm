#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"
#include "src/kd_tree.h"

/* randomized select */
void test_randomized_select(int argc, char **argv);
/* kd_tree */
void test_kd_tree(int argc, char **argv);
void test_kd_tree_print(kd_node* kd_root, int level);

int main(int argc, char **argv)
{
    test_kd_tree(argc, argv);
    return 0;
}

void test_kd_tree(int argc, char **argv) 
{
    int n = 6;
    double a[6][2] = {{2,3}, {5,4}, {9,6}, {4,7}, {8,1}, {7,2}};
    feature *features;
    kd_node *kd_root;
    int i, j;

    features = (feature*)malloc(n*sizeof(feature));
    for (i = 0; i < n; i++) {
        features[i].descr[0] = a[i][0];
        features[i].descr[1] = a[i][1];
        features[i].d = 2;
    }

    kd_root = kd_tree_build(features, n);
    test_kd_tree_print(kd_root, 1);
    kd_tree_free(kd_root);
}

void test_kd_tree_print(kd_node* kd_root, int level) 
{
    feature feature;
    feature = kd_root->features[kd_root->n/2];
    printf("lv:%d, point:(%lf, %lf)\n", level, feature.descr[0], feature.descr[1]);
    // printf("n=%d,ki=%d,kv=%lf,leaf=%d\n",kd_root->n, kd_root->ki, kd_root->kv, kd_root->leaf);
    if (kd_root->left)
        test_kd_tree_print(kd_root->left, level+1);
    if (kd_root->right)
        test_kd_tree_print(kd_root->right, level+1);
}

void test_randomized_select(int argc, char **argv) 
{
    double a[10] = {9,8,7,6,5,4,3,2,1,0};
    double med;

    med = randomized_select(a, 10, 5);
    printf("med:%lf\n", med);
}