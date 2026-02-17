#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

//Function for validating the arguements
int validation(int argc,char **argv,flist **head)
{
    int file_count=0;
    for(int i=1;i<argc;i++)
    {
        if(validate_extension(argv[i])==FAILURE)
        {
            //if .txt is not found then continue
            continue;
        }
        //if .txt is found then open the file and check it is present or not
        FILE *fptr=fopen(argv[i],"r");
        if(fptr==NULL)
        {
            printf("File is not present\n");
            continue;
        }
        //if file is present then check if file is empty/not
        fseek(fptr,0,SEEK_END);
        if(ftell(fptr)==0)
        {
            printf("File is empty\n");
            fclose(fptr);
            continue;
        }
        rewind(fptr);
        fclose(fptr);

        //if file is not empty then insert in the linked list
        
        int result = insert_at_last(head,argv[i]);
        if(result==SUCCESS)
        {
            file_count++;
        }
        else if(result==FAILURE)
        {
            return FAILURE;
        }
        else if(result==DUPLICATE)
        {
            return DUPLICATE;
        }
    }
    if(file_count==0)
    {  
        printf("Please provide valid file names in '.txt' format to proceed further\n./a.out <filename.txt> <filename.txt>\n");
        return FAILURE;
    }
    printf("%d File added succesfully\n",file_count);
    return SUCCESS;
}

//Function for Validating the extension ".txt"
int validate_extension(char *argv)
{
    //If .txt is not found then return failure
    if(strstr(argv,".txt")==NULL)
        return FAILURE;
    
    //if .txt is found then return success
    else if(strstr(argv,".txt"))
        return SUCCESS;
}

//Function for Inserting file at last
int insert_at_last(flist **head,char *argv)
{
    //If head is NULL then add first file into the list
    if(*head==NULL)
    {
        flist *newnode=malloc(sizeof(flist));
        if(newnode==NULL)
        {
            perror(" ");
            return FAILURE;
        }
        strcpy(newnode->filename,argv);
        newnode->link=NULL;
        *head=newnode;

    }
    else
    {
        //Add the remaining files into the list
        flist *newnode=malloc(sizeof(flist));
        if(newnode==NULL)
        {
            perror(" ");
            return FAILURE;
        }

        newnode->link=NULL;
        strcpy(newnode->filename,argv);

        flist *temp=*head;

        while(temp->link!=NULL)
        {
            //Check the file is already present or not
            if(strcmp(temp->filename,newnode->filename)==0)
                return DUPLICATE;
            
            temp=temp->link;
        }

        temp->link=newnode;
    }
    
    return SUCCESS;
}

//Function for Printing the linked list containing files
void print_list(flist *head)
{
    printf("The list is : ");
    flist *temp=head;
    printf("NULL -> ");
    while(temp)
    {
        printf("%s -> ",temp->filename);
        temp=temp->link;
    }
    printf("NULL");
    printf("\n");
}

