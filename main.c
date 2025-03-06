/***************************************************************************************************************************************************
*Author		:Emertxe(http://www.emertxe.com)
*Date		:Mon 22 May 2017 14:00:05 IST
*File		:main.c
*Title		:Driver function
*Description	:This function acts like the driver function for the project inverted search
****************************************************************************************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "inverted_search.h"

int main(int argc, char *argv[])
{
	/* Define the main function here */
	Slist *head = NULL; // declaring the head
	if(argc > 1)
	{
		if(read_and_validate_args(argv, &head, argc));
		  printf("Read and validation completed successfully\n");
	}
	else 
	{
		printf("Argument should be greater than 1\n");
		return 0;
	}
    
	if(head != NULL)  // validation for list is updated with file names or not
	{
	int option;
    Hash arr[28]; // Declaring the Hash array i.e, table of 28 elements 0 to 27
    create_HT(arr,28);  // intialising the contents

	printf("Enter the Operation want to perform\n");
	printf(" 1.Create Database\n 2.Display Database\n 3.Update Database\n 4.Search\n 5.Save Database\n 6.Exit\n");
	int create_flag =0 , update_flag =0;
	while(1)
	{
		
			
	  scanf("%d",&option);

      switch(option)
	  {
		case 1: if(create_flag == 0)
		       {
		         printf("Create database\n");
		        if(create_database(arr,head) == SUCCESS) // function call
				{
					printf("Database created successfully\n");
					create_flag =1;
				}
				else 
				   printf("Database creation failed\n");  
                 
			   }
			   else
			     printf("Can't Perform Create Database once created\n"); 
				break;

		case 2: printf("Display Database\n");
		        display_HT(arr,28);
                 break;

		case 3:  if(create_flag == 0 && update_flag == 0)
		         {
					printf("Update Database\n");
		            char bk_file[50];
				    printf("Enter Backup file name\n");
				    getchar();
				   scanf("%[^\n]",bk_file);
				   getchar();
				   printf("Backup file you enterd is %s\n",bk_file);
				   if(validate_BKfile(bk_file) == SUCCESS)
				      printf("Backup file is valid\n");
				   else
				   {
					  printf("Backup file is not valid\n");
					 break;
				   }

				    if(update_HT(arr,&head,argv,bk_file) == SUCCESS) // function call
					{
						update_flag =1;
						printf("Updated to Database Successfully\n");
					} 
				    else
				      printf("Update failed\n");

				 }
				 else
				   printf("Can't perform Update Database once Created or Updated\n");
		        
				
				
		
				 break;
		        
		case 4: printf("Search\n");
		        char word[50];
				printf("Enter the word to be searched :\n");
				getchar();
				scanf("%[^\n]",word);
				getchar();
				printf("The word you entered is %s\n",word);
				if(search_HT(arr,word) == WORD_NOT_FOUND)
                   printf("Word not found\n");
				else
				  printf("Details of the word printed successfully\n");
				   
				break;	

		case 5: printf("Save Database\n");
		        char file[50];
                printf("Enter the file name\n");
				getchar();
				scanf("%[^\n]",file);   // reading the filename to be stored
				getchar();
                
				// validation of filename
				char *s1 = strstr(file,".");
				if(s1 == NULL)
				{
					printf("%s dont have .txt extension\n",file);
					break;
				}
				 
		        if(strcmp(s1,".txt") != 0)
		        {
                    printf("%s dont have .txt extension\n",file);
		            break;
		        }
				
                printf("file is %s\n",file);
				if(save_HT(arr,file) == SUCCESS)
				    printf("Saved to file Successfully\n");
				else
				    printf("Saving to file failed\n");
				
				
                break;

		case 6: printf("Exit\n");
		         return 0;

		default : printf("Enter valid option\n");
		         break;		
	  }
	}
	}
	else 
	  printf("List is empty, So can't perform operation\n");

	return 0;
}


int read_and_validate_args(char *argv[], Slist **head, int argc)
{
	for(int i=1;i<argc;i++)
	{
		// 1. To Check file extension .txt
		char *s1 = strstr(argv[i],".");
		if(s1 == NULL)
		{
			printf("%s dont have .txt extension\n",argv[i]);
			continue;
		}
		  

		if(strcmp(s1,".txt") != 0)
		{
           printf("%s dont have .txt extension\n",argv[i]);
		   continue;
		}

        // 2. To check whether the file availability
		FILE *fptr = fopen(argv[i],"r");
		if(fptr == NULL)
		{
			printf("%s is not available\n",argv[i]);
			continue;
		}
		  
		// 3. To check the file content
		
		fseek(fptr,0,SEEK_END);   // to set the fptr at last
		long size = ftell(fptr); // it tells the size of the file
		rewind(fptr);  // making fptr to point back to the first position

		if(size > 0)
		{
			fclose(fptr);
		}
		else
		{
            printf("%s file content not available\n",argv[i]);
			fclose(fptr);
			continue;
		}

		// 4. Check for Duplicate file name
         int flag =0;
		for(int j=0;j<i;j++)
		{
			if(i!=j)
			{
				int cmp = strcmp(argv[i],argv[j]);
			    if(cmp == 0)
			    {
				  printf("%s file name duplicate found\n",argv[i]);
				  flag = 1;
				  break;
			    }

			}
		}
		if(flag ==1)
		  continue;

		// 5. Inseting the file name at last(Insert at last);
        
        // Creation of newnode
		Slist *newnode = malloc(sizeof(Slist));
		if(newnode == NULL)
		   return FAILURE;
		strcpy(newnode->name,argv[i]);
		newnode->link = NULL;

 		if(*head == NULL)
		{
			*head = newnode;
		}
		else
		{
			Slist *temp = *head;
		    while(temp->link != NULL)
		    {
			  temp = temp->link;
		    }
		    temp->link = newnode;

		}
		
		
	}
	print_list(*head);
	return SUCCESS;
}

