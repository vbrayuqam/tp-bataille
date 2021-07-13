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
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
void initialisation_plateau(int **plateau, int taille_plateau);
void affichage_plateau(int **plateau, int taille_plateau);
void affichage_grille(char **grille, int taille_plateau);
void affichage_prop(int **grille, int taille_plateau);
void comparaison_grille(int **plateau, int **prop, char **grille, int taille_plateau);
void initialisation_grille(char **grille, int taille_plateau);

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
      printf("\nVeuillez entrez la taille du plateau (nombre entier entre 12 et 30) : ");
      if (scanf("%d", &taille_plateau) != 1) {
         perror("\nValeur illegale, fin du programme\n");
	 exit(-1);
      }
      if (taille_plateau < 12 || taille_plateau > 30) {
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
      if (plateau[nav[i].premiere_case.x][nav[i].premiere_case.y] != 0) {
         valide = 0;
      }
      plateau[nav[i].premiere_case.x][nav[i].premiere_case.y] = i;
      switch (nav[i].sens) {
         case 0:
            for (int j = 1; j < i; j++) { 
	       if(!(nav[i].premiere_case.x - j < 0)) {
	          if (plateau[nav[i].premiere_case.x - j][nav[i].premiere_case.y] != 0) {
                     valide = 0;
                  }
                  plateau[nav[i].premiere_case.x - j][nav[i].premiere_case.y] = i;
               } else {
	          valide = 0;
	       }
	    }
            break;	    
	 case 1:
	    for (int j = 1; j < i; j++) {
               if(!(nav[i].premiere_case.y + j >= taille_plateau)) {
                  if (plateau[nav[i].premiere_case.x][nav[i].premiere_case.y + j] != 0) {
                     valide = 0;
                  }
                  plateau[nav[i].premiere_case.x][nav[i].premiere_case.y + j] = i;
               } else {
                  valide = 0;
               }
            }
	    break;
	 case 2:
	    for (int j = 1; j < i; j++) {
               if(!(nav[i].premiere_case.x + j >= taille_plateau)) {
                  if (plateau[nav[i].premiere_case.x + j][nav[i].premiere_case.y] != 0) {
                     valide = 0;
                  }
                  plateau[nav[i].premiere_case.x + j][nav[i].premiere_case.y] = i;
               } else {
                  valide = 0;
               }
            }
	    break;
	 case 3:
	    for (int j = 1; j < i; j++) {
               if(!(nav[i].premiere_case.y - j < 0)) {
                  if (plateau[nav[i].premiere_case.x][nav[i].premiere_case.y - j] != 0) {
                     valide = 0;
                  }
                  plateau[nav[i].premiere_case.x][nav[i].premiere_case.y - j] = i;
               } else {
                  valide = 0;
               }
            }
	    break;
      }
   }
   return valide;
}
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau) {
   int x;
   int y;
   printf("\nAux canons!\n");
   do {
      printf("\nVeuillez saisir une valeur entre 0 (haut) et %d (bas) pour l'axe laterale : ", taille_plateau - 1);
      if (scanf("%d", &x) != 1) {
         perror("\nValeur illegale, fin du programme\n");
         exit(-1);
      }
   } while (x < 0 || x >= taille_plateau);
   do {
      printf("\nVeuillez saisir une valeur entre 0 (gauche) et %d (droite) pour l'axe horizontale : ", taille_plateau - 1);
      if (scanf("%d", &y) != 1) {
         perror("\nValeur illegale, fin du programme\n");
         exit(-1);
      }
   } while (y < 0 || y >= taille_plateau);
   *nb_joue += 1;
   if (plateau[x][y] != 0) {
      if (prop[x][y] == -1) {
         printf("\nDeja joue!\n");
      } else {
	 *nb_touche += 1;
	 nb_touche_nav[plateau[x][y]] += 1;
	 prop[x][y] = -1;
      }
	 if (nb_touche_nav[plateau[x][y]] == plateau[x][y]) {
	    printf("\nCoule!\n");
	 } else {
	    printf("\nTouche!\n");
	 
      }
   } else {
      if (prop[x][y] == -1) {
         printf("\nDeja joue!\n");
      } else {
         printf("\nA l'eau!\n");
         prop[x][y] = -1;
      } 
   }    
}
void initialisation_plateau(int **plateau, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         plateau[i][j] = 0;
      }
   }
}
void affichage_plateau(int **plateau, int taille_plateau) {
   printf("\nVoice le plateau de jeu initial:\n");
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         printf("%d", plateau[i][j]);
      }
      printf("\n");
   }
}
void affichage_grille(char **grille, int taille_plateau) {
   printf("\nVoici l'etat actuel de la grille:\n");
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         printf("%c", grille[i][j]);
      }
      printf("\n");
   }
}
void affichage_prop(int **prop, int taille_plateau) {
   printf("\nVoici l'ensemble de vos proposition durant le jeu:\n");
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         printf("%d", prop[i][j]);
      }
      printf("\n");
   }
}
void comparaison_grille(int **plateau, int **prop, char **grille, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i ++) {
      for (int j = 0; j < taille_plateau; j ++) {
         if (prop[i][j] == -1) {
	    grille[i][j] = 'O';
	    if (plateau[i][j] != 0) {
               grille[i][j] = 'X';
            }
	 }
      }
   }
}
void initialisation_grille(char **grille, int taille_plateau) {
   for (int i = 0; i < taille_plateau; i++) {
      for (int j = 0; j < taille_plateau; j++) {
         grille[i][j] = '.';
      }
   }
}
//Main
int main(int argc, char *argv[]) {
   init_nb_aleatoire();
   gestion_argument(argc);
   int validation;
   int nb_joue = 0;
   int *nb_joue_ptr = &nb_joue;
   int nb_touche = 0;
   int *nb_touche_ptr = &nb_touche;
   int nb_touche_nav[7];
   for (int i = 0; i < 7; i++) {
      nb_touche_nav[i] = 0;
   }
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
   
   //Boucle d'initiation du plateau
   do {
      initialisation_plateau(plateau, taille_plateau); 
      assigner_navires(navires, taille_plateau);
      validation = est_valide(plateau, taille_plateau, navires);
   } while (validation == 0);
   initialisation_grille(grille, taille_plateau);

   //Boucle de jeu
   do {
      affichage_plateau(plateau, taille_plateau);
      proposition_joueur(plateau, prop, nb_touche_ptr, nb_joue_ptr, nb_touche_nav, taille_plateau);
      comparaison_grille(plateau, prop, grille, taille_plateau);
      affichage_grille(grille, taille_plateau);
   } while (nb_touche != 20);


   //Affichage de fin de partie
   affichage_plateau(plateau, taille_plateau);

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
