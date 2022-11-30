#include <stdlib.h>
#include "player.h"
#include "graphic.h"

/**
 * @brief Fichier d'exécution du jeu vidéo
 * @file main.c
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 novembre 2022
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
void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, keyboard_status_t *keys, player_t *player, cam_t *camera) {
    init_sdl(window,renderer, SCREEN_W, SCREEN_H);
    init_world(world);
    init_touches(keys);
    init_ressources(*renderer, ressources);
    init_player(player, world);
    init_cam(world, camera, SCREEN_W, SCREEN_H);
}

/**
 * @brief La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 */
int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    ressources_t ressources;
    world_t world;
    cam_t camera;
    keyboard_status_t keys;
    player_t player;

    // Initialisation du jeu
    init(&window, &renderer, &ressources, &world, &keys, &player, &camera);

    // Changement de la couleur de fond
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Chargement de la map
    int tempsFin = 0;

    // Boucle principale
    while (!world.end) {
        // Suppression de l'ancien rendu
        clear_renderer(renderer);

        // Mise à jour des textures
        SDL_RenderCopy(renderer, ressources.background, NULL, NULL);

        // Affiche tous les blocks présent sur la caméra

        for(int i = 0; i<world.map->nb_row; ++i){
            for(int j = 0; j<world.map->nb_col; ++j){
                SDL_Rect block = world.map->DestR[i][j];
                bool onCamera = block.y <= camera.y + camera.h  &&
                        block.y + block.h >= camera.y &&
                        block.x <= camera.x + camera.w &&
                        block.x + block.w >= camera.x;
                

                // Affiche le block s'il y a une collision entre celui-ci et la caméra
                if (onCamera) {
                    handle_animation(&world, i ,j); //Toutes les animations à l'ecran

                    block.x -= camera.x;
                    block.y -= camera.y;
                    SDL_RenderCopy(renderer, ressources.blocks, &world.blocks[world.map->tab[i][j]].SrcR, &block);
                }
            }
        }
        //Temps entre chaque animations : 0.5 seconde
        if(world.timeAnimation == 30)  world.timeAnimation = 0; 
        world.timeAnimation++;
    
        // Affiche le joueur selon la caméra
        SDL_RendererFlip flip = keys.lastIsLeft == 1? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE;
        SDL_Rect block = world.player->DestR;
        block.x -= camera.x;
        block.y -= camera.y;
        SDL_RenderCopyEx(renderer, ressources.player, &world.player->SrcR, &block, 0., NULL, flip);
        

        // Récupération des événements
        SDL_PollEvent(&keys.events);
        refresh_keys(&world, &keys);

        // Déplacement du player
        player_movement(&keys, &player);
        repositioning_camera(&camera, &player.prec);
        handle_collision(&world, &player);
        

        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (tempsFin + 1000 / FPS)) SDL_Delay((tempsFin + 1000 / FPS) - SDL_GetTicks());
        tempsFin = (int) SDL_GetTicks();
    }

    // Libère toute la mémoire utilisée pour le monde
    desallouer_tab_2D(world.map->tab, world.map->nb_row);
    for (int i = 0; i < world.map->nb_row; i++) free(world.map->DestR[i]); // Libère toutes les lignes
    free(world.map->DestR);
    free(world.map);
    free(world.blocks);
    free(world.player);

    // Libère l'espace des ressources
    SDL_DestroyTexture(ressources.background);
    SDL_DestroyTexture(ressources.player);
    SDL_DestroyTexture(ressources.blocks);

    // Quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}


