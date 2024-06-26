Graphe* creerGraphe(){
  Graphe* nouveauGraphe = malloc(sizeof(Graphe));
  if (nouveauGraphe == NULL) {
    return NULL;
  }
  nouveauGraphe -> premier = NULL; 
  return nouveauGraphe;
}

void creerSommet(Graphe *g, int id) {
    if (g == NULL) {
        printf("Erreur : Le graphe est NULL\n");
        return;
    }

    Sommet* nouveau = malloc(sizeof(Sommet));
    if (nouveau == NULL) {
        printf("Erreur : Échec de l'allocation mémoire pour le nouveau sommet\n");
        return;
    }

    nouveau->indice = id;

    if (g->premier == NULL || g->premier->indice > id) {
        nouveau->suivant = g->premier;
        g->premier = nouveau;
        return;
    }

    Sommet* act = g->premier;
    while (act->suivant != NULL && act->suivant->indice < id) {
        act = act->suivant;
    }

    if (act->suivant != NULL && act->suivant->indice == id) {
        printf("Ce sommet existe déjà\n");
        free(nouveau); 
        return;
    }
    nouveau->suivant = act->suivant;
    act->suivant = nouveau;
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
    if (g == NULL) { exit(EXIT_FAILURE); }
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

void afficherGraphe(Graphe* g){
  Sommet* sommete = g->premier;
  while(sommete != NULL){
    printf("| \nv\n");
    printf("%d", sommete-> indice);
    Voisin* voisinAct = sommete->voisins;
    while(voisinAct!= NULL){
        printf("->");
        printf("%d", voisinAct->indice);
        voisinAct= voisinAct->suivant;
    }
    printf("\n");
    sommete = sommete -> suivant;
  }  
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
    Sommet* sommet1 = rechercherSommet(g, idSommet1);
    Sommet* sommet2 = rechercherSommet(g, idSommet2);
 
    if (sommet1 == NULL || sommet2 == NULL) {
        printf("L'un des deux sommets n'existe pas dans le graphe\n");
        return;
    }
 
    Sommet* sommetMin = (idSommet1 < idSommet2) ? sommet1 : sommet2;
    Sommet* sommetMax = (idSommet1 < idSommet2) ? sommet2 : sommet1;
 
    Voisin* voisinCourant = sommetMax->voisins;
    while (voisinCourant != NULL) {
        if (voisinCourant->indice!= sommetMin->indice){
        ajouterArete(g, sommetMin->indice, voisinCourant->indice);
        }
        voisinCourant = voisinCourant->suivant;
    }
    supprimerSommet(g, sommetMax->indice);
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
