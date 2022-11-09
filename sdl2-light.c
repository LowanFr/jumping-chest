/**
 * \file sdl2-light.c
 * \brief sur-couche de SDL2 pour simplifier son utilisation pour le projet
 * \author DOUILLET Esteban & SCHNEIDER Paul
 * \version 1.0
 * \date 9 Novembre 2022
*/

#include "sdl2-light.h"
#include <stdio.h>

int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
    if(0 != SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)) {
        fprintf(stderr, "Erreur initialisation de la SDL : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer)) {
        fprintf(stderr, "Erreur lors de la creation de l'image et du renderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer) {
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp) {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture) {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

void apply_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    SDL_Rect dst = {0, 0, 0, 0};
    
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    dst.x = x; dst.y=y;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void clean_texture(SDL_Texture *texture) {
    if (NULL != texture) {
        SDL_DestroyTexture(texture);
    }
}

void clear_renderer(SDL_Renderer *renderer){
    SDL_RenderClear(renderer);
}

void update_screen(SDL_Renderer *renderer){
    SDL_RenderPresent(renderer);
}

void pause(int time){
    SDL_Delay(time);
}

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window) {
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();    
}
