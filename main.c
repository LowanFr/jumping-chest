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
 * @param game La partie
 */
void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world,
          keyboard_status_t *keyboard, mouse_status_t *mouse, game_t *game) {
    init_sdl(window, renderer, SCREEN_W, SCREEN_H);
    init_ttf();
    init_game(game);
    init_keyboard(keyboard);
    init_mouse(mouse);
    init_ressources(*renderer, ressources, game);
    world->newLevel = false;
    world->hearts = 3;
    world->reinstall = false;
    init_world(game, world, false);
}

/**
 * Libère la mémoire de tout le programme.
 * @param window La fenêtre
 * @param renderer Le moteur de rendu
 * @param ressources Les ressources
 * @param game Le jeu
 * @param world Le monde
 */
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
 * Applique des pauses pour être à 60 FPS
 */
void sleep() {
    // Ralentissement pour un affichage fluide
    SDL_Delay(1000 / FPS);
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
    keyboard_status_t keyboard;
    mouse_status_t mouse;
    game_t game;
    world.reinstall = true;

    while (world.reinstall) {
        // Initialisation du jeu
        init(&window, &renderer, &ressources, &world, &keyboard, &mouse, &game);

        // Boucle du menu
        while (world.pause || world.menu || world.waitingMenu) {
            // Actualisation du menu
            refresh_menu(&game, &world, renderer, &ressources);
            handle_event(renderer, &ressources, &mouse, &keyboard, &game, &world, &event);

            // Boucle principal
            while (!world.end) {
                // Mise à jour de l'affichage
                refresh_graphics(renderer, &game, &world, &ressources, &keyboard);

                // Mise à jour du niveau si besoin avec les nouvelles textures
                refresh_level(renderer, &game, &ressources, &world);

                // Exécution de tous les événements
                handle_event(renderer, &ressources, &mouse, &keyboard, &game, &world, &event);
                update_hearts(&game, &world);

                // Déplacement du joueur
                player_movement(&keyboard, world.player);
                repositioning_camera(&world);
                handle_collision(&game, &world, world.player, &keyboard);

                // Incrémente le nombre de cycles
                if (world.cycles == 180) world.cycles = 0;
                else world.cycles++;

                sleep();
            }
            sleep();
        }

        // Libère toute la mémoire utilisée pour le monde
        clean(window, renderer, &ressources, &game, &world);

    }
    return EXIT_SUCCESS;
}


