#ifndef SDL2_LIGHT_H
#define SDL2_LIGHT_H

/**
 * \file sdl2-light.g
 * \brief Header de la sur-couche de SDL2 pour simplifier son utilisation pour le projet
 * \author DOUILLET Esteban & SCHNEIDER Paul
 * \date 30 Novembre 2022
*/

#include <SDL.h>

/**
 * @brief La fonction nettoie le renderer et la fenêtre du jeu en mémoire
 * @param renderer le renderer à nettoyer
 * @param window la fenêtre à nettoyer
*/
void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);

/**
 * @brief La fonction initialise la SDL.
 * Elle crée la fenêtre du jeu ainsi que le renderer
 * @param window la fenêtre du jeu
 * @param renderer le renderer
 * @param width largeur de l'écran de jeu
 * @param height hauteur de l'écran de jeu
 * @return -1 en cas d'erreur, 0 sinon
*/
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
 * @brief La fonction nettoie une texture en mémoire
 * @param texture la texture à nettoyer
*/
void clean_texture(SDL_Texture *texture);

/**
 * @brief La fonction vide le contenu graphique du renderer lié à l'écran de jeu
 * @param renderer le renderer de l'écran
*/
void clear_renderer(SDL_Renderer *renderer);

/**
 * @brief La fonction met à jour l'écran avec le contenu du renderer
 * @param renderer le renderer de l'écran
*/
void update_screen(SDL_Renderer *renderer);

#endif
