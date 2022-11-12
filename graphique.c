/**
 * \file graphic.c
 * \brief Exécutable du module de la partie graphique
 * \author Esteban DOUILLET & SCHNEIDER Paul
 * \version 1.0
 * \date 9 Novembre 2022
 */
#include "graphique.h"

void clean_ressources(ressources_t *ressources) {
    clean_texture(ressources->background);
    clean_texture(ressources->player);
    clean_texture(ressources->blocks);
}

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources) {
    ressources->background = charger_image("../assets/background.bmp", renderer);
    ressources->player = charger_image("../assets/player.bmp", renderer);
    ressources->blocks = charger_image("../assets/classic.bmp", renderer);
}

void apply_background(SDL_Renderer *renderer, ressources_t *ressources) {
    if (ressources->background != NULL) {
        SDL_RenderCopy(renderer, ressources->background, 0,0);
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (sprite->is_deleted) { // une sprite supprimée doit être invisible
        set_invisible(sprite);
    }

    if (sprite->is_visible) { // toutes les images visibles doivent être appliquées sur le renderer
        SDL_RenderCopy(renderer, texture, &sprite->SrcR, &sprite->DestR);
    }
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources) {
    // on vide le renderer
    clear_renderer(renderer);

    // application des ressources dans le renderer
    apply_background(renderer, ressources);
    apply_sprite(renderer, ressources->player, world->joueur);

    // on met à jour l'écran
    if (!world->end) {
        update_screen(renderer);
    }
}