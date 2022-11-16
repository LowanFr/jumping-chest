#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file player.h
 * @brief Header du module : player
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 14 Novembre 2022
 */

#include "world.h"
#include "keyboard.h"

/**
 * \brief Gravité, sert au player de retomber
 */
#define GRAVITE 2

/**
 * @brief Définition d'un nouveau type appelé player_t qui est un pointeur vers une struct player_s.
 */
struct player_s {
    // todo: Sprite du player dans joueur_t
    bool saut; /*!< Champ vérifiant si le joueur est en saut. */
    int timeSinceJumpStart; /*!< La durée depuis laquelle le joueur est en saut. */
    int ground; /*!< Le sol sur lequel il doit atterrir. */
};
typedef struct player_s player_t;

/**
 * @brief Définition des données du joueur
 * @param player Le joueur
 */
void init_player(player_t *player);

/**
 * @brief Gestion du déplacement du joueur
 * @param touches Les touches
 * @param player Le joueur
 * @param sprite_player L'image du joueur
 */
void player_movement(keyboard_status_t *touches, player_t *player, sprite_t *sprite_player);

#endif