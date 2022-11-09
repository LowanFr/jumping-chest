#ifndef JOUEUR_H
#define JOUEUR_H

#include "world.h"

// Defining a new type called etat_clavier_t which is a pointer to a struct etat_clavier_s.
struct etat_clavier_s {
    bool left;
    bool right;
    bool space;
};
typedef struct etat_clavier_s etat_clavier_t;

// Defining a new type called joueur_t which is a pointer to a struct joueur_s.
struct joueur_s {
    // todo: Sprite du joueur dans joueur_t 
    bool saut;
    int tempsDepuisLeDebutDuSaut;
    int ground;
};
typedef struct joueur_s joueur_t;

void deplacement_joueur(etat_clavier_t *touches, joueur_t *joueur, sprite_t *sprite_joueur);

#endif