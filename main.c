#include <stdlib.h>
#include "player.h"
#include "graphic.h"
#include "sdl2-ttf-light.h"

/**
 * @brief Fichier d'exécution du jeu vidéo.
 * @file main.c
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 30 novembre 2022
 */

/**
 * @brief Nombre de FPS dans le jeu.
 */
#define FPS 60



/**
 * @brief Initialisation du jeu.
 * @param window La fenêtre
 * @param renderer Le rendu
 * @param ressources Les ressources
 * @param world Le monde
 * @param keys Les touches du clavier
 * @param camera La caméra
 * @param game La partie
 */
void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world,
          keyboard_status_t *keyboard, mouse_status_t *mouse, cam_t *camera, game_t *game) {
    init_sdl(window, renderer, SCREEN_W, SCREEN_H);
    init_ttf();
    init_game(game);
    init_keyboard(keyboard);
    init_mouse(mouse);
    init_ressources(*renderer, ressources, false);
    world->newLevel = false;
    init_world(game, world, false);
    init_cam(world, camera, SCREEN_W, SCREEN_H);
}

void clean(SDL_Window *window, SDL_Renderer *renderer, ressources_t *ressources, game_t *game, world_t *world) {
    // Libère la mémoire de la partie
    clean_data(world);
    clean_game(game);

    // Libère l'espace des ressources
    clean_ressources(ressources);

    // Quitter SDL
    clean_ttf();
    clean_sdl(renderer, window);
}

/**
 * @brief La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 */
int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    ressources_t ressources;
    world_t world;
    cam_t camera;
    keyboard_status_t keyboard;
    mouse_status_t mouse;
    game_t game;
    int delay = 0;


    // Initialisation du jeu
    init(&window, &renderer, &ressources, &world, &keyboard, &mouse, &camera, &game);

    // Boucle du menu
    while (world.pause || world.menu) {
        // Actualisation du menu
        refresh_menu(&world, renderer, &ressources);
        handle_event(renderer, &ressources, &mouse, &keyboard, &game, &world, &event);

        // Boucle principal
        while (!world.end) {
            // Mise à jour de l'affichage
            refresh_graphics(renderer, &game, &world, &ressources, &keyboard);

            // Mise à jour du niveau si besoin avec les nouvelles textures
            refresh_level(renderer, &game, &ressources, &world);

            // Exécution de tous les événements
            handle_event(renderer, &ressources, &mouse, &keyboard, &game, &world, &event);

            // Déplacement du joueur
            player_movement(&keyboard, world.player);
            repositioning_camera(&world);
            handle_collision(&game, &world, world.player, &keyboard);

            // Ralentissement pour un affichage fluide
            if (SDL_GetTicks() < (delay + 1000 / FPS)) SDL_Delay((delay + 1000 / FPS) - SDL_GetTicks());
            delay = (int) SDL_GetTicks();
        }

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (delay + 1000 / FPS)) SDL_Delay((delay + 1000 / FPS) - SDL_GetTicks());
        delay = (int) SDL_GetTicks();
    }

    // Libère toute la mémoire utilisée pour le monde
    clean(window, renderer, &ressources, &game, &world);

    return EXIT_SUCCESS;
}


