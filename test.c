#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "src/randomized_select.h"
#include "src/kd_tree.h"
#include "src/heap.h"

/* cmp */
int cmp_int(const void *a, const void *b); 

/********************************************************************************/
/* main */
/********************************************************************************/
int main(int argc, char **argv)
{
    // test(argc, argv);
    return 0;
}

/********************************************************************************/
/* cmp */
/********************************************************************************/
int cmp_int(const void *a, const void *b) 
{
    return *(int*)a - *(int*)b;
}


