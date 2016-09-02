#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// the two functions level_2 and level_2_opt performs the exact same task
// However, level_2_opt is more cache friendly. 

// Note: you may observe that this function performs "useless" looping
// over an array of structures that are all filled with zero bits. 
// Your task is not to remove that "useless" code, but modify it 
// so that it is more cache friendly. 
// You also should not be removing any parts of the structures.
//
// (In an actual application, the structures would be populated with
// real data and the loop would be computing some real results.) 


char * level_2()
{
    data_2 * B = (data_2 * ) calloc( LARGER, sizeof(data_2) ) ;
	if (!B) return 0; 
	double sum_f = 0.0;
	double sum_n = 0; 
	char * sum_c = (char*) malloc( (2*LARGER + 1) * sizeof(char) );	
	sum_c[2*LARGER] = '\0'; 

    int i; 

	for(i = 0; i < LARGER; i++){
		sum_f += B[i].f1 + B[i].f2; 
		sum_n += B[i].n1 + B[i].n2; 
		sum_c[2*i] = B[i].c1;
		sum_c[2*i+1] = B[i].c2;
	}
	
	
    free(B); 
    return sum_c;
}

/*
COMMENTS:
In each for-loop interation, you have to access sum_f, sum_n, sum_c again and again.
This does not have good temporal locality.
We can improve temporal locality by first completing the computation for  sum_f,
then move on the complete computing for sum_n, 
then sum_c.
*/

char * level_2_opt()
{	
	// create the array of structures (same or equivalent to the one
	// in the function above: 

	// DO NOT modify the following declarations 
	double sum_f = 0.0;
	double sum_n = 0; 
	char * sum_c = (char*) malloc( (2*LARGER + 1) * sizeof(char) );	
	sum_c[2*LARGER] = '\0'; 	
	
	// enter your code here (make sure to free the array B once 
	// before returning) 

  	 data_2 * B = (data_2 * ) calloc( LARGER, sizeof(data_2) ) ;

	int i;
	for(i = 0; i < LARGER; i++){
		sum_f += B[i].f1 + B[i].f2; 
	}//improve temporal locality for variable sum_f

	for(i= 0; i < LARGER; i++){
		sum_n += B[i].n1 + B[i].n2; 
	}//improve temporal locality for variable sum_n

	for(i = 0; i < LARGER; i++){
		sum_c[2*i] = B[i].c1;
		sum_c[2*i+1] = B[i].c2;
	}//improve temporal locality for array sum_c
	
	free(B);
    
	//DO NOT modify the rest of this function 
    return sum_c;
}

