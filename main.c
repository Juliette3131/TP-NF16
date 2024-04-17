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
