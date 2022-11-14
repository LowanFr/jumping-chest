#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H
#include <SDL_ttf.h>
#include <SDL.h>

/**
 * Chargement d'une image et renvoie un pointeur vers la texture.
 * @param nomFichier Nom/Chemin vers un fichier
 * @param renderer Rendu
 * @return Texture avec l'image
 */
SDL_Texture* charger_image(const char* nomFichier, SDL_Renderer* renderer);

/**
 * Chargement d'une image et renvoie un pointeur vers la texture.
 * @param nomFichier Nom/Chemin vers un fichier
 * @param renderer Rendu
 * @param r Taux de rouge
 * @param g Taux de vert
 * @param b Taux de bleu
 * @return Texture avec l'image (avec transparence)
 */
SDL_Texture* charger_image_transparente(const char* nomFichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

/**
 * Chargement d'un texte et renvoie un pointeur vers la texture.
 * @param message Message à afficher
 * @param renderer Rendu
 * @param font Police d'écriture
 * @param color Couleur
 * @return Texture avec le texte
 */
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color);
#endif