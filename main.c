#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "world.h"
#include "joueur.h"
#include "constante.h"

//Couleur bleu texture rgb(55,78,211)

#define FPS 60

/**
 * La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv C'est un tableau de chaînes de caractères qui contient les arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Event events; // Événements liés à la fenêtre
    world_t world;
    

    bool end = false;
    etat_clavier_t touches;

    joueur_t joueur;
    joueur.saut = false;
    joueur.tempsDepuisLeDebutDuSaut = 0;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d’initialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Créer la fenêtre
    window = SDL_CreateWindow("Fenêtre SDL", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);

    // En cas d’erreur
    if (window == NULL){
        printf("Erreur de la creation d’une fenêtre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création du contexte de rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Changement de la couleur de fond
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Chargement fond
    SDL_Texture* fond = charger_image("../assets/background.bmp", renderer);

    // Charger l'image obj
    Uint8 r = 55, g = 78, b = 211;
    SDL_Texture* obj = charger_image_transparente("../assets/gugus.bmp", renderer, r, g, b);

    //Charger textures
    SDL_Texture* textures = charger_image_transparente("../assets/classic.bmp", renderer, r, g, b);
    
    init_textures(&world);

    // Définition de la hauteur / largeur d'obj
    int objetW, objetH;
    SDL_QueryTexture(obj, NULL, NULL, &objetW, &objetH);

    // Définition du rectangle source pour obj
    SDL_Rect SrcR, DestR;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = objetW; // Largeur de l’objet en pixels
    SrcR.h = objetH; // Hauteur de l’objet en pixels

    // Définition du rectangle destination pour obj
    DestR.x = 350;
    DestR.y = 721 - objetH - 63*3;
    DestR.w = objetW;
    DestR.h = objetH;

    //Chargement de la map
    int temps_fin = 0;

    // Boucle principale
    while (!end) {
        // Suppression de l'ancien rendu
        clear_renderer(renderer);

        // Mise à jour du rendu
        apply_texture()
        SDL_RenderCopy(renderer, fond, NULL, NULL);
        SDL_RenderCopy(renderer, obj, &SrcR, &DestR);

        SDL_RenderCopy(renderer, textures, &world.textures[1].SrcR, &world.textures[0].DestR);
        
        

        // Récupération des événements
        SDL_PollEvent(&events);

        // Effectue des actions sur le type d'événements
        switch (events.type) {
            case SDL_QUIT:
                end = true; break;

            case SDL_KEYDOWN:
                switch(events.key.keysym.sym){
                    case SDLK_ESCAPE:
                        end = true; break;
                    case SDLK_LEFT:
                        touches.left = true; break;
                    case SDLK_SPACE:
                        touches.space = true; break;
                    case SDLK_RIGHT:
                        touches.right = true; break;

                }break;

            case SDL_KEYUP:
                switch(events.key.keysym.sym){
                    case SDLK_LEFT:
                        touches.left = false; break;
                    case SDLK_SPACE:
                        touches.space = false; break;
                    case SDLK_RIGHT:
                        touches.right = false; break;

                }break;
        }

        // Déplacement du joueur
        deplacement_joueur(&touches, &joueur);

        
        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);
        

        // Ralentissement pour un affichage fluide
        if (SDL_GetTicks() < (temps_fin + 1000 / FPS)){
            SDL_Delay((temps_fin + 1000 / FPS) - SDL_GetTicks());
        }
        temps_fin = SDL_GetTicks();
    }

    // Quitter SDL
    SDL_DestroyTexture(obj);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(world.textures);

    return EXIT_SUCCESS;
}


