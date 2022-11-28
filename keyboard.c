#include "keyboard.h"

/**
 * @brief Exécutable des fonctions liées au clavier
 * @file keyboard.c
 * @date 28 Novembre 2022
 * @authors SCHNEIDER Paul, DOUILLET, Esteban
 */

void refresh_keys(world_t *world, keyboard_status_t *keys) {
    // Effectue des actions sur le type d'événements
    switch (keys->events.type) {
        case SDL_QUIT: // Echap
            world->end = true;break;

        case SDL_KEYDOWN: // Touches appuyées
            switch(keys->events.key.keysym.sym) {
                case SDLK_ESCAPE:
                    world->end = true; break;
                case SDLK_LEFT:
                    keys->lastIsLeft = true;
                    keys->left = true; break;
                case SDLK_SPACE:
                    keys->space = true; break;
                case SDLK_RIGHT:
                    keys->lastIsLeft = false;
                    keys->right = true; break;
            }break;

        case SDL_KEYUP: // Les touches libérées
            switch(keys->events.key.keysym.sym) {
                case SDLK_LEFT:
                    keys->left = false; break;
                case SDLK_SPACE:
                    keys->space = false; break;
                case SDLK_RIGHT:
                    keys->right = false; break;
            }break;
    }
}

void init_touches(keyboard_status_t *touches) {
    touches->right = false;
    touches->left = false;
    touches->space = false;
    touches->lastIsLeft = false;
}