/**
 * @file graphic.c
 * @brief Exécutable du module de la partie graphique
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "graphic.h"

SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer) {
    // Chargement de l'image à partir du chemin
    SDL_Surface *surface = SDL_LoadBMP(fileName);

    // Conversion de la surface en texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void clean_ressources(ressources_t *ressources) {
    clean_texture(ressources->background);
    clean_texture(ressources->player);
    clean_texture(ressources->blocks);
}

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources) {
    ressources->background = load_image("../assets/classic_bg.bmp", renderer);
    ressources->player = load_image("../assets/player.bmp", renderer);
    ressources->blocks = load_image("../assets/classic.bmp", renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard) {
    // Vide le renderer
    clear_renderer(renderer);

    // Mise à jour des textures
    SDL_RenderCopy(renderer, ressources->background, NULL, NULL);

    // Affiche tous les blocks présent sur la caméra
    for (int i = 0; i < world->map->nb_row; ++i) {
        for (int j = 0; j < world->map->nb_col; ++j) {
            SDL_Rect block = world->map->DestR[i][j];
            bool onCamera = block.y <= world->cam->y + world->cam->h &&
                            block.y + block.h >= world->cam->y &&
                            block.x <= world->cam->x + world->cam->w &&
                            block.x + block.w >= world->cam->x;

            // Affiche le block s'il y a une collision entre celui-ci et la caméra
            if (onCamera) {
                handle_animations(world, i, j);
                block.x -= world->cam->x;
                block.y -= world->cam->y;
                SDL_RenderCopy(renderer, ressources->blocks, &world->blocks[world->map->tab[i][j]].SrcR, &block);
            }
        }
    }

    // Temps entre chaque animation : 0.5 seconde
    if (world->timeAnimation == 30) world->timeAnimation = 0;
    world->timeAnimation++;

    // Affiche le joueur selon la caméra
    SDL_RendererFlip flip = keyboard->lastIsLeft == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_Rect block = world->player->DestR;
    block.x -= world->cam->x;
    block.y -= world->cam->y;
    SDL_RenderCopyEx(renderer, ressources->player, &world->player->SrcR, &block, 0., NULL, flip);

    // Mise à jour de l'écran
    update_screen(renderer);
}

void handle_animations(world_t *world, int i, int j) {
    // Animation des pièces tous les 30 cycles
    if (world->timeAnimation == 30) coin_animations(world->map->tab, i, j);
}

void coin_animations(int **tab, int i, int j) {
    // Itère l'image de la pièce
    if (tab[i][j] >= 6 && tab[i][j] <= 9) {
        tab[i][j]++;
        if (tab[i][j] == 10) tab[i][j] = 6; // Fin du cycle
    }
}
