#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "fonctions_SDL.h"
#include "constante.h"

void deplacement_joueur(etat_clavier_t *touches, SDL_Rect *DestR,joueur_t *joueur);

/**
 * La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv C'est un tableau de chaînes de caractères qui contient les arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Event events; // Événements liés à la fenêtre
    const int FPS = 60;

    bool end = false;
    etat_clavier_t touches;

    joueur_t joueur;
    joueur.saut = false;
    joueur.tempsDepuisLeDebutDuSaut = 0;
    joueur.y0;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d’initialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Créer la fenêtre
    window = SDL_CreateWindow("Fenêtre SDL", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);

    // En cas d’erreur
    if (window == NULL){
        printf("Erreur de la creation d’une fenêtre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création du contexte de rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Charger le fond / background
    SDL_Texture* fond = charger_image("../assets/fond.bmp", renderer);

    // Charger l'image obj
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* obj = charger_image_transparente("../assets/25aa.bmp", renderer, r, g, b);

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
    DestR.y = 350;
    DestR.w = objetW/3;
    DestR.h = objetH/3;

    // Initialisation de TTF
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../assets/arial.ttf", 28);
    SDL_Color color = {0, 0, 0, 0}; // RGBA : alpha = transparence
    char msg[] = "TP sur Makefile et SDL"; // Message à afficher

    // Chargement du texte puis initialisation de sa position
    SDL_Texture* texte = charger_texte(msg, renderer, font, color);
    SDL_Rect text_pos;

    // Définition de la position du texte
    int texteW, texteH;
    SDL_QueryTexture(texte, NULL, NULL, &texteW, &texteH);
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW; // Largeur du texte en pixels
    text_pos.h = texteH; // Hauteur du texte en pixels

    int temps_debut;
    int temps_fin=0;
    bool right = false;

    // Boucle principale
    while (!end) {
        // Suppression de l'ancien rendu
        SDL_RenderClear(renderer);

        // Mise à jour du rendu
        SDL_RenderCopy(renderer, fond, NULL, NULL);
        SDL_RenderCopy(renderer, obj, &SrcR, &DestR);
        SDL_RenderCopy(renderer, texte, NULL, &text_pos);

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
                        touches.left=true; break;
                    case SDLK_RIGHT:
                        touches.right=true; break;
                    case SDLK_UP:
                        touches.up=true;break;
                }break;

            case SDL_KEYUP:
                switch(events.key.keysym.sym){
                    case SDLK_LEFT:
                        touches.left=false; break;
                    case SDLK_RIGHT:
                        touches.right=false; break;
                    case SDLK_UP:
                        touches.up=false;break;

                }
        }
        deplacement_joueur(&touches,&DestR,&joueur);

        
        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);
        
        
        if (SDL_GetTicks() < (temps_fin + 1000 / FPS)){
            SDL_Delay((temps_fin + 1000 / FPS) - SDL_GetTicks());
        }
        temps_fin = SDL_GetTicks();
        
        
        
    }
    
    
    
 
    // Où y0 est l'ordonnée de départ (au moment où ou saute)


    
    // Quitter SDL_ttf
    TTF_CloseFont(font);
    TTF_Quit();

    // Quitter SDL
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(obj);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void deplacement_joueur(etat_clavier_t *touches, SDL_Rect *DestR,joueur_t *joueur){
    
    
    if(touches->left){
        DestR->x=DestR->x-VITESSE_X_MARCHE;
    }
    if(touches->right){
        DestR->x=DestR->x+VITESSE_X_MARCHE;
    }
    if(touches->up){
        if(joueur->saut==false){
            joueur->y0 = DestR->y;
            joueur->tempsDepuisLeDebutDuSaut = 0;
            joueur->saut = true;
        }
    }
    if(joueur->saut==true){
        DestR->y = joueur->y0 - VITESSE_Y_SAUT * joueur->tempsDepuisLeDebutDuSaut + 0.5 * GRAVITE * joueur->tempsDepuisLeDebutDuSaut * joueur->tempsDepuisLeDebutDuSaut;
        joueur->tempsDepuisLeDebutDuSaut++;
        if(DestR->y-1 >= joueur->y0){
            DestR->y=joueur->y0;
            joueur->saut=false;
        }
    }

}
