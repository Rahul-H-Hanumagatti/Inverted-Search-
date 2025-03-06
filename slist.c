#include<stdio.h>
#include "inverted_search.h"
#include<string.h>
#include<stdlib.h>

int sl_delete_element(Slist **head, char *name)
{
    if(*head == NULL)
    {
        printf("List is empty\n");
        return FAILURE;
    }

    Slist *temp = *head;
    Slist *prev = NULL;

    while(temp != NULL)
    {
        if(strcmp(temp->name ,name)==0) // if given data matches the temp->data i.e, node's data
        {
            if(prev == NULL) // deletion of 1st node
            {  
              *head = temp->link; // updating head with temp->link part so that head will point to next node by breaking the connection with 1st node
              free(temp); // deallocation of memory pointed by temp i.e, 1st node
              printf("Node deleted successfully\n");
              return SUCCESS;
            }

          prev->link = temp->link; // if not the first node the updating the prev->link with temp->link and establishing the connection with previous node and next node
          free(temp); // deallocation of memory pointed by temp i.e, current node
          printf("Node deleted successfully\n");
          return SUCCESS;
        }

       prev = temp; // storing temp in prev to keep track of current node
       temp = temp->link; // updating temp with temp->link to point to next node
        
    }
    return WORD_NOT_FOUND; // if data is not found means

}

int insert_at_last(Slist **head, char *name)
{
   Slist *new_node = malloc(sizeof(Slist)); // 12 bytes + 4 bytes of padding total of 16 bytes
   if(new_node == NULL)
     return FAILURE;
   
   strcpy(new_node->name ,name);
   new_node->link = NULL;

   if(*head == NULL)
   {
     *head = new_node;
      printf("Data inserted at last successfully\n");
      return SUCCESS;
   }

   // if we use *head directly for traversing we will loose the 1st node's data, so we use temp 
   Slist *temp = *head; // storing head's value i.e, 1st node's address in temp. i.e, now temp points to 1st node
   while(temp->link != NULL) // running the loop till temp->link == NULL
   {
     temp = temp->link; // updating temp with temp->link, so that it will point to next node
   }

   temp->link = new_node; // at last updating temp->link part with new_node's address i.e, inserting at last 
   printf("Data inserted at last successfully\n");
   return SUCCESS;
}