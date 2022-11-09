#ifndef CLAVIER_H
#define CLAVIER_H

#include <stdbool.h>
#include <SDL.h>
#include "world.h"


// Defining a new type called etat_clavier_t which is a pointer to a struct etat_clavier_s.
struct etat_clavier_s {
    SDL_Event events; // Événements liés à la fenêtre
    bool left;
    bool right;
    bool space;
};
typedef struct etat_clavier_s etat_clavier_t;

void refresh_keys(world_t *world, etat_clavier_t *touches);

void init_touches(etat_clavier_t *touches);

#endif