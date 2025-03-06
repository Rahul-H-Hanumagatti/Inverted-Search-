#include "inverted_search.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int update_HT(Hash *arr, Slist **head, char *argv[], char *bk_file)
{
    FILE *fptr = fopen(bk_file,"r");
    if(fptr == NULL)
      return FAILURE;
    
    int index, filecount, wordcount;
    char filename[50], word[50];

    //reading from the file and storing back to the Hashtable to its particular index
    //printf("Hello\n");
    while(fscanf(fptr,"#%d;%[^;];%d;",&index,word,&filecount) > 0)
    { 
      //printf("Namskar\n");
      //printf("%d,%s,%d\n",index,word,filecount);

         Main *main = malloc(sizeof(Main));
         if(main == NULL)
           return FAILURE;

          strcpy(main->word,word);
          main->file_count = filecount;
          main->mainlink = NULL;
          main->sublink = NULL;
         //arr[index].link =  main;
          
         Sub *subhead = NULL;
         Sub *subtemp = NULL;
         for(int i=0;i<main->file_count;i++)
         {
           if(fscanf(fptr,"%[^;];%d;",filename,&wordcount)>0)
           {
            //printf("%s,%d\n",filename,wordcount);
             Sub *sub = malloc(sizeof(Sub));
             if(sub == NULL)
                return FAILURE;
              strcpy(sub->file_name,filename);
              sub->word_count = wordcount;
              sub->slink = NULL;

              // linking the subnode to main->sublink
              if(subhead == NULL)
                 subhead = sub;  // is subhead = NULL means directly updating main->link;
              else
                subtemp->slink = sub;  // else updating to previous subnode->slink
              
              subtemp = sub;  // subtemp pointer is used to store the previous subnode
           }
         }

         main->sublink = subhead;  // linking the subnode to mainnode
         //fscanf(fptr,"#\n");

       if(arr[index].link == NULL)  // if that index is empty
         arr[index].link = main;
       else  // if not empty traversing till last node and inserting
       {
         Main *temp = arr[index].link;
         while(temp->mainlink != NULL)
         {
          temp = temp->mainlink;
         }
         temp->mainlink = main;
       }
      
       fscanf(fptr,"#\n");
    }
    //printf("Hi\n");
    fclose(fptr);
    printf("Updated Linked list of file names is\n");
    print_list(*head);
    return SUCCESS;

}



int validate_BKfile(char *bk_file)
{
    
    // 1. To Check file extension .txt
		char *s1 = strstr(bk_file,".");
    if(s1 == NULL)
		{
			printf("%s dont have .txt extension\n",bk_file);
			return FAILURE;
		}
		if(strcmp(s1,".txt") != 0)
		{
       printf("%s dont have .txt extension\n",bk_file);
		    return FAILURE;
		}

    // 2. To check whether the file availability
		FILE *fptr = fopen(bk_file,"r");
    if(fptr == NULL)
    {
        printf("Backup file not available\n");
        return FAILURE;
    }
		// 3. To check the file content
		
		fseek(fptr,0,SEEK_END);   // to set the fptr at last
		long size = ftell(fptr); // it tells the size of the file
		rewind(fptr);  // making fptr to point back to the first position

		if(size < 0)
		{
		   printf("%s file content not available\n",bk_file);
       return FAILURE;
		} 
		
    
    // 4 . reading 1st character of the file
    //fseek(fptr,0,SEEK_SET);
    char ch = fgetc(fptr);
    if(ch == EOF)
    {
      printf("File is empty\n");
      return FAILURE;
    }
    else
      printf("1st Character is %c\n",ch);

    // 5. reading the last character of the file by setting the fptr to end -2
    fseek(fptr,-2,SEEK_END);
    char c = fgetc(fptr); 
    if(c == EOF)
    {
      printf("File is empty\n");
      return FAILURE;
    }
    else
      printf("Last Character is %c\n",c);
     
     rewind(fptr);
     fclose(fptr);
     if(ch == '#' && c == '#')
        return SUCCESS;
     else
        return FAILURE;
           
}