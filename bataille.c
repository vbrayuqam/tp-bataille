//Inclusion des librairies
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Declaration des fonctions
void init_nb_aleatoire();
int nb_aleatoire(int max);
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
