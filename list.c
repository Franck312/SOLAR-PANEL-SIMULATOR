// Author: Raphael Viera (raphael.viera@emse.fr)
// Description: recap about linked lists (add node, delete node, print list).
// Creation of a linked list node struct

#include "list.h"

// Add node to the beginning of the list
void add_node(struct Node **head, Element *new_data, int time, int priority)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    new_node->elem = new_data;

    new_node->time = time;

    new_node->next = *head;
    new_node->priority = priority;

    *head = new_node;
}

//Remove the first occurrence of data_key in the linked list
int remove_node(struct Node **head, char *name)
{
    // Store head node
    struct Node *temp = *head, *previous;

    // Check if the data_key to be removed is in the head
    if (temp != NULL && (strcmp(temp->elem->word, name) == 0))
    {
        *head = temp->next; // Changed head
        free(temp);
        return 1;
    }

    // 1) Search for the data_key to be removed
    // 2) save the previous node in temp
    while (temp != NULL && (strcmp(temp->elem->word, name) != 0))
    {
        previous = temp;
        temp = temp->next;
    }

    // If data_key was not found
    if (temp == NULL)
        return 0;

    // Unlink the node from the linked list
    previous->next = temp->next;

    free(temp); // Free memory
    return 1;
}

// Print the linked list. Starting from a given node.
void print_list(struct Node *node)
{
    while (node != NULL)
    {
        printf(" %s \n", node->elem->word);
        node = node->next;
    }
    printf("\n");
}
//selectione un objet est le place dans une liste chainée
void selectobj(HashTable *hashTab, struct Node **head, char *name, int time, int priority)
{

    Element *point;
    point = FindObject(hashTab, name);

    add_node(head, point, time, priority);
}
// vérifie si un objet est dans la liste
int check_list(struct Node *node, char *word)
{

    while (node != NULL)
    {
        if (strcmp(word, (node)->elem->word) == 0)
        {
            return 1;
        }
        node = (node)->next;
    }

    return 0;
}
