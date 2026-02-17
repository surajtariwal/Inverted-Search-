#ifndef HEADER_H
#define HEADER_H

//Macros 
#define SUCCESS 1
#define FAILURE 0
#define DUPLICATE -1

//Structure for Node
typedef struct node
{
    char filename[20];
    struct node *link;
}flist;

//Structure for Sub node
typedef struct s_node
{
    int wordcount;
    char filename[20];
    struct s_node *slink;
}s_node;

//Structure for Main node
typedef struct m_node
{
    char word[20];
    int filecount;
    s_node *sublink;
    struct m_node *mainlink;   
}m_node;

//Structure for Hash Table
typedef struct hash
{
    int index;
    m_node *link;
}hash_t;

//Functions of Linked List
int insert_at_last(flist **head,char argv[]);
void print_list(flist *head);

//Functions for Validation 
int validate_extension(char argv[]);
int validation(int argc,char **argv,flist **head);

//Functions of Database
void create_hash_table(hash_t *arr);
int create_database(flist **head,hash_t arr[]);
int update_database(flist **head,hash_t arr[]);
int check_index(char ch);
void display_database(flist *head,hash_t arr[]);
int save_database(hash_t arr[]);
int search_database(flist *head,hash_t arr[]);

#endif
