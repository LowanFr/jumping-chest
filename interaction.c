#include "interaction.h"

/**
 * @brief Exécutable des fonctions liées aux interactions
 * @file interaction.c
 * @date 30 Novembre 2022
 * @authors SCHNEIDER Paul, DOUILLET, Esteban
 */

void refresh_keys(world_t *world, keyboard_status_t *keyboard, SDL_Event *event) {
    // Effectue des actions sur le type d'événements
    switch (event->type) {
        case SDL_QUIT: // Fermeture de la fenêtre
            world->end = true;
            break;

        case SDL_KEYDOWN: // Touches appuyées
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    world->end = true;
                    break;
                case SDLK_LEFT:
                    keyboard->lastIsLeft = true;
                    keyboard->left = true;
                    break;
                case SDLK_SPACE:
                    keyboard->space = true;
                    break;
                case SDLK_RIGHT:
                    keyboard->lastIsLeft = false;
                    keyboard->right = true;
                    break;
            }
            break;

        case SDL_KEYUP: // Les touches libérées
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    keyboard->left = false;
                    break;
                case SDLK_SPACE:
                    keyboard->space = false;
                    break;
                case SDLK_RIGHT:
                    keyboard->right = false;
                    break;
            }
            break;
    }
}

void init_keyboard(keyboard_status_t *keyboard) {
    keyboard->right = false;
    keyboard->left = false;
    keyboard->space = false;
    keyboard->lastIsLeft = false;
}

void init_mouse(mouse_status_t *mouse) {
    mouse->right = false;
    mouse->left = false;
    mouse->x = 0;
    mouse->y = 0;
}

void refresh_mouse(mouse_status_t *mouse, SDL_Event *event) {
    // Actualisation des coordonnées de la souris
    SDL_GetGlobalMouseState(&mouse->x, &mouse->y);

    // Effectue des actions sur le type d'événements
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN: // Bouton appuyé
            switch (event->button.button) {
                case SDL_BUTTON_LEFT:
                    mouse->left = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouse->right = true;
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP: // Bouton libéré
            switch (event->button.button) {
                case SDL_BUTTON_LEFT:
                    mouse->left = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    mouse->right = false;
                    break;
            }
            break;
    }
}

void handle_event(mouse_status_t *mouse, keyboard_status_t *keyboard, world_t *world, SDL_Event *event) {
    // Exécute tous les événements en attente à chaque cycle
    while (SDL_PollEvent(event)) {
        refresh_keys(world, keyboard, event);
        refresh_mouse(mouse, event);
    }
}
