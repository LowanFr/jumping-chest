#ifndef STRUCT_H
#define STRUCT_H
#include <SDL.h>

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

struct textures_s{
    // Définition du rectangle source pour obj
    // Définition du rectangle destination pour obj
    SDL_Rect SrcR, DestR;
};typedef struct textures_s textures_t;

struct world_s{
    textures_t *textures;
};typedef struct world_s world_t;




#endif