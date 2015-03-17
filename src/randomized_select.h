#ifndef __RANDOMIZED_SELECT_H
#define __RANDOMIZED_SELECT_H

/*
 * 由n个不同的数据构成的集合中选择第i个顺序统计量
 * 分治
 * 借助中位数进行优化处理
 *
 * 最坏运行时间O(n)
 */
double randomized_select(double* a, int n, int r);

#endif

