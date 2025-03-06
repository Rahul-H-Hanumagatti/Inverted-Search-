#ifndef INV_H
#define INV_H

#define SUCCESS 0
#define FAILURE -1
#define WORD_NOT_FOUND 2

// Structure for Single linked list to store filenames
typedef struct node
{
    char name[50];
    struct node *link;
}Slist;

// Structure for Hash Table
typedef struct hash
{
    int index;
    struct main *link;
}Hash;

// Structure for Main node
typedef struct main
{
    int file_count;
    char word[50];
    struct main *mainlink;
    struct sub *sublink;
}Main;

// Structure for Subnode
typedef struct sub
{
    int word_count;
    char file_name[50];
    struct sub *slink;

}Sub;

/* Function to read and validate CLA*/
int read_and_validate_args(char *argv[], Slist **head, int argc);

void print_list(Slist *head);

int create_database(Hash *arr, Slist *head);

int create_HT(Hash *arr, int size);

void display_HT(Hash *arr, int size);

int save_HT(Hash *arr, char *file);

int search_HT(Hash *arr, char *word);

int update_HT(Hash *arr, Slist **head,char *argv[], char *bk_file);

int validate_BKfile(char *bk_file);

#endif