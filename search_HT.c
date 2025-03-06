#include<stdio.h>
#include "inverted_search.h"
#include<ctype.h>
#include<string.h>

int search_HT(Hash *arr, char *word)
{
    //printf("Word is %s\n",word);
          
    int i = tolower(word[0]);  // converting to lowercase
    //printf("1st letter of %s is %c\n",word,i);
           
    int index; 

    if(i>= 48 && i<=57)
        index =26;
    else if((i>= 32 && i<= 47) || (i>= 58 && i<=64) || (i>= 91 && i<=96) || (i>=123 && i<=126))
        index = 27;
    else  // Hash function
        index = i % 97;   // finding the index to which the word should be added

    //printf("index is %d\n",index);

    if(arr[index].link == NULL)
    {
        return WORD_NOT_FOUND;
    }

    Main *temp = arr[index].link;  // for traversal till last node
    
    while(temp != NULL)
    {
        if(strcmp(temp->word,word) == 0)
        {
            printf("Word %s is present in %d files\n",temp->word,temp->file_count);
            Sub *temp2 = temp->sublink;
            while(temp2 != NULL)
            {
                printf("In file %s %d times\n",temp2->file_name,temp2->word_count);
                temp2 = temp2->slink;
            }
          
           return SUCCESS;
        }
        temp = temp->mainlink;   // traverse till last node
    }

    return WORD_NOT_FOUND;

}