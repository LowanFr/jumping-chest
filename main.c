#include "fonctions_SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * La fonction principale. C'est la première fonction qui est appelée lors de l'exécution du programme.
 * @param argc Le nombre d'arguments passés au programme.
 * @param argv C'est un tableau de chaînes de caractères qui contient les arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {
    SDL_Window* window; // Déclaration de la fenêtre
    SDL_Event events; // Événements liés à la fenêtre
    bool end = false;

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
    SDL_Texture* obj = charger_image_transparente("../assets/obj.bmp", renderer, r, g, b);

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

    // Charger l'image sprites
    r = 0; // Couleur cyan
    SDL_Texture* sprites = charger_image_transparente("../assets/sprites.bmp", renderer, r, g, b);
    int spritesW, spritesH;
    SDL_QueryTexture(sprites, NULL, NULL, &spritesW, &spritesH);

    // Définition du rectangle source pour chaque sprite dans sprites
    SDL_Rect SrcR_sprite[6];
    for(int i=0;i<6;i++){
        SrcR_sprite[i].x = i > 2 ? (spritesW/3)*(i-3): (spritesW/3)*i; 
        //x=0 Pour i=0 et 3/x=spritesW/3 Pour i=1 et 4/x=2*(spriteW/3) Pour i=2 et 5/
        SrcR_sprite[i].y = i > 2 ? spritesH/2 : 0;
        SrcR_sprite[i].w = spritesW/3; // Largeur de l’objet en pixels
        SrcR_sprite[i].h = spritesH/2; // Hauteur de l’objet en pixels
    }

    // Définition du rectangle destination pour chaque sprite dans sprites
    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++) {
        DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
        DestR_sprite[i].y = i > 2 ? 60 : 120;
        DestR_sprite[i].w = spritesW/3; // Largeur du sprite
        DestR_sprite[i].h = spritesH/2; // Hauteur du sprite
    }

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

    // Boucle principale
    while (!end) {
        // Suppression de l'ancien rendu
        SDL_RenderClear(renderer);

        // Mise à jour du rendu
        SDL_RenderCopy(renderer, fond, NULL, NULL);
        SDL_RenderCopy(renderer, obj, &SrcR, &DestR);
        for (int i = 0; i < 6; i++) SDL_RenderCopy(renderer, sprites, &SrcR_sprite[i], &DestR_sprite[i]);
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
                    case SDLK_q:
                        end = true; break;
                }
        }

        // Mise à jour de l'écran avec le rendu
        SDL_RenderPresent(renderer);
    }

    // Quitter SDL_ttf
    TTF_CloseFont(font);
    TTF_Quit();

    // Quitter SDL
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(obj);
    SDL_DestroyTexture(sprites);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}