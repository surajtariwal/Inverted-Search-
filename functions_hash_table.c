#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"


//Function for Creating hash table
void create_hash_table(hash_t *arr)
{
    for(int i=0;i<27;i++)
    {
        arr[i].index=i;
        arr[i].link=NULL;
    }
}

//Function for Creating Database
int create_database(flist **head,hash_t arr[])
{
    flist *temp=*head;
    while(temp)
    {
        //Take each file name
        FILE *fptr=fopen(temp->filename,"r");
        if(fptr==NULL)
        {
            perror(" ");
            return FAILURE;
        }
        char buffer[20];
        while(fscanf(fptr,"%s",buffer)!=EOF)
        {
            //reading each word from file & storing it in buffer
            int idx = check_index(buffer[0]);   //checking the index to store in hash table
            if(arr[idx].link==NULL)
            {
                //if index is NULL then store the word, count, update subnode and mainlink 
                m_node *mainnode=malloc(sizeof(m_node));
                if(mainnode==NULL)
                {
                    perror(" ");
                    return FAILURE;
                } 
                s_node *subnode=malloc(sizeof(s_node));
                if(subnode==NULL)
                {
                    perror(" ");
                    return FAILURE;
                }

                //update sublink part
                subnode->wordcount=1;
                strcpy(subnode->filename,temp->filename);
                subnode->slink=NULL;

                //update mainnode part
                mainnode->filecount = 1;
                strcpy(mainnode->word,buffer);
                mainnode->mainlink=NULL;
                mainnode->sublink=subnode;

                arr[idx].link = mainnode;
                
            }
            else if(arr[idx].link!=NULL)
            {
                // if index is not null then compare the buffer with word that is stored in mainnode
                
                m_node *temp_mainnode = (arr[idx].link);
                m_node *prev_mainnode = NULL;

                while(temp_mainnode)
                {
                    //if both files are equal then update the sublink part
                    if(strcmp(buffer,temp_mainnode->word)==0)
                    {
                        break;
                    }
                    prev_mainnode = temp_mainnode;
                    temp_mainnode = temp_mainnode->mainlink;
                }
                
                if(temp_mainnode)
                {
                    //if mainnode of mainlink part is NULL or not
                    s_node *temp_subnode = temp_mainnode->sublink;
                    s_node *prev_subnode = NULL;

                    while(temp_subnode)
                    {
                        //check if the filename is same or not
                        if(strcmp(temp->filename,temp_subnode->filename)==0)
                            break;
                        
                        prev_subnode = temp_subnode;
                        temp_subnode = temp_subnode->slink;
                    }    
                    if(temp_subnode)
                    {
                        temp_subnode->wordcount++;
                    }
                    else
                    {
                        //create new subnode and link to previous subnode
                        s_node *newsub = malloc(sizeof(s_node));
                        if(newsub==NULL)
                        {
                            perror(" ");
                            return FAILURE;
                        }

                        newsub->wordcount=1;
                        strcpy(newsub->filename,temp->filename);
                        newsub->slink=NULL;

                        prev_subnode->slink = newsub;
                        temp_mainnode->filecount++;
                    }
                }
                else
                {
                    //create new mainlink and add to previous mainlink.
                    m_node *newmain = malloc(sizeof(m_node));
                    s_node *newsub = malloc(sizeof(s_node));

                    if(newmain==NULL)
                    {
                        perror(" ");
                        return FAILURE;
                    }
                    if(newsub==NULL)
                    {
                        perror(" ");
                        return FAILURE;
                    }

                    newsub->wordcount=1;
                    newsub->slink=NULL;
                    strcpy(newsub->filename,temp->filename);

                    strcpy(newmain->word,buffer);
                    newmain->filecount=1;
                    newmain->sublink=newsub;
                    newmain->mainlink=NULL;

                    prev_mainnode->mainlink = newmain;
                }  
            }
        }
        fclose(fptr);
        temp=temp->link;
    }
    return SUCCESS;
}

//Function for Displaying the database
void display_database(flist *head,hash_t arr[])
{
    printf("---------------------------------------------------------------------------\n");
    printf("| %-5s | %-15s | %-10s | %-20s | %-9s |\n","Index","Word","Filecount","Filename","Wordcount");
    printf("---------------------------------------------------------------------------\n");
    for(int i=0;i<27;i++)
    {
        //check if mainnode is NULL or not
        if(arr[i].link==NULL)
            continue;
        else
        {
            //If not NULL then iterate through the mainnode
            m_node *temp_mainnode = arr[i].link;
            
            while(temp_mainnode)
            {
                s_node *temp_subnode = temp_mainnode -> sublink;
                //iterate through the subnode 
                while(temp_subnode)
                {
                    printf("| %-5d | %-15s | %-10d | %-20s | %-9d |\n",i,temp_mainnode->word,temp_mainnode->filecount,temp_subnode->filename,temp_subnode->wordcount);
                    printf("---------------------------------------------------------------------------\n");
                    temp_subnode = temp_subnode -> slink;
                }
                temp_mainnode = temp_mainnode->mainlink;
            }
        } 
    }
}

