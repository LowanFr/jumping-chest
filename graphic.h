#ifndef GRAPHIC_H
#define GRAPHIC_H

/**
 * @file graphic.h
 * @brief Header du module de la partie graphique
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "world.h"
#include "interaction.h"

/**
 * @brief La fonction nettoie les ressources
 * @param ressources les ressources du jeu
*/
void clean_ressources(ressources_t *ressources);

/**
 * @brief La fonction initialise les ressources
 * @param renderer la surface correspondant à l'écran de jeu
 * @param ressources les ressources du jeu
*/
void init_ressources(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * @brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * @param renderer la surface de l'écran de jeu
 * @param world les données du monde
 * @param ressources les ressources du jeu
 * @param keyboard le statut du clavier
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard);

/**
 * @brief Charge une image .BMP
 * @param fileName Le nom du fichier
 * @param renderer Le rendu
 * @return
 */
SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer);

/**
 * @brief Gère toutes les animations
 * @param world Les données du monde
 * @param i L'abscisse du bloc
 * @param j L'ordonnée du bloc
 */
void handle_animations(world_t *world, int i, int j);

/**
 * @brief Gère l'animation d'une pièce
 * @param world Les données du monde
 * @param i L'abscisse de la pièce
 * @param j L'ordonnée de la pièce
 */
void coin_animations(int **tab, int i, int j);

#endif
