#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGHT 28
#include "csv.h"

// Creation of a linked list node struct
struct Node
{
    Element *elem;
    int time;
    int priority;
    struct Node *next;
};

void add_node(struct Node **head, Element *new_data, int time, int priority);
int remove_node(struct Node **head, char *name);
void print_list(struct Node *node);
void selectobj(HashTable *hashTab, struct Node **head, char *name, int time, int priority);
int check_list(struct Node *node, char *word);