//Inclusion des librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//Structure de donnees
/**
* Structure representant une case dans une matrice.
*/
typedef struct une_case {
   int x;
   int y;
} Case;
/**
* Structure representant une navire.
*/
typedef struct navire {
   int sens;
   Case premiere_case;
   int taille;
} Navire;

//Declaration des fonctions
/**
* Initie la generation de nombres aleatoires.
*/
void init_nb_aleatoire();
/**
* Genere un nombre aleatoire sous une valeur desiree.
*
* @param  max  La valeur au dessus de la valeur maximum desiree.
*/
int nb_aleatoire(int max);
/**
* S'assure qu'aucun argument ne soit donne au programme.
*
* @param  nombre_argument  Le nombre d'arguments donnes au programme.
*/
void gestion_argument(int nombre_argument);
/**
* Demande une taille a l'utilisateur afin de generer le plateau de jeu.
*/
int demande_taille_plateau();
/**
* Creer une navire pour le jeu.
*
* @param  taille  La taille du navire
* @param  taille_plateau La taille du plateau de jeu
*/
Navire creer_navire(int taille, int taille_plateau);
/**
* Assigne les navires a une position dans le plateau.
*
* @param  navires  Tableau contenant les navires
* @param  taille_plateau  La taille du plateau de jeu
*/
void assigner_navires(Navire navires[7], int taille_plateau);
/**
* Positionne les navires dans le plateau et confirme que leurs positions sont valides.
*
* @param  plateau  Matrice de nombres entiers representant le plateau de jeu
* @param  taille_plateau  La taille du plateau de jeu
* @param  nav  Pointeur vers le tableau de navires utilises
*/
int est_valide(int **plateau, int taille_plateau, Navire *nav);
/**
* Propose au joueur d'effectuer un tir et en verifie la validite.
*
* @param  plateau  Matrice de nombres entier representant le plateau de jeu
* @param  prop  Matrice de nombres entier representant les tirs effectues par le joueur
* @param  nb_touche  Le nombre de tirs ayant touches
* @param  nb_joue  Le nombre de tirs joues
* @param  nb_touche_nav  Un tableau contenant le nobre de tirs effectues sur chaque navire
* @param  taille_plateau  La taille du plateau de jeu
*/
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
/**
* Initialise le plateau de jeu.
*
* @param  plateau  Matrice de nombres entier representant le plateau de jeu
* @param  taille_plateau  La taille du plateau de jeu
*/
void initialisation_plateau(int **plateau, int taille_plateau);
/**
* Affiche le plateau de jeu.
*
* @param  plateau  Matrice de nombres entier representant le plateau de jeu
* @param  taille_plateau  La taille du plateau de jeu
*/
void affichage_plateau(int **plateau, int taille_plateau);
/**
* Affiche la grille des tirs.
*
* @param  grille  Matrice de char representant les tirs du joueur
* @param  taille_plateau  La taille du plateau de jeu
*/
void affichage_grille(char **grille, int taille_plateau);
/**
* Affiche la matrice des propositions faites au joueurs.
*
* @param  prop  Matrice de nombres entier representant les tirs effectues par le joueur
* @param  taille_plateau  La taille du plateau de jeu
*/
void affichage_prop(int **grille, int taille_plateau);
/**
* Propose au joueur d'effectuer un tir et en verifie la validite.
*
* @param  plateau  Matrice de nombres entier representant le plateau de jeu
* @param  prop  Matrice de nombres entier representant les tirs effectues par le joueur
* @param  nb_touche  Le nombre de tirs ayant touches
* @param  nb_joue  Le nombre de tirs joues
* @param  nb_touche_nav  Un tableau contenant le nobre de tirs effectues sur chaque navire
* @param  taille_plateau  La taille du plateau de jeu
*/
void comparaison_grille(int **plateau, int **prop, char **grille, int taille_plateau, int *nb_touche_nav);
void initialisation_grille(char **grille, int taille_plateau);
void comp_nav_coule(int **plateau, char **grille, int taille_plateau, int *nb_touche_nav);

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
      printf("\nVeuillez entrez la taille du plateau (nombre entier entre 8 et 30) : ");
      if (scanf("%d", &taille_plateau) != 1) {
         perror("\nValeur illegale, fin du programme\n");
	 exit(-1);
      }
      if (taille_plateau < 8 || taille_plateau > 30) {
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
void comparaison_grille(int **plateau, int **prop, char **grille, int taille_plateau, int *nb_touche_nav) {
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
   comp_nav_coule(plateau, grille, taille_plateau, nb_touche_nav);
}
void comp_nav_coule(int **plateau, char **grille, int taille_plateau, int *nb_touche_nav) {
   for (int n = 2; n < 7; n ++) {
      for (int i = 0; i < taille_plateau; i++) {
         for (int j = 0; j < taille_plateau; j++) {
	    if (nb_touche_nav[n] == n) {
	       if (plateau[i][j] == n) {
	          grille[i][j] = 'C';
	       }
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
      proposition_joueur(plateau, prop, nb_touche_ptr, nb_joue_ptr, nb_touche_nav, taille_plateau);
      comparaison_grille(plateau, prop, grille, taille_plateau, nb_touche_nav);
      affichage_grille(grille, taille_plateau);
   } while (nb_touche != 20);

   //Affichage de fin de partie
   printf("\n\nPartie termine!\n\n");
   affichage_plateau(plateau, taille_plateau);
   printf("\nMerci et a la prochaine!\n");

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
