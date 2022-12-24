#ifndef INTERACTION_H
#define INTERACTION_H

/**
 * @brief Fichier représentant le module des interactions.
 * @file interaction.h
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 30 Novembre 2022
 */

#include <stdbool.h>
#include <SDL.h>
#include "graphic.h"

/**
 * @brief Actualisation des actions sur le clavier.
 * @param world Le monde
 * @param keyboard Le statut du clavier
 * @param event L'événement
 */
void refresh_keys(game_t *game, world_t *world, keyboard_status_t *keyboard, SDL_Event *event);

/**
 * @brief Initialisation du status du clavier par défaut.
 * @param keyboard Le statut du clavier
 */
void init_keyboard(keyboard_status_t *keyboard);

/**
 * @brief Actualisation des événements.
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 * @param mouse La souris
 * @param keyboard Le clavier
 * @param game La partie
 * @param world Le monde
 * @param event L'événement
 */
void handle_event(SDL_Renderer *renderer, ressources_t *ressources, mouse_status_t *mouse, keyboard_status_t *keyboard,
                  game_t *game, world_t *world, SDL_Event *event);

/**
 * @brief Initialisation de la souris.
 * @param mouse La souris
 * @param event L'événement
 */
void init_mouse(mouse_status_t *mouse);

/**
 * @brief Actualisation des actions de la souris.
 * @param mouse La souris
 */
void refresh_mouse(mouse_status_t *mouse, SDL_Event *event);

/**
 * @brief Actualisations des événements sur les boutons.
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 * @param game La partie
 * @param world  Le monde
 * @param mouseStatus Le status de la souris
 */
void handle_button(SDL_Renderer *renderer, ressources_t *ressources, game_t *game, world_t *world,
                   mouse_status_t *mouseStatus);

void write_pseudo(game_t *game, SDL_Keycode key);

#endif
