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

sommet* rechercheSommet(graphe *g, int id){
  sommet* sommetr = g->premier;
  while (sommetr != NULL){
    if (sommetr-> indice == id){
      return sommetr;
    }
    sommetr = sommetr->suivant;
  }
  return NULL;
}

void ajouterArete(graphe *g, int id1, int id2){
  sommet* voisin1 = rechercheSommet(g, id1);
  sommet* voisin2 = rechercheSommet(g, id2);
  if (voisin1 == NULL || voisin2==NULL){
    printf("Un des sommets n'existe pas");
    return;
  }
  voisin1-> voisinSuivant = voisin2;
  voisin2-> voisinSuivant = voisin1;
  voisin* voisin1 = malloc(sizeof(*voisin))
  voisin1-> indice= id1
  voisin1->
}

int main(){
  
  return 0;
}
