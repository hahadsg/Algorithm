#ifndef __KD_TREE_H
#define __KD_TREE_H

typedef struct point {
    double v[2]; // 数据
} point;

typedef struct kd_node {
    int split;                    // 以ki维切割
    point point;                  // 特征
    struct kd_node *right, *left; // 左右子树

} kd_node;


kd_node* kd_tree_build(point* points, int n, int d);
void kd_tree_free(kd_node* kd_root);

#endif