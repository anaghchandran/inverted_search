

#ifndef INVERT_H
#define INVERT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1
#define SIZE 100
#define HASH 28
#define special_char 27

typedef struct slist {
    char file_name[SIZE];
    struct slist *link;
} slist;

typedef struct sub_node {
    int word_count;
    char file_name[SIZE];
    struct sub_node *sub_link;
} s_node;

typedef struct main_node {
    int file_count;
    char word[SIZE];
    struct sub_node *sub_link;
    struct main_node *main_link;
} m_node;

typedef struct hash_table {
    int index;
    struct main_node *link;
} hash;

int read_and_validate(int argc, char *argv[], slist **head);
int insert_at_last(slist **head, char *data);
void print_list(slist *head);
int create_hash(hash *array, int size);
int read_from_file(slist **head, hash *array, int size);
int remove_duplicate(slist **head, char *argv);
int insert_hash(hash *array, char *word, char *file_name);
int display_database(hash *array , int size);
int search_data(hash *array, int size );
int save_data_base(hash *array, int size);
int update_data_base(hash *array,int size, slist **head );
#endif

