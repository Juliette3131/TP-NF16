#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct voisin {
  int indice;
  struct voisin *voisinSuivant;
} voisin;

typedef struct sommet {
  int indice;
  struct sommet *suivant;
  voisin *voisinSuivant;
} sommet;

typedef struct graphe {
  sommet *premier;
} graphe; 

graphe* creerGraphe(){
  graphe* nouveauGraphe = malloc(sizeof(graphe));
  if (nouveauGraphe == NULL) {
    return NULL;
  }
  nouveauGraphe -> premier = NULL 
  return nouveauGraphe;
}

void creerSommet(graphe* g, int id){
  sommet* nouveauSommet = malloc(sizeof(sommet));
  if (nouveauSommet==NULL){
    return NULL;
  }
  nouveauSommet-> indice = id;
  nouveauSommet -> suivant = g->premier;
  g->premier = nouveauSommet;
  nouveauSommet-> voisinSuivant = NULL;
}


int main(){
  
  return 0;
}
