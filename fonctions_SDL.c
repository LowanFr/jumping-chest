#include "fonctions_SDL.h"

SDL_Texture* charger_image(const char* nomFichier, SDL_Renderer* renderer) {
    // Chargement de l'image à partir du chemin
    SDL_Surface* surface = SDL_LoadBMP(nomFichier);

    // Conversion de la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* charger_image_transparente(const char* nomFichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    // Chargement de l'image à partir du chemin
    SDL_Surface* surface = SDL_LoadBMP(nomFichier);

    // Récupération de la valeur (RGB) au format donné puis application sur la surface
    Uint32 colorKey = SDL_MapRGB(surface->format, r, g, b);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);

    // Conversion de la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color) {
    // Écrire le texte sur une surface SDL
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);

    //Convertir la surface de l'image au format texture
    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return image;
}