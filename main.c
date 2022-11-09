#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "world.h"
#include "joueur.h"
#include "constante.h"
#include "graphique.h"
#include "clavier.h"

//Couleur bleu texture rgb(55,78,211)

#define SCREEN_H 720
#define SCREEN_W 1280

void init(SDL_Window **window, SDL_Renderer **renderer, ressources_t *ressources, world_t *world, etat_clavier_t *touches, joueur_t *joueur){
    init_sdl(window,renderer,SCREEN_W, SCREEN_H);
    init_world(world);
    init_touches(touches);
    init_ressources(*renderer, ressources);
    init_joueur(joueur);
}

/**
 * La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv C'est un tableau de chaînes de caractères qui contient les arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Renderer* renderer;
    ressources_t ressources;
    world_t world;
    etat_clavier_t touches;
    joueur_t joueur;

    init(&window, &renderer, &ressources, &world, &touches, &joueur);

    //Changement de la couleur de fond
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Chargement de la map
    int temps_fin = 0;

    // Boucle principale
    while (!world.end) {
        // Suppression de l'ancien rendu
        clear_renderer(renderer);

        // Mise à jour du rendu
        
        SDL_RenderCopy(renderer, ressources.background, NULL, NULL);
        SDL_RenderCopy(renderer, ressources.player, &world.joueur->SrcR, &world.joueur->DestR);

        SDL_RenderCopy(renderer, ressources.blocks, &world.blocks[1].SrcR, &world.blocks[0].DestR);
        
        

        // Récupération des événements
        SDL_PollEvent(&touches.events);

        refresh_keys(&world, &touches);

        

        // Déplacement du joueur
        deplacement_joueur(&touches, &joueur, world.joueur);

        
        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);
        

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (temps_fin + 1000 / FPS)){
            SDL_Delay((temps_fin + 1000 / FPS) - SDL_GetTicks());
        }
        temps_fin = SDL_GetTicks();
    }

    // Quitter SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(world.blocks);

    return EXIT_SUCCESS;
}


