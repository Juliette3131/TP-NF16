#include <stdio.h>
#include <stdlib.h>

typedef struct Voisin Voisin;
struct Voisin
{
    int indice;
    Voisin *suivant;
};

typedef struct Sommet Sommet;
struct Sommet
{
    int indice;
    Sommet *suivant;
    Voisin *voisins;
};

typedef struct Graphe Graphe;
struct Graphe
{
    Sommet *premier;
};

Graphe* creerGraphe()
{
    Graphe *graphe = malloc(sizeof(*graphe)); //Alloue l'espace mémoire pour insérer le prochain élément
    Sommet *sommet = malloc(sizeof(*sommet));

    if (graphe == NULL || sommet == NULL)
    {
        exit(EXIT_FAILURE);
    } //Vérification que cet allouage mémoire ne pose pas problème pour éviter d'endommager l'ordinateur

    sommet->indice = 1;
    sommet->suivant = NULL;
    sommet->voisins = NULL;
    graphe->premier = sommet;

    return graphe;
}

void creerSommet(Graphe *g, int id)
{
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return;}
    else
    {
        Sommet *ajouter_apres = g->premier;
        int ajouter = 0;
        while (ajouter == 0)
        {
            if (id == g->premier->indice) {printf("Le sommet %d existe deja\n", id); break;}
            if (ajouter_apres->suivant == NULL || id < ajouter_apres->suivant->indice)
            {
                Sommet *nouveau = malloc(sizeof(*nouveau));
                nouveau->indice = id;
                if (ajouter_apres->suivant == NULL) nouveau->suivant = NULL;
                else nouveau->suivant = ajouter_apres->suivant;
                ajouter_apres->suivant = nouveau;
                nouveau->voisins = NULL;
                printf("Sommet %d ajoute avec succes !\n", id);
                ajouter = 1;
            }
            else
            {
                ajouter_apres = ajouter_apres->suivant;
            }
        }
    }
}

Sommet* rechercherSommet(Graphe *g, int id)
{
    if (g == NULL){exit(EXIT_FAILURE);}
    Sommet *temp = g->premier;
    while (temp->indice != id)
    {
        if (temp->suivant == NULL) return NULL;
        temp = temp->suivant;
    }
    return temp;
}

void ajouterArete(Graphe *g, int id1, int id2) {
    if (g == NULL){printf("--> Aucun graphe n'existe. Creez d'abord un graphe <-- "); return;}
    Sommet *sommet1 = rechercherSommet(g, id1);
    if (sommet1 == NULL) {
        printf("Le sommet %d n'est pas dans le graphe.\n", id1);
        return;
    }

    Voisin *ajouter_apres = sommet1->voisins;
    int ajouter = 0;
    while (ajouter == 0) {
        if (ajouter_apres == NULL) {
            Voisin *nouveau = malloc(sizeof(*nouveau));
            nouveau->indice = id2;
            nouveau->suivant = NULL;
            sommet1->voisins = nouveau;
            ajouter = 1;
        } else {
            if (id2 == sommet1->voisins->indice) {
                printf("Ces 2 sommets sont deja voisins.\n");
                break;
            }
            if (ajouter_apres->suivant == NULL || id2 < ajouter_apres->suivant->indice) {
                Voisin *nouveau = malloc(sizeof(*nouveau));
                nouveau->indice = id2;
                if (ajouter_apres->suivant == NULL) nouveau->suivant = NULL;
                else nouveau->suivant = ajouter_apres->suivant;
                ajouter_apres->suivant = nouveau;
                nouveau->suivant = NULL;
                ajouter = 1;
            } else {
                ajouter_apres = ajouter_apres->suivant;
            }
        }
    }

    Sommet *sommet2 = rechercherSommet(g, id2);
    if (sommet2 == NULL){printf("Le sommet %d n'est pas dans le graphe.\n", id1); return;}

    ajouter_apres = sommet2->voisins;
    ajouter = 0;
    while (ajouter == 0) {
        if (ajouter_apres == NULL) {
            Voisin *nouveau = malloc(sizeof(*nouveau));
            nouveau->indice = id1;
            nouveau->suivant = NULL;
            sommet2->voisins = nouveau;
            ajouter = 1;
        } else {
            if (id1 == sommet2->voisins->indice) {break;}
            if (ajouter_apres->suivant == NULL || id1 < ajouter_apres->suivant->indice) {
                Voisin *nouveau = malloc(sizeof(*nouveau));
                nouveau->indice = id1;
                if (ajouter_apres->suivant == NULL) nouveau->suivant = NULL;
                else nouveau->suivant = ajouter_apres->suivant;
                ajouter_apres->suivant = nouveau;
                nouveau->suivant = NULL;
                ajouter = 1;
            } else {
                ajouter_apres = ajouter_apres->suivant;
            }
        }
    }
}

