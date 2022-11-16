#include <stdlib.h>
#include "player.h"
#include "graphic.h"

/**
 * \brief Nombre de FPS dans le jeu
 */
#define FPS 60

// La taille de l'écran
#define SCREEN_H 720
#define SCREEN_W 1280

/**
 * @brief Initialisation du jeu
 * @param window La fenêtre
 * @param renderer Le rendu
 * @param ressources Les ressources
 * @param world Le monde
 * @param keys Les touches du clavier
 * @param player Le joueur
 */
void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, keyboard_status_t *keys, player_t *player) {
    init_sdl(window,renderer, SCREEN_W, SCREEN_H);
    init_world(world);
    init_touches(keys);
    init_ressources(*renderer, ressources);
    init_player(player, world);
}

/**
 * @brief La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 */
int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    ressources_t ressources;
    world_t world;
    keyboard_status_t keys;
    player_t player;

    // Initialisation du jeu
    init(&window, &renderer, &ressources, &world, &keys, &player);

    //Changement de la couleur de fond
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Chargement de la map
    int tempsFin = 0;

    // Boucle principale
    while (!world.end) {
        // Suppression de l'ancien rendu
        clear_renderer(renderer);

        // Mise à jour des textures
        SDL_RenderCopy(renderer, ressources.background, NULL, NULL);
        

        for(int i = 0; i<world.map->nb_row; ++i){
            for(int j = 0; j<world.map->nb_col; ++j){
                SDL_RenderCopy(renderer, ressources.blocks, &world.blocks[world.map->tab[i][j]].SrcR, &world.map->DestR[i][j]);
            }
        }
        SDL_RenderCopy(renderer, ressources.player, &world.player->SrcR, &world.player->DestR);
        handle_collision(&world, &player);

        // Récupération des événements
        SDL_PollEvent(&keys.events);
        refresh_keys(&world, &keys);

        // Déplacement du player
        player_movement(&keys, &player);

        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (tempsFin + 1000 / FPS)){
            SDL_Delay((tempsFin + 1000 / FPS) - SDL_GetTicks());
        }
        tempsFin = (int) SDL_GetTicks();
    }
    
    // Quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(ressources.background);
    SDL_DestroyTexture(ressources.player);
    SDL_DestroyTexture(ressources.blocks);
    SDL_Quit();
    
    desallouer_tab_2D(world.map->tab, world.map->nb_row);
    
    for (int i = 0; i < world.map->nb_row; i++) { // Libère toutes les lignes
        free(world.map->DestR[i]);
    }
    free(world.map->DestR);
    
    free(world.map);
    free(world.blocks);
    free(world.player);

    return EXIT_SUCCESS;
}


