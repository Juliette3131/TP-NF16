int main(){
   int choix;
   Graphe* nouveauGraphe;

    do {
        afficherMenu();
        printf("Entrez votre choix : ");
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
                break;
            case 3:
                printf("Nous allons ajouter un sommet. Comment voulez-vous qu'il s'appelle?\n");
                int id;
                scanf("%d", &id);
                creerSommet(nouveauGraphe, id);
                break;
            case 4:
                printf("Nous allons ajouter une arete au graphe\n");
                printf("Nom du premier voisin : \n");
                int id1, id2;
                scanf("%d", &id1);
                printf("Nom du duexième voisin : \n");
                scanf("%d", &id2);
                ajouterArete(nouveauGraphe, id1, id2);
                break;
            
            case 5:
                printf("Nous allons afficher le graphe.\n");
                afficherGraphe(nouveauGraphe);
                break;
            case 6:
                int deg= rechercherDegre(nouveauGraphe);
                printf("%d", deg);
                break;
            case 7:
                printf("Quel sommet voulez-vous supprimer?\n");
                int supp;
                scanf("%d", &supp);
                supprimerSommet(nouveauGraphe, supp);
                break;
            case 8:
                int n = contientBoucle(nouveauGraphe);
                if (n==1){
                    printf("Il y'a bien une boucle dans le graphe!\n");
                }
                else {
                    printf("Pas de boucle dans le graphe\n");
                }
                break;
            case 9:
                printf("Nous allons Fuionner deux sommets. L'indice gardé sera le plus petit.\n");
                printf("Nom du premier sommet : \n");
                int s1, s2;
                scanf("%d", &s1);
                printf("Nom du duexième sommet : \n");
                scanf("%d", &s2);
                fusionnerSommet(nouveauGraphe, s1, s2);
                break;
            case 10:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 10);

    return 0;
}
