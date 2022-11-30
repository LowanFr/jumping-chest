/**
 * @file sdl2-light.c
 * @brief sur-couche de SDL2 pour simplifier son utilisation pour le projet.
 * @author DOUILLET Esteban & SCHNEIDER Paul
 * @date 30 Novembre 2022
*/

#include "sdl2-light.h"
#include <stdio.h>

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer)) {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void clean_texture(SDL_Texture *texture) {
    if (NULL != texture) SDL_DestroyTexture(texture);
}

void clear_renderer(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
}

void update_screen(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}

void clean_sdl(SDL_Renderer *renderer, SDL_Window *window) {
    if (NULL != renderer) SDL_DestroyRenderer(renderer);
    if (NULL != window) SDL_DestroyWindow(window);
    SDL_Quit();
}
