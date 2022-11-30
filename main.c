#include <stdlib.h>
#include "player.h"
#include "graphic.h"

/**
 * @brief Fichier d'exécution du jeu vidéo
 * @file main.c
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 30 novembre 2022
 */

/**
 * @brief Nombre de FPS dans le jeu
 */
#define FPS 60

/**
 * @brief La hauteur de l'écran
 */
#define SCREEN_H 720

/**
 * @brief La largeur de l'écran
 */
#define SCREEN_W 1280

/**
 * @brief Initialisation du jeu
 * @param window La fenêtre
 * @param renderer Le rendu
 * @param ressources Les ressources
 * @param world Le monde
 * @param keys Les touches du clavier
 * @param player Le joueur
 * @param camera La caméra
 */
void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, keyboard_status_t *keyboard,
     mouse_status_t *mouse, player_t *player, cam_t *camera) {
    init_sdl(window, renderer, SCREEN_W, SCREEN_H);
    init_world(world);
    init_keyboard(keyboard);
    init_mouse(mouse);
    init_ressources(*renderer, ressources);
    init_player(player, world);
    init_cam(world, camera, SCREEN_W, SCREEN_H);
}

void clean(SDL_Window *window, SDL_Renderer *renderer, ressources_t *ressources, world_t *world) {
    // Libère toute la mémoire utilisée pour le monde
    desallouer_tab_2D(world->map->tab, world->map->nb_row);
    for (int i = 0; i < world->map->nb_row; i++) free(world->map->DestR[i]); // Libère toutes les lignes
    free(world->map->DestR);
    free(world->map);
    free(world->blocks);
    free(world->player);

    // Libère l'espace des ressources
    clean_ressources(ressources);

    // Quitter SDL
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
    player_t player;
    int tempsFin = 0;

    // Initialisation du jeu
    init(&window, &renderer, &ressources, &world, &keyboard, &mouse, &player, &camera);

    // Boucle principale
    while (!world.end) {
        refresh_graphics(renderer, &world, &ressources, &keyboard); //

        // Exécution de tous les événements
        handle_event(&mouse, &keyboard, &world, &event);

        // Déplacement du joueur
        player_movement(&keyboard, &player);
        repositioning_camera(&camera, &player.prec);
        handle_collision(&world, &player);

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (tempsFin + 1000 / FPS)) SDL_Delay((tempsFin + 1000 / FPS) - SDL_GetTicks());
        tempsFin = (int) SDL_GetTicks();
    }

    // Libère toute la mémoire utilisée pour le monde
    clean(window, renderer, &ressources, &world);

    return EXIT_SUCCESS;
}


