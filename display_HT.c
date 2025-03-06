#include "inverted_search.h"
#include<stdio.h>

void display_HT(Hash *arr, int size)
{
    int flag =0;
    for(int i=0;i<size;i++)
    {
        if(arr[i].link != NULL)
        {
            flag =1;
            break;
        }
    }

    if(flag == 1)
    {
        printf("\n-------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-15s | %-10s | %-20s | %-10s |\n", "Index", "Word", "File Count", "Filename", "Word Count");
        printf("-------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<size;i++)
    {
        if(arr[i].link == NULL)
          continue;
        else if(arr[i].link != NULL)
        {
            Main *temp = arr[i].link;
            while(temp != NULL)
            {
                //printf("  %d            %s                %d         ",arr[i].index,temp->word,temp->file_count);
                 printf("| %-5d | %-15s | %-10d | ", arr[i].index, temp->word, temp->file_count);
                
                
                Sub *temp2 = temp->sublink;
                if(temp->file_count == 1)
                    printf("%-20s | %-10d |\n", temp2->file_name, temp2->word_count);
                //printf("      %s               %d \n",temp2->file_name,temp2->word_count);
                else
                {
                    while(temp2 != NULL)  // printing its respective sublink's details
                    {
                        printf("%-20s | %-10d |\n", temp2->file_name, temp2->word_count);
                        //printf("%s          %d \n",temp2->file_name,temp2->word_count);
                        if(temp2->slink != NULL)
                             printf("|       |                 |            | ");
                           // printf("                                            ");
        
                      temp2 = temp2->slink;  // to traverse to next subnode of that particular main node
                    }   

                }
                //printf("---------------------------------------------------------------------------------");
                  printf("-------------------------------------------------------------------------------------------------------------\n");
                temp = temp->mainlink; // to traverse to next main node

            }
        }
    }
    }
    else
        printf("Database is empty\n");
    
}