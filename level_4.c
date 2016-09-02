#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// the two functions level_4 and level_4_opt performs the exact same task
// However, level_4_opt is more cache friendly. 


// Note: Data structures like linked lists are not very
// cache friendly (their nodes can be scattered all over
// the heap). The following method compacts the nodes of a linked 
// list into adjacent memory locations in an array and it also
// preserves the traditional linked list connections. 
// Your own code needs to accomplish the same. 
 

void level_4(node** head, int length)
{
    // malloc a contiguous block of memory on the heap
    // that is big enough for the entire list.
    node* new_list = malloc(sizeof(node) * length);

    // go through the list and make a copy of all the 
    // nodes and place them into the contiguous block in order
    node* n = *head;
    int i;
    for(i = 0 ; i < length ; ++i) {
        node copy = { n->value, NULL };
        new_list[i] = copy;
        n = n->next;
    }

    // go through the list again and "link" each node in 
    // the contiguous block to the next node in memory; 
    // free all the nodes in the old list
    n = *head;
    for(i = 0 ; i < length - 1 ; ++i) {
        // link each node in the new list
        new_list[i].next = &new_list[i+1];
        // free the old nodes
        node* free_me = n;
        n = n->next;
        free(free_me);
    }

    // free the last node of the old list
    free(n);

    // point head at the new packed list
    *head = new_list;
}

/*
COMMENTS:
There are two for loops, 
and in each of the for loops we need to access the same data, like new_list.
Accessing new_list in two different for loops is bad for both spacial locality and temporal locality
because you have to travel back and forth and you are not using the current variable again, when you could.

We can increase locality by merging the two for loops to access new_list more effectively.
*/

void level_4_opt(node** head, int length)
{
	
	// malloc a contiguous block of memory on the heap for the entire list.
	node* new_list = malloc(sizeof(node) * length);

	//copy the first node into new_list before the for loop
	node* n = *head;
	node copy = {n->value, NULL};
	new_list[0]=copy;
	
	node* oldNode=n;
	n=n->next;

	int i;
	for(i = 1 ; i < length ; ++i) {
        	node copy2 = { n->value, NULL };
        	new_list[i] = copy2;
		
		new_list[i-1].next = &new_list[i];

		// free the old nodes
       		node* free_me = oldNode;
        	oldNode = oldNode->next;
        	free(free_me);
	
       		n = n->next;
    }
	
	// free the last node of the old list
   	 free(n);

   	 // point head at the new packed list
   	 *head = new_list;



}



void addFront(data * s,  node ** head) {
	if (head == 0 ) return;
	if (s == 0 ) return; 
	
    //allocate memory for storing the node 
    node *n = ( node *)malloc(sizeof( node));
    //make sure that the memory was allocated,
    //if not, just quit
    if (n == NULL) return;
    n->value = *s;
    
    n->next = (*head);
    (*head) = n;
}


