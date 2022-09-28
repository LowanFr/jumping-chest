#ifndef STRUCT_H
#define STRUCT_H

struct etat_clavier_s {
    bool left;
    bool right;
    bool space;
};
typedef struct etat_clavier_s etat_clavier_t;

struct joueur_s {
    bool saut;
    int tempsDepuisLeDebutDuSaut;
    int ground;
};
typedef struct joueur_s joueur_t;


#endif