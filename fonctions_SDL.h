#ifndef SDL2
#define SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * \brief La fonction charge une image
 * \param nomfichier nom du fichier à charger
 * \param renderer 
*/
SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer);

/**
 * \brief La fonction charge une image transparente
 * \param nomfichier nom du fichier à charger
 * \param renderer 
 * \param r red
 * \param g green
 * \param b blue
*/
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) ;

/**
 * \brief La fonction charge un texte
 * \param message message à afficher
 * \param renderer 
 * \param font
 * \param color
*/
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,
TTF_Font *font, SDL_Color color);
#endif