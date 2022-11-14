#ifndef CLAVIER_H
#define CLAVIER_H

#include <stdbool.h>
#include <SDL.h>
#include "world.h"


// Defining a new type called etat_clavier_t which is a pointer to a struct etat_clavier_s.
struct keyboard_status_s {
    SDL_Event events; // Événements liés à la fenêtre
    bool left;
    bool right;
    bool space;
};
typedef struct keyboard_status_s keyboard_status_t;

void refresh_keys(world_t *world, keyboard_status_t *keys);

void init_touches(keyboard_status_t *touches);

#endif