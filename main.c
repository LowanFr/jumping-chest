
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"

int main(int argc, char* argv[]){
    SDL_Window* fenetre; //Déclaration de la fenêtre
    SDL_Event evenements; //évenements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO)<0){//Initialisation de la SDL 
        printf("Erreur d'initialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    //Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) //En cas d'erreur
    {
        printf("Erreur de la creation d'une fenetre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "../Assets/fond.bmp", ecran );
    
    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* obj_transp = charger_image_transparente("../Assets/obj.bmp", ecran,r,g,b);
    int objetW, objetH;
    SDL_QueryTexture(obj_transp, NULL, NULL, &objetW, &objetH);
    

    SDL_Rect SrcR;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = objetW; // Largeur de l’objet en pixels (à récupérer)
    SrcR.h = objetH; // Hauteur de l’objet en pixels (à récupérer)

    SDL_Rect DestR;
    DestR.x = 350;
    DestR.y = 350;
    DestR.w = objetW/3;
    DestR.h = objetH/3;

    //Création du tableau de sprite
    r=0;//Pour la couleur cyan
    SDL_Texture* obj_sprite = charger_image_transparente("../Assets/sprites.bmp", ecran,r,g,b);
    int tailleW, tailleH;
    SDL_QueryTexture(obj_sprite, NULL, NULL, &tailleW, &tailleH);
    SDL_Rect SrcR_sprite[6];
    for(int i=0;i<6;i++){
        SrcR_sprite[i].x = i > 2 ? (tailleW/3)*(i-3): (tailleW/3)*i;
        SrcR_sprite[i].y = i > 2 ? tailleH/2 : 0;
        SrcR_sprite[i].w = tailleW/3; // Largeur de l’objet en pixels (à récupérer)
        SrcR_sprite[i].h = tailleH/2; // Hauteur de l’objet en pixels (à récupérer)
    }
    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++)
    {
    DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
    DestR_sprite[i].y = i > 2 ? 60 : 120;
    DestR_sprite[i].w = tailleW/3; // Largeur du sprite
    DestR_sprite[i].h = tailleH/2; // Hauteur du sprite
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../Assets/arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char msg[] = "TP sur Makefile et SDL";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    SDL_Rect text_pos; // Position du texte

    int texteW, texteH;
    SDL_QueryTexture(texte, NULL, NULL, &texteW, &texteH);
    printf("w=%d et h=%d", texteW, texteH);
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW; // Largeur du texte en pixels (à récupérer)
    text_pos.h = texteH; // Hauteur du texte en pixels (à récupérer)

    // Boucle principale
    while(!terminer){
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_RenderCopy(ecran, obj_transp, &SrcR, &DestR);
        for(int i=0; i<6; ++i){
            SDL_RenderCopy(ecran, obj_sprite, &SrcR_sprite[i], &DestR_sprite[i]);
        }
        //Appliquer la surface du texte sur l’écran
        SDL_RenderCopy(ecran,texte,NULL,&text_pos);
        
        //SDL_PollEvent ...
        SDL_RenderPresent(ecran);
        
        SDL_PollEvent( &evenements );
        switch(evenements.type)
        {
            case SDL_QUIT:
            terminer = true; break;
            case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                case SDLK_q:
                terminer = true; break;
            }
        }
    }
    // Libérer de la mémoire
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ecran);
    // Fermer la police et quitter SDL_ttf
    TTF_CloseFont( font );
    TTF_Quit();
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}