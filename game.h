#ifndef GAME_H
#define GAME_H

/**
 * @file game.h
 * @brief Header concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Définition d'une partie d'un joueur
 */
struct game_s {
    char *level; /*!< Champ concernant le niveau. */
    int score; /*!< Champ concernant le score actuel. */
    char *pseudo; /*!< Champ concernant le pseudonyme associé à la partie. */
    char *startDate; /*!< Champ concernant la date à laquelle la partie est lancée. */
    char *endDate; /*!< Champ concernant la date à laquelle la partie est finie. */
};
typedef struct game_s game_t;

/**
 * @brief Initialiser la partie
 * @param game La partie
 */
void init_game(game_t *game);

/**
 * @brief Libérer la mémoire de la partie
 * @param game La partie
 */
void clean_game(game_t *game);

#endif
