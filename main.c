#include "stat.h"
#define PR 0.7
#define typemax 20
HashTable hashTab;
struct Node *head = NULL;
int panelmax= 11;

char tab[typemax][20];// tableau contenant les catégories
int lentype = 0;// longueur

//affiche par catégorie les objets disponibles dans les menus
void printbytype()
{
	char type[20];
	printf("Catégories disponibles:\n");
	for (int i = 0; i < lentype; i++)
	{
		printf("%s\n", tab[i]);
	}
	printf("Catégorie de l'objet recherché:\n");
	scanf("%s", type);
	printtype(&hashTab, type);
}
// menu 1
void menu1()
{
	bool quit = false;
	char choice;
	while (!quit)
	{
		printf("\n");
		printf("----------------------------------------------------\n");
		printf("1:  Ajouter un objet dans le fichier\n");
		printf("2:  Afficher les objets disponibles\n");
		printf("3:  Supprimer un objet\n");
		printf("4:  Retour\n");
		printf("----------------------------------------------------\n\n");
		scanf(" %c", &choice);

		switch (choice)
		{
		case '1':
		{
			int power;
			char type[20];
			char name[20];
			printf("Catégorie:\n");
			scanf("%s", type);
			printf("Nom:\n");
			scanf("%s", name);
			printf("Puissance(W):\n");
			scanf("%d", &power);
			if (FindObject(&hashTab, name) == NULL)
			{

				add(type, name, power);
				initializeHashTable(&hashTab);
				read(&hashTab, tab, &lentype);
				printf("Objet ajouté avec succès");
			}
			else
			{
				printf("Désolé cet appareil existe déja\n");
			}
			break;
		}
		case '2':

		{
			printbytype();
			break;
		}
		case '3':

		{
			char name[20];
			printbytype();
			printf("Nom:\n");
			scanf("%s", name);
			delete (FindWord(name, "puissance_eletromenagers.csv"));
			printf("La suppresion a été effectué avec succès");
			initializeHashTable(&hashTab);
			read(&hashTab, tab, &lentype);
			break;
		}
		case '4':
		{
			quit = true;
			break;
		}
		default:
		{
			printf("/!\\ Erreur: cette option n'est pas supportée.\n");
			break;
		}
		}
	}
}
// menu 2
void menu2()
{
	bool quit = false;
	char choice;

	while (!quit)
	{
		printf("\n");
		printf("----------------------------------------------------\n");
		printf("1:  Ajouter un objet dans la maison\n");
		printf("2:  Supprimer un objet de la maison\n");
		printf("3:  Afficher les objets séléctionés\n");
		printf("4:  Modifier la surface exploitable\n");
		printf("5:  Retour\n");
		printf("----------------------------------------------------\n\n");
		scanf(" %c", &choice);

		switch (choice)
		{ // faire le cas ou il ajoute deux fois un objet
		case '1':

		{   printbytype();
			char name[28];
			int time;
			int priority;
			printf("\nNom:\n");
			scanf("%s", name);
			printf("Temps d'utilisation journalière en heure:\n");
			scanf("%d", &time);
			printf("Quel niveau de priorité affectez vous à l'objet ?(entre 1 et 10)\n");
			scanf("%d", &priority);
			int exist = check_list(head, name);
			if (FindObject(&hashTab, name) == NULL)
			{
				printf("Désolé cet appareil n'existe pas vous devez l'ajouter au catalogue\n");
			}
			else if (exist)
			{

				printf("Désolé cet appareil est déja sélectionné, voulez vous vraiment en rajouter un ? Y/N\n");
				char answer;
				scanf(" %c", &answer);
				if (answer == 'Y')
				{
					selectobj(&hashTab, &head, name, time, priority);
					printf("Objet ajouté avec succès\n");
				}
			}
			else
			{

				selectobj(&hashTab, &head, name, time, priority);
				printf("Objet ajouté avec succès\n");
			}

			break;
		}
		case '2':
		{
			char name[20];
			printf("Nom de l'objet à supprimer:\n");
			scanf("%s", name);
			remove_node(&head, name) ? printf("succès") : printf("Echec objet non present dans la selection\n");
			break;
		}
		case '3':
		{
			printf("Objet(s) sélectionné(s):\n");
			print_list(head);
			break;
		}
		case '4':
		{
			printf("Surface exploitable en m2:\n");
			scanf("%d",&panelmax);
			panelmax= (int)floor(panelmax/1.7);
			break;
		}

		case '5':
		{
			quit = true;
		}
		default:
		{
			printf("/!\\ Erreur: cette option n'est pas supportée.\n");
			break;
		}
		}
	}
}
// menu 3
void menu3()
{
	bool quit = false;
	char choice;

	while (!quit)
	{
		printf("\n");
		printf("----------------------------------------------------\n");
		printf("1:  Consommation totale de la maison\n");
		printf("2:  Consommation par objet\n");
		printf("3:  Quit\n");
		printf("----------------------------------------------------\n\n");
		scanf(" %c", &choice);

		switch (choice)
		{
		case '1':
		{
			char name[20];
			int time;
			printf("Horizon statistique (en jour):\n");
			scanf("%d", &time);
			float conso = consotot(head, time);
			printf("\nLa consommation totale annuelle %.2f KWH, soit %.2f euros", conso, toeuro(conso));
			break;
		}
		case '2':
		{	printbytype();
			char name[20];
			printf("\nNom de l'objet:\n");
			scanf("%s", name);
			int time;
			printf("Horizon statistique (en jour):\n");
			scanf("%d", &time);
			if (check_list(head, name))
			{	int conso=consoobj(head, time, name);
				printf("\n Consommation de l'objet: %d WH, soit %.2f euros", conso,toeuro(conso/1000));
			}
			else
			{
				printf("Désolé vous n'avez pas cet objet dans votre maison");
			}
			break;
		}
		case '3':
		{
			quit = true;
			break;
		}

		default:
		{
			printf("/!\\ Erreur: cette option n'est pas supportée.\n");
			break;
		}
		}
	}
}
// menu 4
void menu4()
{

	float produ = product(PR);
	int N = solarnb(consotot(head, 365), produ);



	printf("       /  /  /  /  /  /\n");
	printf("    =================\n");
	printf("  /` /` /` /` /` /`\n");
	printf("          |\\|         _____\n");
	printf("          |/|      /`^ \\   `\\ \n");
	printf("          |\\|    /` [_] `\\   `\\ \n");
	printf("          |/|  /` ___    _`\\___`\\ \n");
	printf("          |\\|  | [_|_]  [_] |   |\n");
	printf("----------|/|--|------------|---|-----\n");
	printf("\n");


	printf("\nNombre de panneaux solaires nécessaire pour couvrir totalement votre consommation: %d.\n", N);
	
	if (N > panelmax)
	{
		printf("Malheuresement vous ne disposez pas de l'espace nécessaire sur votre toit, le nombre de panneaux sera donc limité à %d.\n",panelmax);
		N = panelmax;
	}
	printf("\n");
	printf("Le coût de la démarche sera de %.2f euros.\n", cost(N));
	printf("\n");
	printf("La production annuelle est de %.2f KWH.\n", produ * 1.7 * N);
	printf("\n");
	printf("Les économies annuelles sont de %.2f euros.\n", toeuro(1.7 * N * produ));
	printf("\n");
	int y, m, d;
	int roi = ROI(N, head, produ,panelmax);
	todate(roi, &y, &m, &d);

	printf("Le retour sur investissement se fera dans : %d année(s) %d mois %d jour(s).", y, m, d);
	printf("\n");
}
//menu 5
void menu5()
{
	FILE *fic;
	fic = fopen("bilan.txt", "w");
	if (fic == NULL)
	{
		printf("Ouverture fichier impossible !");
		exit(0);
	}
	float produ = product(PR);
	int N = solarnb(consotot(head, 365), produ);
	fprintf(fic,"SOLAR PANEL ULTIMATE V1:\n\n");
	fprintf(fic,"Récapitulatif relatif au retour sur investissement:\n\n");

	fprintf(fic,"       /  /  /  /  /  /\n");
	fprintf(fic,"    =================\n");
	fprintf(fic,"  /` /` /` /` /` /`\n");
	fprintf(fic,"          |\\|         _____\n");
	fprintf(fic,"          |/|      /`^ \\   `\\ \n");
	fprintf(fic,"          |\\|    /` [_] `\\   `\\ \n");
	fprintf(fic,"          |/|  /` ___    _`\\___`\\ \n");
	fprintf(fic,"          |\\|  | [_|_]  [_] |   |\n");
	fprintf(fic,"----------|/|--|------------|---|-----\n");
	fprintf(fic,"\n");



	fprintf(fic, "Nombre de panneaux solaires nécessaire pour couvrir totalement votre consommation: %d.\n", N);

	if (N > panelmax)
	{
		fprintf(fic, "Malheuresement vous ne disposez pas de l'espace nécessaire sur votre toit, le nombre de panneau sera donc limité à %d.\n",panelmax);
		N = panelmax;
	}
	fprintf(fic,"\n");
	fprintf(fic, "Le coût de la démarche sera de %.2f euros.\n", cost(N));

	int y, m, d;
	int roi = ROI(N, head, produ,panelmax);
	todate(roi, &y, &m, &d);
	fprintf(fic,"\n");
	fprintf(fic, "La production annuelle est de %.2f KWH.\n", produ * 1.7 * N);
	fprintf(fic,"\n");
	fprintf(fic, "Les économies annuelles sont de %.2f euros.\n", toeuro(produ * 1.7 * N));
	fprintf(fic,"\n");
	fprintf(fic, "Le retour sur investissement se fera dans : %d année(s) %d mois %d jour(s).\n", y, m, d);
	fprintf(fic,"\n");
	fclose(fic);

	printf("Le récapitulatif est maintenant disponible dans le fichier bilan.txt.\n");

}
// menu 6
void menu6()
{
	bool quit = false;
	char choice;

	while (!quit)
	{
		printf("\n");
		printf("----------------------------------------------------\n");
		printf("1:  Meilleures heures statistiquement\n");
		printf("2:  Meilleures heures en tenant compte de la météo\n");
		printf("3:  Quit\n");
		printf("----------------------------------------------------\n\n");
		scanf(" %c", &choice);

		switch (choice)
		{
		case '1':
		{
			int nb;
			float tab[24];
			int result[5];
			printf("Top 1...5 ?:\n");
			scanf("%d", &nb);
			nb = (nb > 5) ? nb = 5 : nb;
			besthour(tab);
			tophours(tab, result, nb);
			printf("Les meilleures heures selon les statistiques sont: \n");
			for (int i = 0; i < nb; i++)
			{
				printf("%dh;", result[i]);
			}
			break;
		}
		case '2':
		{ 
			int nb;
			int tab[5];
			printf("Top 1...5 ?:\n");
			scanf("%d", &nb);
			nb = (nb > 5) ? nb = 5 : nb;
			bestweather(tab, 12, nb);
			printf("Les meilleures heures selon la météo de demain sont: \n");
			for (int i = 0; i < nb; i++)
			{
				printf("%dh;", tab[i]);
			}
			break;
		}
		case '3':
		{
			quit = true;
			break;
		}

		default:
		{
			printf("/!\\ Erreur: cette option n'est pas supportée.\n");
			break;
		}
		}
	}
}
//menu 7
void menu7()
{
	struct Node **tab;
	int n = lenlist(head);
	tab = (struct Node **)malloc(sizeof(struct Node *) * (n + 1));
	totab(head, tab);

	float r;
	float produ = product(PR);
	int N = solarnb(consotot(head, 365), product(PR));
	N=(N>panelmax) ? panelmax: N;
	printf("Quel est l'ensoleillement prévu de 1 à 4 ?");
	scanf("%f", &r);
	r = (r > 4) ? r = 4 : r;
	if (r == 4)
	{
		r = 1.5;
	}
	else if ((r == 3))
	{
		r = 1.25;
	}
	else if (r == 2)
	{
		r = 0.75;
	}
	else
	{
		r = 0.5;
	}
	int capacity = (int)1000 * r * N * 1.7 * (produ / 365);
	dp_knapsack_instance(tab, capacity, n);
}
// menu principal
void menu()
{
	bool quit = false;
	char choice;

	while (!quit)
	{
		printf("\n");
		printf("-----------------------------------------------------------------------------\n");
		printf("1:  Editer le fichier catalogue des électroménagers\n");
		printf("2:  Configuration de la maison\n");
		printf("3:  Information de consommation\n");
		printf("4:  Simulations liées aux panneaux\n");
		printf("5:  Créer un récapitulatif (Tableau de bord)\n");
		printf("6:  Planification heure par heure de la consommation (statistiques ou météo)\n");
		printf("7:  Planification d'utilisation journalière selon la météo\n");
		printf("8:  Quit\n");
		printf("-----------------------------------------------------------------------------\n\n");
		scanf(" %c", &choice);

		switch (choice)
		{
		case '1':
		{
			menu1();
			break;
		}
		case '2':
		{
			menu2();
			break;
		}
		case '3':
		{
			menu3();
			break;
		}
		case '4':
		{
			menu4();
			break;
		}
		case '5':
		{
			menu5();
			break;
		}
		case '6':
		{
			menu6();
			break;
		}
		case '7':
		{
			menu7();
			break;
		}

		case '8':
		{
			quit = true;
			break;
		}

		default:
		{
			printf("/!\\ Erreur: Cette option n'est pas supportée.");
			break;
		}
		}
	}
}

int main()
{

	initializeHashTable(&hashTab);
	read(&hashTab, tab, &lentype);

	// Pour tester le programme rapidement vous pouvez décommenter la portion ci-desssous pour sélectionner directement 6 objets.
	// selectobj( &hashTab, &head,"Chauffage",7,10);
	// selectobj( &hashTab, &head,"Four",2,3);
	// selectobj( &hashTab, &head,"PS5",4,2);
	// selectobj( &hashTab, &head,"Xbox",8,9);
	// selectobj( &hashTab, &head,"Lampes",8,7);
	// selectobj( &hashTab, &head,"Tesla",12,2);

	printHashTableCharacteristics(&hashTab);
	menu();

	return 0;
}
