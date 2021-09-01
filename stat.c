#include "stat.h"
// retourne le max entre 2 entiers
int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}
// retourne la consomation totale de l'habitation sur un nombre de jour choisi
float consotot(struct Node *node, int day)
{
    float sum = 0;
    while (node != NULL)
    {
        sum = sum + node->elem->power * node->time * day;
        node = node->next;
    }
    return sum / 1000;
}
// converti des KWH en euros
float toeuro(float conso)
{
    return conso * 0.1765;
}
//retourne la consomation d'un objet
int consoobj(struct Node *node, int day, char *name)
{
    int obj;
    while (node != NULL)
    {
        if (strcmp(node->elem->word, name) == 0)
        {
            obj = node->elem->power * node->time * day;
            return obj;
        }
        node = node->next;
    }
    return 0;
}
//retourne la production annuelle par m2
float product(float PR)
{
    float product = averageyear() * PR * 0.3;
    return product;
}
//calcul le nombre de panneaux nécessaires pour couvrir la consomation
int solarnb(float conso, float produ)
{
    int nb = (int)ceil((conso / produ) / 1.7);
    return nb;
}
// calcul le cout de l'installation à partir du nombre de panneau
float cost(int N)
{
    return 2500 * 0.30 * N;
}
// calcul le nombre de jour pour obtenir un retour sur investissement
int ROI(int solarnb, struct Node *head, float produ,int nbsol)
{

    if (solarnb > nbsol)
    {
        solarnb = nbsol;
    }
    float price = cost(solarnb);
    int i = 0;
    float prod = toeuro(produ * 1.7 * solarnb / 365);
    while (price > 0)
    {
        price = price - prod;

        i++;
    }
    return i;
}
// convertit des jours en années, mois, jours
void todate(int ndays, int *y, int *m, int *d)
{

    *y = (int)ndays / 365;

    ndays = ndays - (365 * (*y));

    *m = (int)ndays / 30;

    *d = (int)ndays - (*m * 30);
}
// Permet d'obtenir l'irradiation heure par heure d'après le fichier contenant les informations détaillés heure par heure des irradiations
void besthour(float *tab)
{

    FILE *fic;
    char ligne[100];
    char *ptr_chaine;
    int num_ligne = 0;
    float data_float;
    float sum = 0;
   
    fic = fopen("daily.csv", "r+");
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
    for (int i = 0; i < 8; i++)
    {
        fgets(ligne, 100, fic);
    }

    while (fgets(ligne, 100, fic) != NULL && num_ligne < 24)
    {
        num_ligne++;
        ptr_chaine = strtok(ligne, "\t");
        ptr_chaine = strtok(NULL, "\t");
        ptr_chaine = strtok(NULL, "\t");
        ptr_chaine = strtok(NULL, "\t");
        sscanf(ptr_chaine, "%f", &tab[num_ligne]);
    }
    fclose(fic);
}
// permet d'obtenir le maximun d'un tableau
int MAX(float *TAB, int N)
{
    int I, MAX; 
    MAX = 0;
    for (I = 1; I < N; I++)
        if (*(TAB + MAX) < *(TAB + I))
            MAX = I;
    return MAX;
}
// permet d'obtenir les meilleures heures d'ensoillement
void tophours(float *tab, int *result, int len)
{
    for (int i = 0; i < len; i++)
    {
        result[i] = MAX(tab, 24);
        tab[MAX(tab, 24)] = 0;
    }
}
// permet de savoir si une valeur est dans un tableau
int valueinarray(int val, int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}
// permet d'obtenir les meilleures heures en fonction de la météo
void bestweather(int *tab, int DAY, int nb)
{

    FILE *fic;
    char ligne[500];
    char *ptr_chaine;
    int num_ligne = 0;
    float data_float;
    float sum = 0;
    int day;
   
    fic = fopen("météo.csv", "r+");
    if (fic == NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
    
    
    fgets(ligne, 500, fic);
    
    int i = 0;
    int heure;
    while (fgets(ligne, 500, fic) != NULL && i < nb)
    {
        num_ligne++;
        ptr_chaine = strtok(ligne, "-T:");
        ptr_chaine = strtok(NULL, "-T:");
        ptr_chaine = strtok(NULL, "-T:");
        sscanf(ptr_chaine, "%d", &day);

        if (day == DAY)
        {
            ptr_chaine = strtok(NULL, "-T:");
            sscanf(ptr_chaine, "%d", &heure);
            if (!valueinarray(heure, tab, i))
            {
                tab[i] = heure;
                i++;
            }
        }
    }
    fclose(fic);
}
// calcul la longueur d'une liste chainée
int lenlist(struct Node *node)
{
    int i = 0;
    while (node != NULL)
    {
        i++;
        node = (node)->next;
    }
    return i;
}
// convertie une liste chainé en tableau
void totab(struct Node *node, struct Node **tab)
{

    int i = 1;
    while (node != NULL)
    {
        tab[i] = node;
        i++;
        node = (node)->next;
    }
}
// résolution du probléme du sac à dos
int dp_knapsack_instance(struct Node **items, int capacity, int nb_items)
{
    int **V = (int **)malloc(sizeof(int *) * (capacity + 1));
    int **keep_x = (int **)malloc(sizeof(int *) * (capacity + 1));

    for (int s = 0; s <= capacity; s++)
    {
        V[s] = (int *)malloc(sizeof(int) * (nb_items + 1));
        keep_x[s] = (int *)malloc(sizeof(int) * (nb_items + 1));
        V[s][0] = 0;

        for (int t = 0; t <= nb_items; t++)
            keep_x[s][t] = 0;
    }

    for (int s = 0; s <= capacity; s++)
    {

        for (int t = 1; t <= nb_items; t++)
        {
            if (items[t]->elem->power * items[t]->time <= s)
            {
                V[s][t] = max(V[s][t - 1], V[s - items[t]->elem->power * items[t]->time][t - 1] + items[t]->priority);

                if (V[s - items[t]->elem->power * items[t]->time][t] + items[t]->priority > V[s][t - 1])
                    keep_x[s][t] = 1;
            }
            else

                V[s][t] = V[s][t - 1];
        }
    }

    printf("----------------------------------------------------------");
    printf("\nVous devriez utiliser les objets suivants: ");
    int k = capacity;
    for (int t = nb_items; t >= 0; t--)
    {
        if (keep_x[k][t] == 1)
        {
            printf("%s, ", items[t]->elem->word);
            k = k - items[t]->elem->power * items[t]->time;
        }
    }
    printf("\n----------------------------------------------------------\n");

    return V[capacity][nb_items];
}