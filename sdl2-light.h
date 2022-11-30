#ifndef SDL2_LIGHT_H
#define SDL2_LIGHT_H

/**
 * @file sdl2-light.h
 * @brief Header de la sur-couche de SDL2 pour simplifier son utilisation pour le projet.
 * @author DOUILLET Esteban & SCHNEIDER Paul
 * @date 30 Novembre 2022
*/

#include <SDL.h>

/**
 * @brief Nettoie le renderer et la fenêtre du jeu en mémoire.
 * @param renderer Le moteur de rendu
 * @param window La fenêtre
*/
void clean_sdl(SDL_Renderer *renderer, SDL_Window *window);

/**
 * @brief Initialise la SDL.
 * Elle crée la fenêtre du jeu ainsi que le renderer.
 * @param window La fenêtre du jeu
 * @param renderer Le moteur de rendu
 * @param width La largeur de l'écran de jeu
 * @param height La hauteur de l'écran de jeu
 * @return -1 en cas d'erreur, 0 sinon
*/
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
 * @brief Nettoie une texture en mémoire.
 * @param texture La texture à nettoyer
*/
void clean_texture(SDL_Texture *texture);

/**
 * @brief Vide le contenu graphique du renderer lié à l'écran de jeu.
 * @param renderer Le moteur de rendu
*/
void clear_renderer(SDL_Renderer *renderer);

/**
 * @brief Mise à jour de l'écran avec le contenu du moteur de rendu.
 * @param renderer Le moteur de rendu
*/
void update_screen(SDL_Renderer *renderer);

#endif
