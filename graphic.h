#ifndef GRAPHIC_H
#define GRAPHIC_H

/**
 * @file graphic.h
 * @brief Header du module de la partie graphique
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 28 Novembre 2022
 */
#include "world.h"

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
 * @brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * @param renderer le renderer
 * @param ressources les ressources du jeu
*/
void apply_background(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * @brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * @param renderer le renderer
 * @param texture les ressources du jeu
 * @param sprite les données de l'image
 */
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

/**
 * @brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * @param renderer la surface de l'écran de jeu
 * @param world les données du monde
 * @param ressources les ressources du jeu
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources);

/**
 * @brief Charge une image .BMP
 * @param nomFichier Le nom du fichier
 * @param renderer Le rendu
 * @return
 */
SDL_Texture* charger_image(const char* nomFichier, SDL_Renderer* renderer);

#endif