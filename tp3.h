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
