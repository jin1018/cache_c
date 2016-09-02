  
#include <stdlib.h>
#include <stdio.h>

#include "proj3.h"

// the two functions level_1 and level_1_opt performs the exact same task
// However, level_1_opt is more cache friendly.


double level_1(double * B, double * A, int x, int y )
{	
    int i, j; 

    for(i = 0; i < LARGE; i++)
        for(j = 0; j < SMALL; j++){
            A[ i ] = A[i] + B[  j*LARGE + i ] ;
		}

    return A[x+y];
}

/*
COMMENTS:
variable LARGE ==1024, SMALL == 64
In the original code, the outer loop iterates many more times than the inner loop.
The code that modifies the data uses both variables from the outer loop and inner loop.
The variable in the inner loop has closer in the cache.
Instead of reaching the further variables 64 times reaching the closer variables 1024 times,
we should reach for the closer variables1024 times and reach for the further variables 64 times.
*/

double level_1_opt(double * B, double * A, int x, int y )
{	
	int i,j;

	for(j = 0; j < SMALL; j++)
		for(i = 0; i < LARGE; i++){
			A[ i ] = A[i] + B[  j*LARGE + i ] ;
		}


	//DO NOT modify the rest of this function 
    return A[x+y];
}
