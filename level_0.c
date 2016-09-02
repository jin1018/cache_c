#include <stdlib.h>
#include <stdio.h>
#include "proj3.h"

// the two functions level_0 and level_0_opt performs the exact same task
// However, level_0_opt is more cache friendly. 


int level_0( int * B, int x, int y )
{
	if (!B) return -1; 
	
    int c, r; 

    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            B[ r*N + c ] = 2*(B[ r*N + c ] + 2);

    
    return  B[ x*N + y ];
}

/*
We want to visit B sequentially in the order:  B[0*N+0], B[0*N+1], .... B[0*N+1023], B[1*N+0],B[1*N+1],.....B[1023*N+1023],
*/

int level_0_opt( int * B, int x, int y )
{
	if (!B) return -1; 
	
     int c, r; 

    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            B[ c*N + r ] = 2*(B[ c*N + r ] + 2);

    
    return  B[ x*N + y ];
}
