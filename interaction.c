#include "interaction.h"

/**
 * @brief Exécutable des fonctions liées aux interactions.
 * @file interaction.c
 * @date 30 Novembre 2022
 * @authors SCHNEIDER Paul, DOUILLET, Esteban
 */

void refresh_keys(world_t *world, keyboard_status_t *keyboard, SDL_Event *event) {
    // Effectue des actions sur le type d'événements
    switch (event->type) {
        case SDL_QUIT: // Fermeture de la fenêtre
            world->end = true;
            world->pause = false;
            world->menu = false;
            break;

        case SDL_KEYDOWN: // Touches appuyées
            switch (event->key.keysym.sym) {
                case SDLK_ESCAPE:
                    world->end = true;
                    if (world->menu) {
                        world->menu = false;
                    } else if (world->pause) {
                        world->pause = false;
                        world->menu = true;
                    } else if (!world->pause) {
                        world->pause = true;
                        world->cycles_pause = 0;
                    }
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
                case SDLK_e:
                    keyboard->e = true;
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
                case SDLK_e:
                    keyboard->e = false;
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
    keyboard->e = false;
}

void init_mouse(mouse_status_t *mouse) {
    mouse->left = false;
    mouse->x = 0;
    mouse->y = 0;
}

void refresh_mouse(mouse_status_t *mouse, SDL_Event *event) {
    // Actualisation des coordonnées de la souris
    SDL_GetMouseState(&mouse->x, &mouse->y);

    // Effectue des actions sur le type d'événements
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN: // Bouton appuyé
            switch (event->button.button) {
                case SDL_BUTTON_LEFT:
                    mouse->left = true;
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP: // Bouton libéré
            switch (event->button.button) {
                case SDL_BUTTON_LEFT:
                    mouse->left = false;
                    break;
            }
    }
}

void handle_event(SDL_Renderer *renderer, ressources_t *ressources,
                  mouse_status_t *mouse, keyboard_status_t *keyboard, game_t *game, world_t *world, SDL_Event *event) {
    // Exécute tous les événements en attente à chaque cycle
    while (SDL_PollEvent(event)) {
        refresh_keys(world, keyboard, event);
        refresh_mouse(mouse, event);
        handle_button(renderer, ressources, game, world, mouse);
    }

}

void handle_button(SDL_Renderer *renderer, ressources_t *ressources, game_t *game, world_t *world,
                   mouse_status_t *mouseStatus) {

    // Vérifie qu'il y a un clic gauche
    if (!mouseStatus->left) return;

    // Parcours tous les boutons
    for (int i = 0; i < 4; i++) {
        // Vérifie que le bouton est activé
        button_t button = world->buttons[i];
        if (!button.enable) continue;

        // Vérifie une collision entre le bouton et la souris
        bool cond1 = mouseStatus->x <= button.DestR.x + button.DestR.w && mouseStatus->x >= button.DestR.x;
        bool cond2 = mouseStatus->y <= button.DestR.y + button.DestR.h && mouseStatus->y >= button.DestR.y;
        if (!cond1 || !cond2) continue;

        // Bouton reprendre une partie
        if (button.type == 0) {
            if (world->pause == true) {
                world->pause = false;
                world->end = false;
            }
        }

        // Bouton pour sauvegarder
        if (button.type == 3) {
            // Récupération de la date actuelle
            time_t date = time(NULL);
            struct tm tm = *localtime(&date);

            // Défini le chemin vers le dossier
            char folder[100];
            sprintf(folder, "../backups/%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1,
                    tm.tm_mday,
                    tm.tm_hour, tm.tm_min, tm.tm_sec);

            // Vérifie que le dossier n'existe pas puis le crée
            struct stat st = {0};
            if (stat(folder, &st) != -1) return;
            mkdir(folder, 0700);

            // Sauvegarde toutes les structures de données
            save_game(game, folder);
            save_world(world, folder);

            world->menu = true;
            world->pause = false;
        }

        // Bouton de nouvelle partie
        if (button.type == 1 && world->menu == true && world->end == true) {
            world->menu = false;
            world->end = false;
            init_world(game, world, true);
            init_ressources(renderer, ressources, game);
        }

        // Bouton pour quitter
        if (button.type == 2 && world->menu) world->menu = false;
        if (button.type == 2 && world->pause) {
            world->menu = true;
            world->pause = false;
        }
    }
}
