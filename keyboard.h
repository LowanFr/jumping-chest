#ifndef CLAVIER_H
#define CLAVIER_H

/**
 * @brief Fichier représentant le module du clavier
 * @file keyboard.h
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */

#include <stdbool.h>
#include <SDL.h>
#include "world.h"

/**
 * @brief Définition d'un nouveau type appelé keyboard_state_t qui est un pointeur vers une structure keyboard_state_s.
 */
struct keyboard_status_s {
    SDL_Event events; /*!< Champ concernant les événements liés à la fenêtre. */
    bool left; /*!< Champ concernant la flèche gauche. */
    bool right; /*!< Champ concernant la flèche droite. */
    bool space; /*!< Champ concernant l'espace'. */
    bool lastIsLeft; /*!< Champ concernant la dernière touche appuyé. */
};
typedef struct keyboard_status_s keyboard_status_t;

/**
 * @brief Actualisation des actions sur le clavier
 * @param world Le monde
 * @param keys Le statut du clavier
 */
void refresh_keys(world_t *world, keyboard_status_t *keys);

/**
 * @brief Initialisation du status du clavier par défaut
 * @param touches Le statut du clavier
 */
void init_touches(keyboard_status_t *touches);

#endif