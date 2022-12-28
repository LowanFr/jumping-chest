#include "interaction.h"

/**
 * @brief Exécutable des fonctions liées aux interactions.
 * @file interaction.c
 * @date 30 Novembre 2022
 * @authors SCHNEIDER Paul, DOUILLET, Esteban
 */

void refresh_keys(game_t *game, world_t *world, keyboard_status_t *keyboard, SDL_Event *event) {
    SDL_Keycode key;

    // Effectue des actions sur le type d'événements
    switch (event->type) {
        case SDL_QUIT: // Fermeture de la fenêtre
            world->end = true;
            world->pause = false;
            world->menu = false;
            world->waitingMenu = false;
            game->enteringPseudo = false;
            break;

        case SDL_KEYDOWN: // Touches appuyées
            key = event->key.keysym.sym;
            write_pseudo(game, key);

            switch (key) {
                case SDLK_ESCAPE:
                    if (!world->waitingMenu) {
                        world->end = true;
                        if (world->menu) world->menu = false;
                        else if (world->pause) {
                            world->pause = false;
                            world->menu = true;
                        } else {
                            world->pause = true;
                            world->cyclesPause = 0;
                        }
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
                default:
                    keyboard->e = true;
                    break;
            }
            break;

        case SDL_KEYUP: // Les touches libérées
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:
                    if (keyboard->right) keyboard->lastIsLeft = false;
                    keyboard->left = false;
                    break;
                case SDLK_SPACE:
                    keyboard->space = false;
                    break;
                case SDLK_RIGHT:
                    if (keyboard->left) keyboard->lastIsLeft = true;
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
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) mouse->left = true;
    else if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT) mouse->left = false;
}

void handle_event(SDL_Renderer *renderer, ressources_t *ressources,
                  mouse_status_t *mouse, keyboard_status_t *keyboard, game_t *game, world_t *world, SDL_Event *event) {
    // Exécute tous les événements en attente à chaque cycle
    while (SDL_PollEvent(event)) {
        refresh_keys(game, world, keyboard, event);
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

        // Affiche le bouton correspondant
        if (button.type == 0) resume_button(renderer, game, world, ressources);
        if (button.type == 1) new_game_button(renderer, game, world, ressources);
        if (button.type == 2) exit_button(world);
        if (button.type == 3) save_button(game, world);
    }
}

void resume_button(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources) {
    if (world->pause == true) { // Reprend la partie en cours
        world->pause = false;
        world->end = false;
    } else { // Charge la sauvegarde
        world->menu = false;
        load_game(game);
        load_world(world);
        init_ressources(renderer, ressources, game);
        world->end = false;
    }
}

void save_button(game_t *game, world_t *world) {
    // Défini le chemin vers le dossier
    char folder[100] = "../backups";

    // Sauvegarde toutes les structures de données
    save_game(game, folder);
    save_world(world, folder);

    // Redirige sur le menu principal
    world->menu = true;
    world->pause = false;
}

void new_game_button(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources) {
    world->menu = false;
    world->end = false;
    init_game(game);
    init_world(game, world, true);
    init_ressources(renderer, ressources, game);
}

void exit_button(world_t *world) {
    if (world->menu) { // Ferme le jeu
        world->menu = false;
    } else { // Redirige vers le menu principal
        world->menu = true;
        world->pause = false;
    }
}

void write_pseudo(game_t *game, SDL_Keycode key) {
    if (!game->enteringPseudo) return;

    // Supprime le dernier caractère
    if (key == SDLK_BACKSPACE || key == SDLK_RETURN || key == SDLK_ESCAPE) {
        if (key == SDLK_RETURN || key == SDLK_ESCAPE) game->enteringPseudo = false;
        else game->pseudo[strlen(game->pseudo) - 1] = 0;
        return;
    }

    // Récupère le nom de la clef
    char keyName[50];
    sprintf(keyName, "%s", SDL_GetKeyName(key));

    // Vérifie la taille du pseudonyme et de la clef
    if (strlen(game->pseudo) >= 20 || strlen(keyName) > 1) return;
    strcat(game->pseudo, keyName);
}
