#ifdef JOUEUR_H
#define JOUEUR_H

// Defining a new type called etat_clavier_t which is a pointer to a struct etat_clavier_s.
struct etat_clavier_s {
    bool left;
    bool right;
    bool space;
};
typedef struct etat_clavier_s etat_clavier_t;

#endif