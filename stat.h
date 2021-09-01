#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <math.h>
float consotot(struct Node *node, int day);
int consoobj(struct Node *node, int day, char *name);
float product(float PR);
int solarnb(float conso, float produ);
float cost(int N);
int ROI(int solarnb, struct Node *head, float produ,int nbsol);
void todate(int ndays, int *y, int *m, int *d);
float toeuro(float conso);
void tophours(float *tab, int *result, int len);
void bestweather(int *tab, int DAY, int nb);
void besthour(float *tab);
int dp_knapsack_instance(struct Node **items, int capacity, int nb_items);
void totab(struct Node *node, struct Node **tab);
int lenlist(struct Node *node);