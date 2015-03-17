#ifndef __KD_TREE_H
#define __KD_TREE_H

typedef struct feature {
    int d; // 维数
    double descr[2];        // 数据
} feature;

typedef struct kd_node {
    int ki;                      // 以ki维切割
    double kv;                   // ki维的中位数
    int leaf;                    // 是否叶子节点
    feature *features;           // 特征
    int n;                       // 特征个数
    struct kd_node *right, *left; // 左右子树

} kd_node;

kd_node* kd_tree_build(feature* features, int n);
void kd_tree_free(kd_node* kd_root);

#endif