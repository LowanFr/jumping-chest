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
#include "sdl2-ttf-light.h"
#include "map.h"
#include "game.h"

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
 * @brief La gravité, sert au joueur de retomber.
 */
#define GRAVITY 2

/**
 * @brief La vitesse du joueur sur l'axe des ordonnées (saut).
 */
#define JUMP_BLOB_SPEED 20


/**
 * @brief L'indice de l'image du joueur dans la tile-map
 */
#define TEXTURE_INDEX_PLAYER (-1)

struct button_s {
    bool enable; /*!< Champ concernant l'état du bouton. */
    int type; /*!< Champ concernant le type du bouton. */
    SDL_Rect DestR; /*!< Champ concernant la destination du bouton. */
};
typedef struct button_s button_t;

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
    int textureIndex; /*!< Champ concernant l'index de la texture du bloc. */
    int v; /*!< Champ concernant la vitesse de l'image. */
    SDL_Rect prec; /*!< Champ concernant les coordonnées précédentes du joueur. */
    bool saut; /*!< Champ vérifiant si le joueur est en saut. */
    int timeSinceJumpStart; /*!< La durée depuis laquelle le joueur est en saut. */
    int ground; /*!< Le sol sur lequel il doit atterrir. */
    bool isright;
    bool isAttacked;
    bool print_e;
    
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
    sprite_t *letter_e; /*!< Champ liée à l'image de la lettre E*/
    cam_t *cam; /*!<  Champ désignant la camera. */
    map_t *map; /*!<  Champ désignant la map du jeu. */
    int cycles; /*!<  Champ désignant le nombre de cycle de jeu. */
    int hearts; /*!<  Champ désignant la map du jeu. */
    button_t *buttons; /*!<  Champ désignant les boutons */
    bool end; /*!<  Champ désignant la fin de la partie. */
    bool menu;
    bool pause;
    bool newLevel;
    int counter_score_vie;

};
typedef struct world_s world_t;

/**
 * @brief Définition des ressources pour chaque élément du jeu.
 */
struct ressources_s {
    SDL_Texture *background; /*!< Ressource liée à l'image du fond de l'écran. */
    SDL_Texture *player; /*!< Ressource liée à l'image du joueur. */
    SDL_Texture *blocks; /*!< Ressource liée à l'image des blocs. */
    SDL_Texture *newGame; /*!< Ressource liée à l'image pour lancer une nouvelle partie. */
    SDL_Texture *resume; /*!< Ressource liée à l'image du bouton pour reprendre une partie. */
    SDL_Texture *save; /*!< Ressource liée à l'image du bouton de sauvegarde. */
    SDL_Texture *exit; /*!< Ressource liée à l'image du bouton pour quitter. */
    SDL_Texture *letter_e; /*!< Ressource liée à l'image de la lettre E*/
    TTF_Font * score; /*!< Ressource liée au texte de la vie */
};
typedef struct ressources_s ressources_t;

/**
 * @brief Définition d'un clavier avec les touches majeures.
 */
struct keyboard_status_s {
    bool left; /*!< Champ concernant la flèche gauche. */
    bool right; /*!< Champ concernant la flèche droite. */
    bool space; /*!< Champ concernant l'espace'. */
    bool lastIsLeft; /*!< Champ concernant la dernière touche appuyé. */
    bool e;
};
typedef struct keyboard_status_s keyboard_status_t;

/**
 * @brief Définition d'une souris avec les boutons et les coordonnées.
 */
struct mouse_status_s {
    bool right; /*!< Champ concernant l'état du click gauche. */
    bool left; /*!< Champ concernant l'état du click droit. */
    int x; /*!< Champ concernant l'abscisse de la souris'. */
    int y; /*!< Champ concernant l'ordonnée de la souris. */
};
typedef struct mouse_status_s mouse_status_t;

/**
 * @brief Repositionnement de la caméra en se basant sur les coordonnées de l'utilisateur.
 * @param world Le monde
 */
void repositioning_camera(world_t *world);

/**
 * @brief Initialisation du monde.
 * @param game La partie
 * @param world Le monde
 * @param new_game Si c'est une nouvelle partie
 */
void init_world(game_t *game, world_t *world, bool new_game);

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
 * @param textureIndex L'indice de la texture de l'image
 */
void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int textureIndex, bool print_e);

/**
 * @brief Déplacement des blobs.
 * @param world Le monde
 * @param sprite L'image
 */
void blob_movement(world_t *world, sprite_t *sprite);

/**
 * @brief Libération de la mémoire du monde
 * @param world Le monde
 */
void clean_data(world_t *world);

/**
 * @brief Chargement des ressources du nouveau niveau.
 * @param renderer Le moteur de rendu
 * @param game La partie
 * @param ressources Les ressources
 * @param restart Si la partie redémarre
 */
void new_level(SDL_Renderer *renderer, game_t *game, ressources_t *ressources, bool restart);

/**
 * @brief Actualisation des ressources du niveau
 * @param renderer Le moteur de rendu
 * @param game La partie
 * @param ressources Les ressources
 * @param world Le monde
 */
void refresh_level(SDL_Renderer *renderer, game_t *game, ressources_t *ressources, world_t *world);

/**
 * @brief Charge une image .BMP.
 * @param fileName Le nom du fichier
 * @param renderer Le moniteur de rendu
 * @return
 */
SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer);

#endif
