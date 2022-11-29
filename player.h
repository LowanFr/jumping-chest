#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file player.h
 * @brief Header du module : player
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */

#include "keyboard.h"

/**
 * \brief Gravité, sert au player de retomber
 */
#define GRAVITE 2

/**
 * \brief Vitesse du player sur l'axe Y (saut)
 */
#define VITESSE_Y_SAUT 30

/**
 * @brief Définition d'un nouveau type appelé player_t qui est un pointeur vers une struct player_s.
 */
struct player_s {
    sprite_t *sprite; /*!< Champ concernant l'image du joueur. */
    SDL_Rect prec; /*!< Champ concernant les coordonnées précédentes du joueur. */
    bool saut; /*!< Champ vérifiant si le joueur est en saut. */
    int timeSinceJumpStart; /*!< La durée depuis laquelle le joueur est en saut. */
    int ground; /*!< Le sol sur lequel il doit atterrir. */
};
typedef struct player_s player_t;

/**
 * @brief Définition des données du joueur
 * @param player Le joueur
 * @param world Le monde
 */
void init_player(player_t *player, world_t *world);

/**
 * @brief Gestion du déplacement du joueur
 * @param touches Les touches
 * @param player Le joueur
 */
void player_movement(keyboard_status_t *touches, player_t *player);

/**
 * @brief Vérification de toutes les collisions
 * @param world Le monde
 * @param player Le joueur
 */
void handle_collision(world_t *world, player_t *player);

/**
 * @brief`Vérification de collision avec un bloc solide
 * @param world Le monde
 * @param player Le joueur
 */
void handle_collision_solidBlock(world_t *world, player_t *player);

#endif