//Function for saving the database
int save_database(hash_t arr[])
{
    char file[20];
    printf("Enter the filename to store database in it : ");
    scanf("%s",file);
    int res = validate_extension(file);
    if(res==FAILURE)
    {
        printf("Enter the filename ending with '.txt'\n");
        return FAILURE;
    }
    FILE *fptr = fopen(file,"w");
    if(fptr==NULL)
    {
        perror(" ");
        return FAILURE;
    }
    fprintf(fptr,"----------------------------------------------------------------------------\n");
    fprintf(fptr,"| %-5s | %-15s | %-10s | %-20s | %-9s |\n","Index","Word","Filecount","Filename","Wordcount");
    fprintf(fptr,"----------------------------------------------------------------------------\n");
    
    for(int i=0;i<27;i++)
    {
        //check if mainnode is NULL or not
        if(arr[i].link==NULL)
            continue;
        else
        {
            //if not NULL then iterate through the mainnode
            m_node *temp_mainnode = arr[i].link;
            while(temp_mainnode)
            {
                s_node *temp_subnode = temp_mainnode -> sublink;
                //iterate through the subnode
                while(temp_subnode)
                {
                    fprintf(fptr,"| %-5d | %-15s | %-10d | %-20s | %-9d |\n",i,temp_mainnode->word,temp_mainnode->filecount,temp_subnode->filename,temp_subnode->wordcount);
                    fprintf(fptr,"---------------------------------------------------------------------------\n");
                    temp_subnode = temp_subnode -> slink;
                }
                temp_mainnode = temp_mainnode -> mainlink;
            }
        }
    }
    fclose(fptr);
    return SUCCESS;
}

//Function for Updating the database
int update_database(flist **head,hash_t arr[])
{
    //asking user to enter the file name to update the existing database
    char file[20];
    printf("Enter the new file to update : ");
    scanf("%s",file);
    //check if file is ending with .txt
    int res = validate_extension(file);
    if(res==SUCCESS)
    {
        FILE *fptr = fopen(file,"r");
        if(fptr==NULL)
        {
            //file is ending with .txt and file is present
            perror(" ");
            return FAILURE;
        }
        fseek(fptr,0,SEEK_END);
        int long size = ftell(fptr);
        rewind(fptr);
        if(size==0)
        {
            printf("File is empty\n");
            fclose(fptr);
            return FAILURE;
        }
        fclose(fptr);
    }
    else if(res==FAILURE)
    {
        printf("File not ending with .txt while updating\n");
        return FAILURE;
    }
    //iterate through the linked list
    if(*head==NULL)
    {
        flist *newnode = malloc(sizeof(flist));
        if(newnode==NULL)
        {
            perror(" ");
            return FAILURE;
        }
        newnode->link=NULL;
        strcpy(newnode->filename,file);
        //add the file to the linked list, call create database function and save database function
        *head = newnode;
        create_database(head,arr);
        save_database(arr);
        return SUCCESS;
    }
    else
    {
        flist *newnode = malloc(sizeof(flist));
        if(newnode==NULL)
        {
            perror(" ");
            return FAILURE;
        }
        newnode->link=NULL;
        strcpy(newnode->filename,file);

        flist *temp = *head;
        while(temp->link)
        {
            if(strcmp(temp->filename,file)==0)
            {
                printf("Duplicate file found\n");
                return FAILURE;
            }
            temp = temp -> link;
        }
        //add the file to the linked list, call create database function and save databse function
        temp -> link = newnode;
        create_database(head,arr);
        save_database(arr);
        return SUCCESS;
    }
    
}

//Function for searching the database
int search_database(flist *head,hash_t arr[])
{
    char word[20];
    printf("Enter the word to be searched : ");
    scanf("%s",word);
    //gett the word to search
    int idx = check_index(word[0]);
    if(arr[idx].link == NULL)
    {
        return FAILURE;
    }
    else if(arr[idx].link!=NULL)
    {
        printf("------------------------------------------------------\n");        
        printf("| %-5s | %-15s | %-10s | %-10s |\n","Index","Word","Wordcount","Filename");
        printf("------------------------------------------------------\n");        

        m_node *temp_mainnode = arr[idx].link;
        while(temp_mainnode)
        {
            //Iterating the mainnode and searching the word
            if(strcmp(temp_mainnode->word,word)==0)
            {
                if(temp_mainnode->sublink)
                {
                    s_node *temp_subnode = temp_mainnode->sublink;
                    while(temp_subnode)
                    {
                        //iterting the subnode+
                        printf("| %-5d | %-15s | %-10d | %-10s |\n",idx,temp_mainnode->word,temp_subnode->wordcount,temp_subnode->filename);
                        printf("------------------------------------------------------\n");        
                        temp_subnode = temp_subnode -> slink;
                    }
                }
            }
            temp_mainnode = temp_mainnode -> mainlink;
        }
    }    
    return SUCCESS;
}

//Function for checking the index
int check_index(char ch)
{
    if(ch>='a' && ch<='z')
        return ch - 'a';
    else if(ch>='A' && ch<='Z')
        return ch - 'A';
    else
        return 26;
}