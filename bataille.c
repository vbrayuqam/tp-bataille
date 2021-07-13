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
//Main
int main(int argc, char *argv[]) {
   init_nb_aleatoire();
   gestion_argument(argc);
   int taille_plateau = demande_taille_plateau();
   
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

   //initialisation_plateau();
   //Boucle de jeu
   //Liberer la memoire
   //Affichage du message de fin
   //Free section
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
