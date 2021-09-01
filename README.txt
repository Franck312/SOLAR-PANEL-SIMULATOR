@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ SOLAR PANEL SIMULATOR V1 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		           '
          .      '      .
    .      .     :     .      .
     '.        ______       .'
       '  _.-"`      `"-._ '
        .'                '.
 `'--. /                    \ .--'`
      /                      \
     ;                        ;
- -- |                        | -- -
     |     _.                 |
     ;    /__`A   ,_          ;
 .-'  \   |= |;._.}{__       /  '-.
    _.-""-|.' # '. `  `.-"{}<._
          /       \     \  x   `"
     ----/         \_.-'|--X----
     -=_ |         |    |- X.  =_
    - __ |_________|_.-'|_X-X##
        `'-._|_|;:;_.-'` '::.  `"-
     .:;.      .:.   ::.     '::.
#########################################Contenu#####################################################

Le présent programmme se compose de de fichiers suivant:

#code source utile à la compilation du programme:
-csv.h
-csv.c
-list.h
-list.c
-stat.c
-stat.h
-main.c
-makefile

#csv:
-data.csv : statistiques sur l'irradiation mensuelle durant 16 années
-daily.csv: statistiques d'irradition heure par heure
-météo.csv: irradiation heure par heure en fontion de la météo
-puissance_electormenagers.csv : catalogue des électroménagers disponibles

#fichier généré par le programme:
-bilan.txt: tableau de bord

################################Compilation et exécution#############################################

#compilation
$make solarpanel

#execution
$./solarpanel

####################################Utilisation#######################################################

#Une fois le programme lancé il suffit de se laisser guider par les menus.

#Pour tester le programme rapidement (l'ajout d'objets peut être chronophage), vous pouvez décommenter la
partie indiquée dans le main de main.c pour sélectionner rapidement les 6 objets suivants: 
Chauffage,Four,PS5,Xbox,Lampes,Tesla.

#La surface exploitable par défaut est de 20m2

#En cas d'erreur à l'execution: $chmod +x solarpanel

!!!NE PAS MODIFIER LE CSV MANUELLEMENT!!!: risque d'apparition de caractères invisible(\t\n...)
qui rendrait le programme non fonctionnel 

