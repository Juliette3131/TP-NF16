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

void supprimerSommet(graphe* g, int id) {
    sommet* supp = rechercheSommet(g, id);

    if (g->premier == supp) {
        g->premier = supp->suivant;
        free(supp);
    }
    else {
        for (sommet* s = g->premier; s != NULL; s = s->suivant) {
            voisin* voisinPrecedent = NULL;
            voisin* voisinAct = s->voisinSuivant;
            if (voisinAct->indice == id) {
                s->voisinSuivant = voisinAct->voisinSuivant;
                free(voisinAct);
                continue;
            }

            while (voisinAct != NULL && voisinAct->indice != id) {
                voisinPrecedent = voisinAct;
                voisinAct = voisinAct->voisinSuivant;
            }

            if (voisinAct != NULL && voisinAct->indice == id) {
                voisinPrecedent->voisinSuivant = voisinAct->voisinSuivant;
                free(voisinAct);
            }
        }

        sommet* precedent = g->premier;
        while (precedent->suivant != supp) {
            precedent = precedent->suivant;
        }
        precedent->suivant = supp->suivant;
        free(supp);
    }
}

int contientBoucle(graphe* g){
    sommet * sommet = g->premier;
    int a =0;
    while (sommet != NULL) {
        voisin* voisin = sommet->voisinSuivant;
        while (voisin!= NULL ){
            if (voisin->indice == sommet->indice){
            a=1;
            break;
            }   
            voisin = voisin->voisinSuivant;
        }   
        sommet = sommet->suivant;
    }
    return a;
}
void afficherMenu() {
    printf("=== Menu ===\n");
    printf("1. Créer un graphe vide\n");
    printf("2. Construire un graphe de N sommets\n");
    printf("3. Ajouter un sommet\n");
    printf("4. Ajouter une arête\n");
    printf("5. Afficher un graphe\n");
    printf("6. Donner le degré maximal du graphe\n");
    printf("7. Supprimer un sommet\n");
    printf("8. Vérifier si le graphe contient une boucle\n");
    printf("9. Fusionner deux sommets\n");
    printf("9. Quitter\n");
}

int main(){
int choix;

    do {
        afficherMenu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nous allons creer un graphe vide.\n");
                graphe* nouveauGraphe = creerGraphe();
                break;
            case 2:
                printf("Nous allons construire un graphe. Combien de sommets voulez-vous qu'il comporte?\n");
                break;
            case 3:
                printf("Vous avez choisi l'option 3.\n");
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            
            case 5:
                printf("Au revoir !\n");
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            case 7:
                printf("Au revoir !\n");
                break;
            case 8:
                printf("Au revoir !\n");
                break;
            case 9:
                printf("Au revoir !\n");
                break;
            case 10:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 4);

  return 0;
}
