#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_WORD_LENGHT 28 /* Maximum word length */
#define HASH_SIZE 13	   /* Prime number */
#define BASE 128

typedef struct _element
{
	char type[MAX_WORD_LENGHT];

	char word[MAX_WORD_LENGHT];

	int power;

	struct _element *next;

} Element;

typedef struct _hashTable
{

	unsigned int size;
	unsigned int nbOccupiedEntries;
	unsigned int nbElements;
	Element **Elements;

} HashTable;

void initializeHashTable(HashTable *hashTab);
unsigned long getHashValue(char *string);
void insertElementToHashTable(HashTable *hashTab, char *type, char *word, int power);
Element *FindObject(HashTable *hashTab, char *word);
void printelement(Element *elem);
void printall(HashTable *hashTab);
void printtype(HashTable *hashTab, char *type);
void read(HashTable *hashTab, char tab[][20], int *len);
void add(char *type, char *name, int power);
float averageyear();
int checktab(char tab[][20], char *name, int nb);
int FindWord(char *word, char *file);
int delete (int lno);
void printHashTableCharacteristics(HashTable *hashTab);