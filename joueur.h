#ifndef JOUEUR_H
#define JOUEUR_H

#include "world.h"
#include "clavier.h"


// Defining a new type called joueur_t which is a pointer to a struct joueur_s.
struct joueur_s {
    // todo: Sprite du joueur dans joueur_t 
    bool saut;
    int tempsDepuisLeDebutDuSaut;
    int ground;
};
typedef struct joueur_s joueur_t;

void init_joueur(joueur_t *joueur);

void deplacement_joueur(etat_clavier_t *touches, joueur_t *joueur, sprite_t *sprite_joueur);



#endif