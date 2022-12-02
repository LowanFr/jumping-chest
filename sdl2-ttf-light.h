#ifndef SDL2_TTF_LIGHT_H
#define SDL2_TTF_LIGHT_H

/**
 * @file sdl2-ttf-light.h
 * @authors Esteban DOUILLET, SCHNEIDER Paul
 * @brief Header du module de SDL2 TTF (light)
 * @date 2 Décembre 2022
 */

#include <SDL.h>
#include <SDL_ttf.h>

/**
 * @brief Initialisation de SDL2 TTF
 */
void init_ttf();

/**
 * @brief Chargement d'une police
 * @param path Le chemin
 * @param font_size Le taille
 * @return La police
 */
TTF_Font *load_font(const char *path, int font_size);

/**
 * @brief Application du texte sur le rendu
 * @param renderer Le moteur de rendu
 * @param x L'abscisse du texte
 * @param y L'ordonnée du texte
 * @param w La taille
 * @param h La hauteur
 * @param text Le texte
 * @param font La police
 */
void apply_text(SDL_Renderer *renderer, int x, int y, int w, int h, const char *text, TTF_Font *font);

/**
 * @brief Libère la mémoire de la police
 * @param font La police
 */
void clean_font(TTF_Font *font);

/**
 * @brief Libère la mémoire de SDL2 TTF
 */
void clean_ttf();

#endif
