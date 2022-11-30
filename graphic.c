/**
 * @file graphic.c
 * @brief Exécutable du module de la partie graphique
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 28 Novembre 2022
 */
#include "graphic.h"

SDL_Texture* charger_image(const char* nomFichier, SDL_Renderer* renderer) {
    // Chargement de l'image à partir du chemin
    SDL_Surface* surface = SDL_LoadBMP(nomFichier);

    // Conversion de la surface en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void clean_ressources(ressources_t *ressources) {
    clean_texture(ressources->background);
    clean_texture(ressources->player);
    clean_texture(ressources->blocks);
}

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources) {
    ressources->background = charger_image("../assets/classic_bg.bmp", renderer);
    ressources->player = charger_image("../assets/player.bmp", renderer);
    ressources->blocks = charger_image("../assets/classic.bmp", renderer);
}

void apply_background(SDL_Renderer *renderer, ressources_t *ressources) {
    if (ressources->background != NULL) SDL_RenderCopy(renderer, ressources->background, 0,0);
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    SDL_RenderCopy(renderer, texture, &sprite->SrcR, &sprite->DestR);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources) {
    // Vide le renderer
    clear_renderer(renderer);

    // Applique les ressources dans le renderer
    apply_background(renderer, ressources);
    apply_sprite(renderer, ressources->player, world->player);

    // Mise à jour de l'écran
    if (!world->end) update_screen(renderer);
}
void handle_animation(world_t *world, int i, int j){
    
    if(world->timeAnimation == 30){
        pieces_animations(world->map->tab,i,j);
    }
}

void pieces_animations(int **tab, int i, int j){

    if(tab[i][j] >= 6 && tab[i][j] <= 9){
        tab[i][j]++;
        
        if(tab[i][j] == 10){
            tab[i][j] = 6;
        }
    }
}