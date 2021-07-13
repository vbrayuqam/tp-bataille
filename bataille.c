//Inclusion des librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
Navire creer_navire(int taille, int taille_plateau);
int est_valide(int **plateau, int taille_plateau, Navire *nav);
void initialisation_plateau(int **plateau, int taille_plateau, Navire *nav);
void proposition_joueur(int **plateau, int **prop, int *nb_touche, int *nb_joue, int *nb_touche_nav, int taille_plateau);
void affichage_plateau(int **plateau, int taille_plateau);

//Plateau
//Grille

//Implementation des fonctions
void init_nb_aleatoire() {
   srandom(time(NULL));
}
int nb_aleatoire(int max) {
   return (random() % max);
}
//Main
int main(int argc, char *argv[]) {
   for (int i = 0; i < 100; i++) {
      printf("\n%d\n", nb_aleatoire(4));
   }
   return 0;
}
