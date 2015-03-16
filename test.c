#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"

void test_randomized_select(int argc, char **argv);

int main(int argc, char **argv) {
    test_randomized_select(argc, argv);
	return 0;
}

void test_randomized_select(int argc, char **argv) {
	double a[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
	double med;
	med = randomized_select(a, 10, 5);
	printf("%lf\n", med);
}