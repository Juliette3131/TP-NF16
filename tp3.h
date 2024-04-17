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
