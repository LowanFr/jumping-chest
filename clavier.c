#include "clavier.h"

void refresh_keys(world_t *world ,etat_clavier_t *touches){
    // Effectue des actions sur le type d'événements
        switch (touches->events.type) {
            case SDL_QUIT:
                world->end = true; break;

            case SDL_KEYDOWN:
                switch(touches->events.key.keysym.sym){
                    case SDLK_ESCAPE:
                        world->end = true; break;
                    case SDLK_LEFT:
                        touches->left = true; break;
                    case SDLK_SPACE:
                        touches->space = true; break;
                    case SDLK_RIGHT:
                        touches->right = true; break;

                }break;

            case SDL_KEYUP:
                switch(touches->events.key.keysym.sym){
                    case SDLK_LEFT:
                        touches->left = false; break;
                    case SDLK_SPACE:
                        touches->space = false; break;
                    case SDLK_RIGHT:
                        touches->right = false; break;

                }break;
        }
}

void init_touches(etat_clavier_t *touches){
    touches->right = false;
    touches->left = false;
    touches->space = false;
}