#ifndef GRAPHIC_H
#define GRAPHIC_H

/**
 * @file graphic.h
 * @brief Header du module de la partie graphique.
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "world.h"
#include "sdl2-ttf-light.h"
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
 * @param game Le jeu
*/
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources, game_t *game);

/**
 * @brief Demande à l'utilisateur d'entrer son pseudonyme
 * @param renderer Le moteur de rendu
 * @param world Le monde
 * @param ressources Les ressources
 */
void askPseudo(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources);

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
void refresh_menu(game_t *game, world_t *world, SDL_Renderer *renderer, ressources_t *ressources);

/**
 * @brief Gère l'animation d'un blob.
 * @param block Le blob
 */
void blobs_animations(sprite_t *block);

/**
 * @brief Affiche tous les blocs du monde
 * @param game La partie
 * @param world Le monde
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 * @param keyboard Le clavier
 */
void display_blocks(game_t *game, world_t *world, SDL_Renderer *renderer, ressources_t *ressources,
                    keyboard_status_t *keyboard);

/**
 * @brief Affiche un bloc sur le monde
 * @param game La partie
 * @param world Le monde
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 * @param keyboard Le clavier
 * @param sprite L'image
 */
void display_block(game_t *game, world_t *world, SDL_Renderer *renderer, ressources_t *ressources,
                   keyboard_status_t *keyboard, sprite_t *sprite);

/**
 * @brief Affiche un blob sur le monde
 * @param renderer Le moteur de rendu
 * @param game La partie
 * @param world Le monde
 * @param ressources Les ressources
 * @param keyboard Le clavier
 * @param sprite L'image
 * @param rect Le rectangle adapté à la caméra
 */
void display_blobs(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard, sprite_t *sprite, SDL_Rect *rect);

/**
 * @brief Affiche le score de la partie
 * @param renderer Le moteur de rendu
 * @param game La partie
 * @param ressources Les ressources
 */
void display_score(SDL_Renderer *renderer, game_t *game, ressources_t *ressources);

/**
 * @brief Affiche les vies
 * @param renderer Le moteur de rendu
 * @param world Le monde
 * @param ressources Les ressources
 */
void display_lives(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * @brief Affiche le joueur
 * @param renderer Le moteur de rendu
 * @param world Le monde
 * @param ressources Les ressources
 * @param keyboard Le clavier
 */
void display_player(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard);

void display_menu(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources);
void display_main_menu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);
void display_pause_menu(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);
void display_waiting_menu(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources);

#endif
