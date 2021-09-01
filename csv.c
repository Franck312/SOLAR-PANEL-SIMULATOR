#include "csv.h"
#define MAX 256
//inititialisation de la table de hashage
void initializeHashTable(HashTable *hashTab)
{
    hashTab->size = HASH_SIZE;
    hashTab->nbOccupiedEntries = 0;
    hashTab->nbElements = 0;
    hashTab->Elements = (Element **)malloc(hashTab->size * sizeof(Element *));

    for (unsigned int i = 0; i < hashTab->size; i++)
        hashTab->Elements[i] = NULL;
}
// fonction de hashage
unsigned long getHashValue(char *string)
{
    unsigned long hashValue = 0;
    int i = 0;

    while ((*string) != '\0')
    {
        hashValue += hashValue % HASH_SIZE + ((*string) * (int)pow(BASE, i)) % HASH_SIZE;
        i++;
        string++;
    }
    return hashValue % HASH_SIZE;
}
//insertion élément dans la table
void insertElementToHashTable(HashTable *hashTab, char *type, char *word, int power)
{
    hashTab->nbElements++;
    unsigned long i = getHashValue(word);
    Element *elem = (Element *)malloc(sizeof(Element));
    strcpy(elem->word, word);
    strcpy(elem->type, type);
    elem->power = power;

    if (hashTab->Elements[i] == NULL)
        hashTab->nbOccupiedEntries++;

    elem->next = hashTab->Elements[i];
    hashTab->Elements[i] = elem;
}
//Permet de verifier si un objet est dans la table et renvoie son pointeur
Element *FindObject(HashTable *hashTab, char *word)

{

    unsigned long hashValue = getHashValue(word);

    Element *elem = hashTab->Elements[hashValue];
    bool found = 0;
    Element *old;
    while (found == 0 && elem != NULL)
    {

        found = (strcmp(word, elem->word) == 0);

        old = elem;
        elem = elem->next;
    }

    if (found == 0)
    {
        return NULL;
    }
    else
    {
        //printf("type: %s, name: %s , power: %d \n", old->type, old->word, old->power);

        return old;
    }

}
//affiche un élément
void printelement(Element *elem)
{

    //printf("\n\t catégorie: %s ", elem->type);
    printf("\n\t Nom: %s", elem->word);
    printf(", Puissance(W): %d", elem->power);
}
//affiche tout les éléments
void printall(HashTable *hashTab)
{
    Element *tmp;
    for (int i = 0; i < HASH_SIZE; i++)
    {
        tmp = hashTab->Elements[i];
        while (tmp != NULL)
        {
            printelement(tmp);
            tmp = tmp->next;
        }
    }
}
//affiche par catégorie
void printtype(HashTable *hashTab, char *type)
{
    Element *tmp;
    for (int i = 0; i < HASH_SIZE; i++)
    {
        tmp = hashTab->Elements[i];
        while (tmp != NULL)
        {
            if (!strcmp(type, tmp->type))
            {
                printelement(tmp);
            }

            tmp = tmp->next;
        }
    }
}
// Permet de remplir la table de hachage en lisant le fichier csv contenant les electroménagers
void read(HashTable *hashTab, char tab[][20], int *len)
{

    FILE *fic;
    char ligne[100];
    char *ptr_chaine;
    int num_ligne = 1;
    int data_entier;
    char data_chaine2[20];
    char data_chaine[20];

    fic = fopen("puissance_eletromenagers.csv", "r+");
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    while (fgets(ligne, 100, fic) != NULL)
    {
        ptr_chaine = strtok(ligne, ",");

        sscanf(ptr_chaine, "%s", data_chaine);

        ptr_chaine = strtok(NULL, ",");

        sscanf(ptr_chaine, "%s", data_chaine2);

        ptr_chaine = strtok(NULL, ",");

        sscanf(ptr_chaine, "%d", &data_entier);

        insertElementToHashTable(hashTab, data_chaine, data_chaine2, data_entier);

        if (checktab(tab, data_chaine, *len))
        {
            strcpy(tab[*len], data_chaine);
            (*len)++;
        }

        num_ligne++;
    }
    fclose(fic);
}
// permet d'ajouter un objet au csv
void add(char *type, char *name, int power)
{
    FILE *fic;
    fic = fopen("puissance_eletromenagers.csv", "a");
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
    fprintf(fic, "\n%s, %s, %d", type, name, power);
    fclose(fic);
}
// permet d'extraire la moyenne annuelle du fichier contenant les irradiations
float averageyear()
{

    FILE *fic;
    char ligne[100];
    char *ptr_chaine; 
    int num_ligne = 0;
    float data_float;
    float sum = 0;
    
    fic = fopen("data.csv", "r+");
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }

    for (int i = 0; i < 6; i++)
    {
        fgets(ligne, 100, fic);
    }

    while (fgets(ligne, 100, fic) != NULL && num_ligne < 144)
    {
        num_ligne++;
        ptr_chaine = strtok(ligne, "\t");
        ptr_chaine = strtok(NULL, "\t");
        ptr_chaine = strtok(NULL, "\t");
        sscanf(ptr_chaine, "%f", &data_float);
        sum += data_float;
    }
    fclose(fic);
    return sum / 12;
}
//verifie si une chaine de caractère est contenue dans un un tableau
int checktab(char tab[][20], char *name, int nb)
{   
    for (int i= 0; i < nb; i++)
    {
        if (strcmp(name, tab[i]) == 0)
        {
            return 0;
        }

    }
    return 1;
}
//supprime un objet du csv
int delete (int lno)
{
    int ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
    char fname[MAX] = "puissance_eletromenagers.csv";
    char str[MAX], temp[] = "temp.txt";

    fptr1 = fopen(fname, "r");
    if (!fptr1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return 0;
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return 0;
    }

    lno++;
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);       
    rename(temp, fname); 
    fptr1 = fopen(fname, "r");
    ch = fgetc(fptr1);
    printf(" Maintenant le contenu %s est : \n", fname);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = fgetc(fptr1);
    }
    fclose(fptr1);
    return 0;
}
//Permet d'obtenir la line contenant le mot recherché
int FindWord(char *word, char *file)
{
    char line[1024];
    FILE *fp = fopen(file, "r");
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        i++;
        if (strstr(line, word) != NULL)
        {
            printf("%d", i);
            return i;
        }
    }
    return -1;
}
// permet d'obtenir des statistiques sur la hash table.
void printHashTableCharacteristics(HashTable *hashTab)
{
    /* A loadFactor = 0.75 offers a good tradeoff between time and space cost. */
    float loadFactor = 1.0 * hashTab->nbOccupiedEntries / hashTab->size;

    printf("\n******** Hash Table Characteristics **************\n");
    printf("Number of buckets: %u \n", hashTab->size);
    printf("Load Factor: %.2f \n", loadFactor);
    printf("Total number of elements: %u \n", hashTab->nbElements);
    printf("**************************************************\n");
}
