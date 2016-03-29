#include <stdio.h>

#define MAX 10000

/* Initialize A and x, assign y = 0 */
double A[MAX][MAX], x[MAX], y[MAX];
long int i,j;

int main(int argc, char *argv[]) {

	y[0]=0;
	
	/* First pair of loops*/
	for( i=0; i < MAX; i++)
		for ( j=0; j < MAX; j++)
			y[i] += A[i][j] * x[j];
	
	/* Assign y = 0 */
	
	/* Second pair of loops 	
	for(j = 0; j < MAX; j ++)
		for( i = 0; i < MAX; i ++)
			y[i] += A[i][j] * x[j];
*/
	return 0;
}

