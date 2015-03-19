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
    point *points;
    kd_node *kd_root;
    int i, j;

    points = (point*)malloc(n*sizeof(point));
    for (i = 0; i < n; i++) {
        points[i].v[0] = a[i][0];
        points[i].v[1] = a[i][1];
    }

    kd_root = kd_tree_build(points, n, 2);
    test_kd_tree_print(kd_root, 1);
    kd_tree_free(kd_root);
}

void test_kd_tree_print(kd_node* kd_root, int level) 
{
    printf("lv:%d, point:(%lf, %lf), split=%d\n", level, kd_root->point.v[0], kd_root->point.v[1], kd_root->split);
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