void afficherGraphe(Graphe *g)
{
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return;}
    Sommet *temp = g->premier;
    Voisin *tempV = temp->voisins;
    while (temp != NULL)
    {
        printf("%d", temp->indice);
        if (temp->voisins != NULL)
        {
            tempV = temp->voisins;
            do {
                printf("(%d)", tempV->indice);
                tempV = tempV->suivant;}
            while (tempV != NULL);
        }
        printf(" -> ");
        temp = temp->suivant;
    }
    printf("NULL ------ Fin\n");
}

Graphe* construireGraphe(int N){
    Graphe *nouveauGraphe = creerGraphe();
    printf("\n---------- Creation d'un nouveau graphe ---------\n");
    for (int i = 0; i < N; i++)
    {
        int nb;
        printf("Indice du sommet a creer :");
        scanf("%d", &nb);
        creerSommet(nouveauGraphe, nb);
    }
    int A;
    printf("\nNombre d'aretes:");
    scanf("%d", &A);
    for (int i = 0; i < A; i++){
        int voisin1, voisin2;
        printf("-------------- Arete numero %d --------------\n", i+1);
        printf("Indice du premier voisin :");
        scanf("%d", &voisin1);
        printf("Indice du second voisin :");
        scanf("%d", &voisin2);
        ajouterArete(nouveauGraphe, voisin1, voisin2);
    }
    return nouveauGraphe;
}

int rechercherDegre(Graphe* g){
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return 0;}
    int b=0;
    Sommet* sommetd = g->premier;
    while(sommetd != NULL){
        Voisin* voisinAct = sommetd->voisins;
        int a=0;
        while(voisinAct!= NULL){
            a+=1;
            voisinAct= voisinAct->suivant;
            if(a>b){
                b=a;
            }
        }
        sommetd = sommetd->suivant;
    }
    printf("Le degre maximal de tous les sommets du graphe est %d\n", b);
    return b;
}

void supprimerSommet(Graphe* g, int id) {
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return;}
    Sommet* supp = rechercherSommet(g, id);

    if (g->premier == supp) {
        g->premier = supp->suivant;
        free(supp);
    }
    else {
        for (Sommet* s = g->premier; s != NULL; s = s->suivant) {
            Voisin* voisinPrecedent = NULL;
            Voisin* voisinAct = s->voisins;
            if (voisinAct != NULL && voisinAct->indice == id) {
                s->voisins = s->voisins->suivant;
                free(voisinAct);
                continue;
            }
            while (voisinAct != NULL && voisinAct->indice != id) {
                voisinPrecedent = voisinAct;
                voisinAct = voisinAct->suivant;
            }
            if (voisinAct != NULL && voisinAct->indice == id) {
                voisinPrecedent->suivant = voisinAct->suivant;
                free(voisinAct);
            }
        }
        Sommet* precedent = g->premier;
        while (precedent->suivant != supp){precedent = precedent->suivant;}
        precedent->suivant = supp->suivant;
        free(supp);
    }
}

int contientBoucle(Graphe* g){
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return 0;}
    Sommet * sommet = g->premier;
    int a =0;
    while (sommet != NULL) {
        Voisin* voisin = sommet->voisins;
        while (voisin!= NULL ){
            if (voisin->indice == sommet->indice){
                a=1;
                break;
            }
            voisin = voisin->suivant;
        }
        sommet = sommet->suivant;
    }
    return a;
}

