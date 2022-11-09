#include "world.h"

void init_world(world_t *world){

    world->end = 0;
    world->blocks = calloc(NBR_DE_TEXTURES, sizeof(sprite_t));
    for(int i = 0; i<NBR_DE_TEXTURES; ++i){
        init_sprite(&world->blocks[i],X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i%11), Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i/11),TAILLE_TEXTURES,TAILLE_TEXTURES,0,0,TAILLE_TEXTURES,TAILLE_TEXTURES);
    }
    world->joueur = calloc(1, sizeof(sprite_t));
    init_sprite(world->joueur, 0,0,LARGEUR_PLAYER,HAUTEUR_PLAYER,350,720-3*HAUTEUR_PLAYER,LARGEUR_PLAYER,HAUTEUR_PLAYER);

    
}

void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
    sprite->SrcR.x = x1;
    sprite->SrcR.y = y1;
    sprite->SrcR.w = w1;
    sprite->SrcR.h = h1;

    sprite->DestR.x = x2;
    sprite->DestR.y = y2;
    sprite->DestR.w = w2;
    sprite->DestR.h = h2;
    sprite->v = VITESSE_X_MARCHE;
    sprite->is_visible = 1;
    sprite->is_deleted = 0;
}

void set_invisible(sprite_t *sprite){

}
void init_textures(world_t *world){

}

