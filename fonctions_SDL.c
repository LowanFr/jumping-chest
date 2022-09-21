#include "fonctions_SDL.h"

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer){
    //Charger une image
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    //Convertir la surface de l'image au format texture
    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer,surface);
    return image;
}


SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    //Charger une image
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    
    // Récupérer la valeur (RGB) du pixel au format donné.
    Uint32 key = SDL_MapRGB(surface->format, r, g, b);
    // Définir la couleur (pixel transparent) dans une surface.
    int reussite = SDL_SetColorKey(surface, SDL_TRUE,key) ;
    
    //Convertir la surface de l'image au format texture
    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer,surface);


    return image;
}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer,
TTF_Font *font, SDL_Color color){
    // Écrire le texte sur une surface SDL
    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    //Convertir la surface de l'image au format texture
    SDL_Texture* image = SDL_CreateTextureFromSurface(renderer,surface);

    return image;
}
