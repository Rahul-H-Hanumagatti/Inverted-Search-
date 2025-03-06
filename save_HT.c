#include "inverted_search.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int save_HT(Hash *arr, char *file)
{
    FILE *fptr = fopen(file,"w");
    if(fptr == NULL)
    {
        printf("File opening failed\n");
        return FAILURE;
    }
    
    //fprintf(fptr,"#index;word;file_count;filename;word_count#\n");
    for(int i=0;i<28;i++)
    {
        if(arr[i].link == NULL)
          continue;
        else if(arr[i].link != NULL)
        {
            Main *temp = arr[i].link;
            while(temp != NULL)
            {
                //printf("#%d;%s;%d;",arr[i].index,temp->word,temp->file_count);
                fprintf(fptr, "#%d;%s;%d;",arr[i].index,temp->word,temp->file_count);
                
                Sub *temp2 = temp->sublink;
                if(temp->file_count == 1)
                    fprintf(fptr,"%s;%d;#\n",temp2->file_name,temp2->word_count);
                else
                {
                    while(temp2 != NULL)  // printing its respective sublink's details
                    {
                        fprintf(fptr,"%s;%d;",temp2->file_name,temp2->word_count);
        
                      temp2 = temp2->slink;  // to traverse to next subnode of that particular main node
                    }   
                     fprintf(fptr,"#\n");

                }

                temp = temp->mainlink; // to traverse to next main node
                

            }

        }
       
    }
    fclose(fptr);
    return SUCCESS;


}