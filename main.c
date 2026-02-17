/*

Name    : Suraj Sunil Tariwal
Reg Id  : 25026C_302
Project : INVERTED SEARCH

Description :

This project implements an Inverteed Search Engine. It maps words to the files in which they appear, along 
with their frequency. Here we use Linked List and Hashing concept's.
We use Linked List to store the filenames and hashing is used to store the address of word.
It supports operation such as Create Database, Search Database, Update Database and Save Database.


*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

int main(int argc,char **argv)
{
    if(argc < 2)
    {  
        printf("Please provide valid file names in '.txt' format\n");
        return FAILURE;
    }
    flist *head=NULL;
    //Validate the arguments
    int result = validation(argc,argv,&head);
    if(result==SUCCESS)
    {
        printf("Validation of files is successfull\n");
    }
    else if(result==FAILURE)
    {
        printf("Validation of files is not successfull\n");
        return FAILURE;
    }
    else if(result==DUPLICATE)
    {
        printf("Duplicate file found\n");
    }

    //Print the file list
    print_list(head);

    //Create the hash table
    hash_t arr[27];
    create_hash_table(arr);
    
    while(1)
    {
        printf("1. Create Database\n2. Update Database\n3. Search Database\n4. Display Database\n5. Save Database\n6. Exit\n");
        int option;
        printf("Enter your option : ");
        scanf("%d",&option);
        getchar();
        //Switch body for Database Operations
        switch(option)
        {
            case 1:
            {
                if(create_database(&head,arr)==SUCCESS)
                    printf("Database created successfully\n");
            }
            break;
            case 2:
            {
                if(update_database(&head,arr)==SUCCESS)
                    printf("Database updated successfully\n");
            }
            break;
            case 3:
            {
                if(search_database(head,arr)==FAILURE)
                    printf("Entered word is not in the Database\n");
            }
            break;
            case 4:
            {
                display_database(head,arr);
            }
            break;
            case 5:
            {
                if(save_database(arr)==SUCCESS)
                    printf("Database saved successfully\n");
            }
            break;
            case 6:
                return SUCCESS;
            default:
            printf("Enter the number between 1 to 6\n");
        }
    }
    return SUCCESS;
}