#include "inverted_search.h"
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int create_database(Hash *arr, Slist *head)
{
    Slist *temp = head;
    int count =0;

    while(temp != NULL)
    {
        FILE *fptr = fopen(temp->name,"r");  // declaring file pointer and opening that particular node's file in reading mode
        if(fptr == NULL)
          return FAILURE;
        
        //printf("Reading file %s\n",temp->name);
        char word[50] ={'0'};  // to store each word
        while(fscanf(fptr,"%s",word) > 0)
        {
          if((strcmp(word," ") == 0) || (strcmp(word,"\n")==0))
             continue;
           //printf("Word is %s\n",word);
          
           int i = tolower(word[0]);  // converting to lowercase
           //printf("1st letter of %s is %c\n",word,i);
           int flag_main = 0;  // flag to create main node
           int index; 

           if(i>= 48 && i<=57)
               index =26;
           else if((i>= 32 && i<= 47) || (i>= 58 && i<=64) || (i>= 91 && i<=96) || (i>=123 && i<=126))
               index = 27;
           else  // Hash function
                index = i % 97;   // finding the index to which the word should be added

           //printf("index is %d\n",index);
           
           if(arr[index].link == NULL)   // 1st case , link = NULL, creating mainnode and subnode and establishing connection with hashtable
           {
             // creation of main node
              Main *main = malloc(sizeof(Main));
              if(main == NULL)
                return FAILURE;
              main->file_count = 1;
              strcpy(main->word,word);
              main->mainlink = NULL;
              main->sublink = NULL;

              // creation of subnode
              Sub *sub = malloc(sizeof(Sub));
              if(sub == NULL)
                return FAILURE;
              
              sub->word_count =1;
              strcpy(sub->file_name,temp->name);
              sub->slink = NULL;

              main->sublink = sub;  // connecting sub to main node
              arr[index].link = main;  // connecting main node to hash table
              //printf("Added to Hashtable Successfully for case 1\n");
              //return SUCCESS;
           }
           else if(arr[index].link != NULL)
           {
             Main *temp2 = arr[index].link;
             Main *temp2_prev = temp2;
             int flag_sub=0;
             while(temp2 != NULL)  // traversing till last node
             {
                if(strcmp(temp2->word,word) ==0)  // 3rd case, if words are same
                {
                  
                  flag_main =1;  // to indicate no main node is created , just sub nodes are created and updated
                  //printf("---Yes---\n");
                  Sub *temp3 = temp2->sublink;
                  Sub *prev = NULL;
                  // 2nd case, if word and filename both are same
                  while(temp3 != NULL)
                  { 
                       // 2nd case, if both word and filename both are same means just update its word count
                  //printf("\n----%s------%s------\n",temp->name,temp3->file_name);
                    if(strcmp(temp->name,temp3->file_name) == 0)  // if main node's -> subnode's->filename and current file name is same means just increementing word count
                    {
                      temp3->word_count++;  // increementing subnode's word count
                      flag_sub =1;
                     // printf("Added to Hashtable Successfully for case 2, both word and files are same , so just updated word count in its sub node\n");
                      break;
                    }
                      prev = temp3;  // storing the previous node's address
                      temp3 = temp3->slink;  // traversing to next subnode

                  }
                  if(flag_sub == 1)  // to check sub node is created or not
                     break;
                  else  
                  { 
                       //3rd case, if only words are same
                        // creation of subnode
                       Sub *sub = malloc(sizeof(Sub));
                       if(sub == NULL)
                         return FAILURE;
              
                        sub->word_count =1;
                       strcpy(sub->file_name,temp->name);  // copying filename to file_name of subnode
                       sub->slink = NULL;
                       
                        prev->slink = sub; // connecting subnode to previous subnode
                        
                       temp2->file_count++;  // increementing filecount of mainnode
                       //printf("Added to Hashtable Successfully for case 3, only words are same so  created new subnode linked it to previous sub node and updated file count\n");
                  } 
                  break;
                }
                
                temp2_prev= temp2;  // saving previous node address in temp2_prev
                temp2 = temp2->mainlink;
             }
             // 4th case, creation whole new block;
             // creation of main node
            // printf("\n--------%s-------\n",word);
             if(flag_main==0)  // to check whether the main node of this word id created or not
             {
              Main *main = malloc(sizeof(Main));
              if(main == NULL)
                return FAILURE;
              main->file_count = 1;
              strcpy(main->word,word);
              main->mainlink = NULL;
              main->sublink = NULL;

              // creation of subnode
              Sub *sub = malloc(sizeof(Sub));
              if(sub == NULL)
                return FAILURE;
              
              sub->word_count =1;
              strcpy(sub->file_name,temp->name);
              sub->slink = NULL;
              
              main->sublink = sub;  // connecting sub to main node
              temp2_prev->mainlink = main;  // connecting main node to hash table
              
              // printf("Added to Hashtable Successfully for case 4 i.e, words are different so created main node and sub node and linked main node to previous main node\n");
             }
           } 
        
        }

        fclose(fptr);  // closing that particular node->named file
        temp = temp->link;  // moving to next node's file name
        //printf("Moving to next file\n");
    }
    //printf("Completed Database Successfully\n");
    return SUCCESS;
}