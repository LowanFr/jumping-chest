#ifndef PLAYER_H
#define PLAYER_H

/**
 * @file player.h
 * @brief Header du module : player
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 30 Novembre 2022
 */

#include "interaction.h"

/**
 * @brief La gravité, sert au joueur de retomber.
 */
#define GRAVITY 2

/**
 * @brief La vitesse du joueur sur l'axe des ordonnées (saut).
 */
#define JUMP_SPEED 30



/**
 * @brief Gestion du déplacement du joueur.
 * @param touches Les touches
 * @param player Le joueur
 */
void player_movement(keyboard_status_t *touches, sprite_t *player);

/**
 * @brief Vérification de toutes les collisions.
 * @param world Le monde
 */
void handle_collision(game_t *game, world_t *world, sprite_t *player, keyboard_status_t *key);

/**
 * @brief Vérification de collision avec un coffre
 * @param player Le joueur
 * @param sprite Le bloc
 */
void handle_collision_chest(world_t *world, sprite_t *player, sprite_t *sprite, keyboard_status_t *key);

/**
 * @brief Vérification des collisions entre le joueur et les pièces
 * @param world Le monde
 * @param player Le joueur
 * @param blob Le blob
 */
void handle_collision_blobs(game_t *game, world_t *world, sprite_t *player, sprite_t *blob);

/**
 * @brief Vérification de collision avec un bloc solide.
 * @param player Le joueur
 * @param sprite Le bloc
 */
void handle_collision_solidBlock(sprite_t *player, sprite_t *sprite);

/**
 * @brief Gestion des collisions entre le joueur et les pièces.
 * @param game La partie
 * @param player Le joueur
 * @param sprite Le bloc
 */
void handle_collision_pieces(game_t *game, sprite_t *player, sprite_t *sprite);

#endif
