//Inclusion des librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Structure de donnees
typedef struct une_case {
   int x;
   int y;
} Case;
typedef struct navire {
   int sens;
   Case premiere_case;
   int taille;
} Navire;

//Declaration des fonctions
void init_nb_aleatoire();
int nb_aleatoire(int max);
void gestion_argument(int nombre_argument);
int demande_taille_plateau();
Navire creer_navire(int taille, int taille_plateau);
void assigner_navires(Navire navires[7], int taille_plateau);
int est_valide(int **plateau, int taille_plateau, Navire *nav);
void initialisation_plateau(int **plateau, int taille_plateau);
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
void affichage_plateau(int **plateau, int taille_plateau);

//Implementation des fonctions
void init_nb_aleatoire() {
   srandom(time(NULL));
}
int nb_aleatoire(int max) {
   return (random() % max);
}
void gestion_argument(int nombre_arguments) {
   if (nombre_arguments != 1) {
      perror("\nNombre d'arguments errone, ce programme n'accepte aucuns arguments, fin du programme.\n");
      exit(-1);
   }
}
int demande_taille_plateau() {
   int taille_plateau;
   bool non_valide = true;
   while (non_valide) {
      printf("\nVeuillez entrez la taille du plateau (nombre entier entre 10 et 20) : ");
      scanf("%d", &taille_plateau);
      if (taille_plateau < 10 || taille_plateau > 20) {
         printf("\nMauvaise valeur!\n");
      } else {
         non_valide = false;
      }
   }
   return taille_plateau;
}
Navire creer_navire(int taille, int taille_plateau) {
   Navire nav;
   nav.taille = taille;
   nav.sens = nb_aleatoire(4);
   nav.premiere_case.x = nb_aleatoire(taille_plateau);
   nav.premiere_case.y = nb_aleatoire(taille_plateau);
   return nav;
}
void assigner_navires(Navire navires[7], int taille_plateau) {
   int compteur = 2;
   while (compteur < 7) {
      navires[compteur] = creer_navire(compteur, taille_plateau);
      compteur++;
   }
}
int est_valide(int **plateau, int taille_plateau, Navire *nav) {
   int valide = 1;
   for (int i = 2; i < 7; i++) {
      if (plateau[nav[i].premiere_case.x][nav[i].premiere_case.y] == 1) {
         valide = 0;
      }
      plateau[nav[i].premiere_case.x][nav[i].premiere_case.y] = 1;
      switch (nav[i].sens) {
         case 0:
            for (int j = 1; j < i; j++) {
	       if(!(i + j == taille_plateau)) {
	          if (plateau[nav[i].premiere_case.x + j][nav[i].premiere_case.y] == 1) {
                     valide = 0;
                  }
                  plateau[nav[i].premiere_case.x + j][nav[i].premiere_case.y]
               }

	    }
            break;	    
	 case 1:
	    break;
	 case 2:
	    break;
	 case 3:
	    break;
      }
   }
   return valide;
}

//Main
int main(int argc, char *argv[]) {
   init_nb_aleatoire();
   gestion_argument(argc);
   int taille_plateau = demande_taille_plateau(); 
   Navire navires[7];
   
   //Allocations dynamiques
   int erreur = 0;
   int **plateau = calloc(taille_plateau, sizeof(int*));
   if (!plateau) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
   for (int i = 0; i < taille_plateau; i++) {
      plateau[i] = calloc(taille_plateau, sizeof(int));
      if (!plateau[i]) {
         erreur = 1;
         break;
      }
   }
   if(erreur) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
   int **prop = calloc(taille_plateau, sizeof(int*));
   if (!prop) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
   for (int i = 0; i < taille_plateau; i++) {
      prop[i] = calloc(taille_plateau, sizeof(int));
      if (!prop[i]) {
         erreur = 1;
         break;
      }
   }
   if(erreur) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
   char **grille = calloc(taille_plateau, sizeof(char*));
   if (!grille) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
   for (int i = 0; i < taille_plateau; i++) {
      grille[i] = calloc(taille_plateau, sizeof(char));
      if (!grille[i]) {
         erreur = 1;
         break;
      }
   }
   if(erreur) {
      perror("\nErreur d'allocation de la memoire, fin du programme.\n");
      exit(-1);
   }
  
   assigner_navires(navires, taille_plateau);
   int valide = est_valide(plateau, taille_plateau, navires);
   printf("\nValide : %d\n", valide);
   //initialisation_plateau();
   //Boucle de jeu
   
   //Liberer la memoire
   for (int i = 0; i < taille_plateau; i++) {
      free(plateau[i]);
   }
   free(plateau);
   for (int i = 0; i < taille_plateau; i++) {
      free(prop[i]);
   }
   free(prop);
   for (int i = 0; i < taille_plateau; i++) {
      free(grille[i]);
   }
   free(grille);

   return 0;
}
