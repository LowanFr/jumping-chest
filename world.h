#ifndef LOGICAL_H
#define LOGICAL_H

/**
 * @file world.h
 * @brief Header concernant le module : world
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 14 Novembre 2022
 */
#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "sdl2-light.h"
#include "constant.h"
#include "functions_files.h"

/**
 * Définition d'un nouveau type appelé textures_t qui est un pointeur vers une struct sprite_s.
 */
struct sprite_s{
    SDL_Rect DestR; /*!< Champ concernant la destination de l'image. */
    SDL_Rect SrcR; /*!< Champ concernant la source de l'image. */
    int v; /*!< Champ concernant la vitesse de l'image. */
    bool is_visible; /*!< Champ concernant l'état de visibilité de l'image. */
    bool is_deleted; /*!< Champ concernant l'état de suppression de l'image. */
};
typedef struct sprite_s sprite_t;

/**
 * @brief Définition d'un nouveau type appelé map_t qui est un pointeur vers une struct map_s.
 */
struct map_s{
    int** tab; /*!< Champ désignant un tableau symbolisant la map. */
    int nb_row; /*!< Champ lié aux nombres de lignes de la map. */
    int nb_col; /*!< Champ lié aux nombres de colonnes de la map. */
    SDL_Rect** DestR; /*!< Champ désignant un tableau de rectangle de destination. */
};
typedef struct map_s map_t;

/**
 * @brief Définition d'un nouveau type appelé joueur_t qui est un pointeur vers une structure joueur_s.
 */
struct world_s {
    sprite_t *blocks; /*!<  Champ désignant toutes les images des blocs. */
    sprite_t *player; /*!<  Champ désignant l'image du player. */
    map_t *map; /*!<  Champ désignant la map du jeu. */
    bool end; /*!<  Champ désignant la fin de la partie. */
};
typedef struct world_s world_t;

/**
 * @brief Représentation des ressources
 */
struct ressources_s {
    SDL_Texture *background; /*!< Ressource liée à l'image du fond de l'écran. */
    SDL_Texture *player; /*!< Ressource liée à l'image du player*/
    SDL_Texture *blocks; /*!< Ressource liée à l'image des blocks*/
};
typedef struct ressources_s ressources_t;

/**
 * @brief Modifie l'image pour qu'elle devienne invisible.
 * @param sprite L'image
 */
void set_invisible(sprite_t *sprite);

/**
 * @brief Initialisation du monde.
 * @param world Le monde
 */
void init_world(world_t *world);

/**
 * @brief Initialisation de l'image.
 * @param sprite L'image
 * @param x1 L'abscisse pour la source de l'image
 * @param y1 L'ordonnée pour la source de l'image
 * @param w1 La longueur de l'image pour la source
 * @param h1 La hauteur de l'image pour la source
 * @param x2 L'abscisse pour la destination de l'image
 * @param y2 L'ordonnée pour la destination de l'image
 * @param w2 La longueur pour la destination de l'image
 * @param h2 La hauteur pour la destination de l'image
 */
void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif