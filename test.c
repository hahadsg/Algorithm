#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"
#include "src/kd_tree.h"
#include "src/stack.h"

/* kd_tree */
void test_kd_tree(int argc, char **argv);
void test_kd_tree_print(kd_node* kd_root, int level, char c);

/********************************************************************************/
/* main */
/********************************************************************************/
int main(int argc, char **argv)
{
    test_kd_tree(argc, argv);
    return 0;
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


