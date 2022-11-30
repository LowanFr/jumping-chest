#ifndef WORLD_H
#define WORLD_H

/**
 * @file world.h
 * @brief Header concernant le module : world
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */

#include <stdlib.h>
#include <SDL.h>
#include <stdbool.h>
#include "sdl2-light.h"
#include "map.h"

/**
 * @brief La largeur de l'image du joueur
 */
#define WIDTH_PLAYER 56

/**
 * @brief La hauteur de l'image du joueur
 */
#define HEIGHT_PLAYER 96

/**
 * @brief La vitesse du joueur sur l'axe des abscisses (marche)
 */
#define SPEED_X_WALK 10

/**
 * @brief L'abscisse de la première texture sur la tile-map
 */
#define X_FIRST_TEXTURE 4

/**
 * @brief L'ordonnée de la première texture sur la tile-map
 */
#define Y_FIRST_TEXTURE 72

/**
 * @brief La hauteur/largeur d'une texture
 */
#define SIZE_TEXTURES 64

/**
 * @brief Le nombre de textures dans une tile-map
 */
#define NUMBER_OF_TEXTURES 33

/**
 * @brief La taille de la ligne bleu qui sépare deux textures
 */
#define SHIFT_TEXTURE 4

/**
 * @brief Définition de la caméra avec ses coordonnées et ses dimensions
 */
struct cam_s {
    int x;  /*!< Champ concernant l'abscisse de la caméra. */
    int y;  /*!< Champ concernant l'ordonnée de la caméra. */
    int h;  /*!< Champ concernant la hauteur de la caméra. */
    int w;  /*!< Champ concernant la largeur de la caméra. */
};
typedef struct cam_s cam_t;

/**
 * @brief Définition d'une image avec ses coordonnées et sa vitesse.
 */
struct sprite_s {
    SDL_Rect DestR; /*!< Champ concernant la destination de l'image. */
    SDL_Rect SrcR; /*!< Champ concernant la source de l'image. */
    int v; /*!< Champ concernant la vitesse de l'image. */
};
typedef struct sprite_s sprite_t;

/**
 * @brief Définition de la carte avec chaque bloc et les coordonnées qui conviennent
 */
struct map_s {
    int **tab; /*!< Champ désignant un tableau symbolisant les identifiants des blocs. */
    int nb_row; /*!< Champ lié aux nombres de lignes de la map. */
    int nb_col; /*!< Champ lié aux nombres de colonnes de la map. */
};
typedef struct map_s map_t;

/**
 * @brief Définition du monde avec tous les éléments qu'il contient.
 */
struct world_s {
    sprite_t *textures; /*!<  Champ désignant toutes les images des blocs. */
    sprite_t **blocks; /*!<  Champ désignant toutes les images des blocks. */
    sprite_t *player; /*!<  Champ désignant l'image du joueur. */
    cam_t *cam; /*!<  Champ désignant la camera. */
    map_t *map; /*!<  Champ désignant la map du jeu. */
    int cycles;
    bool end; /*!<  Champ désignant la fin de la partie. */
};
typedef struct world_s world_t;

/**
 * @brief Définition des ressources pour chaque élément du jeu.
 */
struct ressources_s {
    SDL_Texture *background; /*!< Ressource liée à l'image du fond de l'écran. */
    SDL_Texture *player; /*!< Ressource liée à l'image du joueur. */
    SDL_Texture *blocks; /*!< Ressource liée à l'image des blocs. */
};
typedef struct ressources_s ressources_t;


/**
 * @brief Repositionnement de la caméra en se basant sur les coordonnées de l'utilisateur.
 * @param camera La caméra
 * @param player Le joueur
 */
void repositioning_camera(cam_t *camera, SDL_Rect *player);

/**
 * @brief Initialisation du monde.
 * @param world Le monde
 */
void init_world(world_t *world);

/**
 * @brief Initialisation de la caméra.
 * @param world Le monde
 * @param camera La caméra à initialiser
 * @param h La hauteur de la caméra
 * @param w La largeur de la caméra
 */
void init_cam(world_t *world, cam_t *camera, int h, int w);

/**
 * @brief Initialisation d'une image.
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
