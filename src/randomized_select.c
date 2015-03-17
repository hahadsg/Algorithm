 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>

 #include "randomized_select.h"

void static insertion_sort(double *a, int n);
int static partition_array(double *a, int n, double x);

/* 
 * 返回长度n的数组a第r个数据地址
 */
double randomized_select(double* a, int n, int r) 
{
    int i, j;
    int gr, gr_c, rem;
    double *tmp, med;

    /* 递归回溯 */
    if (n == 1)
        return a[0];

    /* 划分成5份 分别进行插入排序 选取每份的中位数 */
    gr = n / 5;
    gr_c = ceil(n / 5.0);
    rem = n % 5;
    for (i = 0, tmp = a; i < gr; i++, tmp+=5) {
        insertion_sort(tmp, 5);
    }
    insertion_sort(tmp, rem);
    tmp = (double*)malloc(gr_c * sizeof(double));
    for (i = 0, j = 2; i < gr; i++, j+=5) {
        tmp[i] = a[j];
    }
    if (rem) {
        tmp[i] = a[n - 1 - rem/2];
    }
    med = randomized_select(tmp, gr_c, (gr-1)/2);
    free(tmp);

    /* 分割数组 */
    j = partition_array(a, n, med);
    if (j == r) {
        return med;
    } else if (j < r) {
        return randomized_select(a+j+1, n-j, r-j);
    } else {
        return randomized_select(a, j, r);
    }
}

/*
 * 插入排序
 */
void static insertion_sort(double *a, int n)
{
    int i, j;
    double tmp;
    for (i = 1; i < n; i++) {
        tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
            a[j+1] = a[j];
        }
        a[j+1] = tmp;
    }        
}

/*
 * 分割数组 左边比x小 右边比x大
 */
int static partition_array(double *a, int n, double x)
{
    int i, j, pos;
    double tmp;
    for (i = 0, j = 0; i < n; i++) {
        if (a[i] <= x) {
            tmp = a[i];
            a[i] = a[j];
            a[j++] = tmp;
            if (a[i] == x) 
                pos = j;
        }
    }
    a[pos] = a[j-1];
    a[j-1] = x;
    return j-1;
}