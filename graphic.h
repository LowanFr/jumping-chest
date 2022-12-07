#ifndef GRAPHIC_H
#define GRAPHIC_H

/**
 * @file graphic.h
 * @brief Header du module de la partie graphique.
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "world.h"
#include "interaction.h"
#include "player.h"

/**
 * @brief Nettoie les ressources.
 * @param ressources les ressources du jeu
*/
void clean_ressources(ressources_t *ressources);

/**
 * @brief Initialise les ressources.
 * @param renderer Le moniteur de rendu
 * @param ressources Les ressources du jeu
*/
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * @brief Rafraichit l'écran en fonction de l'état des données du monde.
 * @param renderer Le moniteur de rendu
 * @param game La partie
 * @param world Les données du monde
 * @param ressources Les ressources du jeu
 * @param keyboard Le statut du clavier
 */
void refresh_graphics(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources,
                      keyboard_status_t *keyboard);

/**
 * @brief Gère toutes les animations.
 * @param world Les données du monde
 * @param block Le bloc
 */
void handle_animations(world_t *world, sprite_t *block);

/**
 * @brief Gère l'animation d'une pièce.
 * @param block Le bloc
 */
void coin_animations(sprite_t *block);

/**
 * @brief Actualisation du menu d'accueil
 * @param world Le monde
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 */
void refresh_menu(world_t *world, SDL_Renderer *renderer, ressources_t *ressources);

#endif
