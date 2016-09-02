#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// the two functions level_3 and level_3_opt performs the exact same task
// However, level_3_opt is more cache friendly. 
//
// Note: your function needs to compute the entire matrix C,
// not only its x entry. 

long level_3(long * B, long * A, int x)
{
	long * C = (long * ) calloc (N,sizeof(long) );
	if (!C) return 0; 
	
    int c, r; 

    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            C[ r ] = B[ r*N + c ] + A[ c*N + r ] ;
	
	long ret = C[x];
	free (C); C = 0; 
    return ret;
}

/*
COMMENTS:
Since we are using" = " instead of " +=  " for " C[ r ] = B[ r*N + c ] + A[ c*N + r ] ;" , C is not really considered as a matrix
In that case, for each iteration on c, C[0], C[1], ....C[N-1] is overwritten over and over again for r N times.
This does not have good locality because we have to access C, B and A at each iteration of r.
Since the output only depends on the last iteration on c, we just need the part when c == N-1 (the last iteration in the outer for loop)
By deleting the unneccessary code, we do not have to visit and access the unneccesary variables as oftern,
so it improves spacial locality.
Especially, in the original code, we do not access the elements of A and B in sequential order. 
For instance, we first get B[0*N+0], then B[1*N+0], then B[2*N+0] and so on. (note that N==1024)
Eliminating this part would greatly improve spacial locality because we do not have to jump from place to place,
and would still get the same output.
*/


long level_3_opt(long * B, long * A, int x)
{
	long * C = (long * ) calloc (N,sizeof(long) );
	if (!C) return 0; 

	int i;
	for(i = 0; i < N; i++){
           	C[ i ] = B[ i*N + (N-1) ] + A[ (N-1)*N + i ] ;

	}


	//DO NOT modify the rest of this function 
	long ret = C[x];
	free (C); C = 0; 
    return ret;
}



