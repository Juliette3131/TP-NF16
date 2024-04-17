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
    if (g == NULL){exit(EXIT_FAILURE);}
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

void afficherGraphe(Graphe *g)
{
    if (g == NULL){exit(EXIT_FAILURE);}
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