void fusionnerSommet(Graphe* g, int idSommet1, int idSommet2) {
    if (g == NULL){printf("--> Aucun graphe existe. Creez d'abord un graphe <-- "); return;}
    Sommet* sommet1 = rechercherSommet(g, idSommet1);
    Sommet* sommet2 = rechercherSommet(g, idSommet2);

    if (sommet1 == NULL || sommet2 == NULL) {
        printf("Erreur : L'un des deux sommets n'existe pas dans le graphe.\n");
        return;
    }

    Sommet* sommetMin = (idSommet1 < idSommet2) ? sommet1 : sommet2;
    Sommet* sommetMax = (idSommet1 < idSommet2) ? sommet2 : sommet1;

    Voisin* voisinCourant = sommetMax->voisins;
    while (voisinCourant != NULL) {
        ajouterArete(g, sommetMin->indice, voisinCourant->indice);
        voisinCourant = voisinCourant->suivant;
    }
    supprimerSommet(g, sommetMax->indice);
}


int afficherMenu() {
    printf("======= Menu =======\n");
    printf("1. Creer un graphe vide\n");
    printf("2. Construire un graphe de N sommets\n");
    printf("3. Ajouter un sommet\n");
    printf("4. Ajouter une arete\n");
    printf("5. Afficher un graphe\n");
    printf("6. Donner le degre maximal du graphe\n");
    printf("7. Supprimer un sommet\n");
    printf("8. Verifier si le graphe contient une boucle\n");
    printf("9. Fusionner deux sommets\n");
    printf("9. Quitter\n");

    int choix;
    Graphe* nouveauGraphe;

    do {
        printf("\n[MENU] Entrez votre choix :");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Nous allons creer un graphe vide.\n");
                nouveauGraphe = creerGraphe();
                break;
            case 2:
                printf("Nous allons construire un graphe. Combien de sommets voulez-vous qu'il comporte?\n");
                int N;
                scanf("%d", &N);
                nouveauGraphe = construireGraphe(N);
                afficherGraphe(nouveauGraphe);
                break;
            case 3:
                printf("Nous allons ajouter un sommet. Quel sera son indice?\n");
                int id;
                scanf("%d", &id);
                creerSommet(nouveauGraphe, id);
                break;
            case 4:
                printf("Nous allons ajouter une arete au graphe.\n");
                printf("Nom du premier voisin :\n");
                int id1, id2;
                scanf("%d", &id1);
                printf("Nom du second voisin :\n");
                scanf("%d", &id2);
                ajouterArete(nouveauGraphe, id1, id2);
                break;
            case 5:
                printf("Nous allons afficher le graphe :\n");
                afficherGraphe(nouveauGraphe);
                break;
            case 6:
                rechercherDegre(nouveauGraphe);
                break;
            case 7:
                printf("Quel sommet voulez-vous supprimer?\n");
                int supp;
                scanf("%d", &supp);
                supprimerSommet(nouveauGraphe, supp);
                break;
            case 8:
                if (contientBoucle(nouveauGraphe)==1){
                    printf("Il y'a bien une boucle dans le graphe!\n");
                }
                else {
                    printf("Pas de boucle dans le graphe\n");
                }
                break;
            case 9:
                printf("Nous allons Fuionner deux sommets. L'indice du nouveau sommet sera le plus petit.\n");
                printf("Nom du premier sommet :\n");
                int s1, s2;
                scanf("%d", &s1);
                printf("Nom du second sommet :\n");
                scanf("%d", &s2);
                fusionnerSommet(nouveauGraphe, s1, s2);
                break;
            case 10:
                printf("Au revoir !\n");
                Sommet *sommetActu = nouveauGraphe->premier;
                do
                {
                    Sommet *sommetAsupp = sommetActu;
                    sommetActu = sommetActu->suivant;
                    free(sommetAsupp);
                }
                while(sommetActu != NULL);
                free(nouveauGraphe);
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 10);
    return 0;
}
