#ifndef LOGICAL_H
#define LOGICAL_H

#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "sdl2-light.h"
#include "constante.h"

// Defining a new type called textures_t which is a pointer to a struct sprite_s.
struct sprite_s{
    SDL_Rect DestR;
    SDL_Rect SrcR;
    int v; /*!< Champ concernant la vitesse de l'image. */
    bool is_visible; /*!< Champ concernant l'état de visibilité de l'image. */
    bool is_deleted; /*!< Champ concernant l'état de suppression de l'image. */
};
typedef struct sprite_s sprite_t;

// Defining a new type called joueur_t which is a pointer to a struct joueur_s.
struct world_s {
    sprite_t *blocks;
    sprite_t *joueur;
    bool end;
};
typedef struct world_s world_t;

/**
 * \brief Représentation des ressources
 */
struct ressources_s {
    SDL_Texture *background; /*!< Ressource liée à l'image du fond de l'écran. */
    SDL_Texture *player; /*!< Ressource liée à l'image du joueur*/
    SDL_Texture *blocks; /*!< Ressource liée à l'image des blocks*/
    
};
/**
 * \brief Type qui correspond aux ressources du jeu
*/
typedef struct ressources_s ressources_t;

void set_invisible(sprite_t *sprite);

void init_world(world_t *world);

void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);


#endif