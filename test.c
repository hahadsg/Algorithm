#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "src/randomized_select.h"

// double rank_select( double* array, int n, int r );
// void insertion_sort( double* array, int n );
// int partition_array( double* array, int n, double pivot );

int main(int argc, char **argv) {
	double a[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
	double med;

	med = randomized_select(a, 10, 5);

	printf("\n%lf\n", med);

	return 0;
}

// double rank_select( double* array, int n, int r )
// {
// 	printf("n:%d,r:%d\n",n,r);
// 	double* tmp, med;
// 	int gr_5, gr_tot, rem_elts, i, j;
// 	/* base case */
// 	if( n == 1 )
// 		return array[0];
// 	/* divide array into groups of 5 and sort them */
// 	gr_5 = n / 5;
// 	gr_tot = ceil( n / 5.0 );
// 	rem_elts = n % 5;
// 	tmp = array;
// 	for( i = 0; i < gr_5; i++ )
// 	{
// 		insertion_sort( tmp, 5 );
// 		tmp += 5;
// 	}
// 	insertion_sort( tmp, rem_elts );
// 	/* recursively find the median of the medians of the groups of 5 */
// 	tmp = calloc( gr_tot, sizeof( double ) );
// 	for( i = 0, j = 2; i < gr_5; i++, j += 5 )
// 		tmp[i] = array[j];
// 	if( rem_elts )
// 		tmp[i++] = array[n - 1 - rem_elts/2];
// 	med = rank_select( tmp, i, ( i - 1 ) / 2 );
// 	printf("med:%lf\n", med);
// 	free( tmp );
// 	 partition around median of medians and recursively select if necessary 
// 	j = partition_array( array, n, med );
// 	printf("j:%d\n\n", j);
// 	if( r == j )
// 		return med;
// 	else if( r < j )
// 		return rank_select( array, j, r );
// 	else
// 	{
// 		array += j+1;
// 		return rank_select( array, ( n - j - 1 ), ( r - j - 1 ) );
// 	}
// }

// void insertion_sort( double* array, int n )
// {
// 	double k;
// 	int i, j;
// 	for( i = 1; i < n; i++ )
// 	{
// 		k = array[i];
// 		j = i-1;
// 		while( j >= 0 && array[j] > k )
// 		{
// 			array[j+1] = array[j];
// 			j -= 1;
// 		}
// 		array[j+1] = k;
// 	}
// }

// int partition_array( double* array, int n, double pivot )
// {
// 	double tmp;
// 	int p, i, j;
// 	i = -1;
// 	for( j = 0; j < n; j++ )
// 		if( array[j] <= pivot )
// 		{
// 			tmp = array[++i];
// 			array[i] = array[j];
// 			array[j] = tmp;
// 			if( array[i] == pivot )
// 				p = i;
// 		}
// 	array[p] = array[i];
// 	array[i] = pivot;
// 	return i;
// }
