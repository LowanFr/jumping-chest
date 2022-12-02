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
 * @param world Les données du monde
 * @param ressources Les ressources du jeu
 * @param keyboard Le statut du clavier
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard);

/**
 * @brief Charge une image .BMP.
 * @param fileName Le nom du fichier
 * @param renderer Le moniteur de rendu
 * @return
 */
SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer);

/**
 * @brief Gère toutes les animations.
 * @param world Les données du monde
 * @param i L'abscisse du bloc
 * @param j L'ordonnée du bloc
 */
void handle_animations(world_t *world, int i, int j);

/**
 * @brief Gère l'animation d'une pièce.
 * @param sprites Les données des images
 * @param i L'abscisse de la pièce
 * @param j L'ordonnée de la pièce
 */
void coin_animations(sprite_t **sprites, int i, int j);

#endif
