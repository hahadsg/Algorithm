#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"
#include "src/kd_tree.h"

/* randomized select */
void test_randomized_select(int argc, char **argv);
/* kd_tree */
void test_kd_tree(int argc, char **argv);
void test_kd_tree_print(kd_node* kd_root);

int main(int argc, char **argv)
{
    test_kd_tree(argc, argv);
    return 0;
}

void test_kd_tree(int argc, char **argv) 
{
    double a[10][2] = {9,9,8,8,7,7,6,6,5,5,4,4,3,3,2,2,1,1,0,0};
    feature *features;
    kd_node *kd_root;
    int n = 10;
    int i, j;

    features = (feature*)malloc(n*sizeof(feature));
    for (i = 0; i < n; i++) {
        features[i].descr[0] = a[i][0];
        features[i].descr[1] = a[i][1];
        features[i].d = 2;
    }

    kd_root = kd_tree_build(features, n);
    test_kd_tree_print(kd_root);
    kd_tree_free(kd_root);
}

void test_kd_tree_print(kd_node* kd_root) 
{
    printf("n=%d,ki=%d,kv=%lf,leaf=%d\n",kd_root->n, kd_root->ki, kd_root->kv, kd_root->leaf);
    if (kd_root->left)
        test_kd_tree_print(kd_root->left);
    if (kd_root->right)
        test_kd_tree_print(kd_root->right);
}

void test_randomized_select(int argc, char **argv) 
{
    double a[10] = {9,8,7,6,5,4,3,2,1,0};
    double med;

    med = randomized_select(a, 10, 5);
    printf("med:%lf\n", med);
}