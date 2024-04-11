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
  nouveauGraphe -> premier = NULL; 
  return nouveauGraphe;
}

void creerSommet(graphe* g, int id){
  sommet* nouveauSommet = malloc(sizeof(sommet));
  if (nouveauSommet==NULL){
    return;
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
  sommet* sommet1 = rechercheSommet(g, id1);
  sommet* sommet2 = rechercheSommet(g, id2);
  if (sommet1 == NULL || sommet2==NULL){
    printf("Un des sommets n'existe pas");
    return;
  }
  voisin* voisin1 = malloc(sizeof(voisin));
  voisin1->indice = id1;
  voisin1->voisinSuivant = sommet2->voisinSuivant;
  sommet2->voisinSuivant = voisin1;

  voisin* voisin2 = malloc(sizeof(voisin));
  voisin2->indice = id2;
  voisin2->voisinSuivant = sommet1->voisinSuivant;
  sommet1->voisinSuivant = voisin2;
}

graphe* construireGraphe(int N){
  graphe* nouveauGraphe = malloc(sizeof(graphe));
  nouveauGraphe = creerGraphe();
  for (int i = 0; i < N; i++){
    int nb;
    printf("Numéro du sommet : ");
    scanf("%d", &nb);
    creerSommet(nouveauGraphe, nb);
  }
  int A;
  printf("Nombre d'aretes: ");
  scanf("%d", &A);
  for (int i = 0; i < A; i++){
    int voisin1, voisin2;
    printf("Numéro du premier voisin : ");
    scanf("%d", &voisin1);
    printf("Numéro du deuxième voisin : ");
    scanf("%d", &voisin2);
    ajouterArete(nouveauGraphe, voisin1, voisin2);
  }
  return nouveauGraphe;
}

void afficherGraphe(graphe* g){
  sommet* sommete = g->premier;
  while(sommete != NULL){
    printf("| \nv\n");
    printf("%d", sommete-> indice);
    voisin* voisinAct = sommete->voisinSuivant;
    while(voisinAct!= NULL){
        printf("->");
        printf("%d", voisinAct->indice);
        voisinAct= voisinAct->voisinSuivant;
    }
    printf("\n");
    sommete = sommete -> suivant;
  }  
}

int rechercherDegre(graphe* g){
    int b=0;
    sommet* sommetd = g->premier;
    while(sommetd != NULL){
    voisin* voisinAct = sommetd->voisinSuivant;
    int a=0;
    while(voisinAct!= NULL){
        a+=1;
        voisinAct= voisinAct->voisinSuivant;
        if(a>b){
            b=a;
        }
    }
    sommetd = sommetd -> suivant;
    }
    printf("%d", b);
    return b;
}

int main(){
  graphe* nouveauGraphe = construireGraphe(3);
  afficherGraphe(nouveauGraphe);
  return 0;
}
