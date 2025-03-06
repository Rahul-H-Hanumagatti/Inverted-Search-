#include<stdio.h>
#include "inverted_search.h"

void print_list(Slist *head)
{
    if(head == NULL)
    {
        printf("list is empty\n");
    }
    else
    {
        printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%s -> ", head -> name);

		    /* Travering in forward direction */
		    head = head -> link;
	    }
    	printf(" NULL\n");

    } 
       
}