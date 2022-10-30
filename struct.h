#ifndef STRUCT_H
#define STRUCT_H
#include <SDL.h>

// Defining a new type called etat_clavier_t which is a pointer to a struct etat_clavier_s.
struct etat_clavier_s {
    bool left;
    bool right;
    bool space;
};
typedef struct etat_clavier_s etat_clavier_t;

// Defining a new type called joueur_t which is a pointer to a struct joueur_s.
struct joueur_s {
    bool saut;
    int tempsDepuisLeDebutDuSaut;
    int ground;
};
typedef struct joueur_s joueur_t;

// Defining a new type called textures_t which is a pointer to a struct textures_s.
struct textures_s{
    SDL_Rect DestR;
    SDL_Rect SrcR;
};
typedef struct textures_s textures_t;

// Defining a new type called world_t which is a pointer to a struct world_s.
struct world_s{
    textures_t *textures;
};
typedef struct world_s world_t;

#endif