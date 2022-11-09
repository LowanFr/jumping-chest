#include "world.h"

void init_data(world_t *world){
    world->blocks = calloc(NBR_DE_TEXTURES, sizeof(sprite_t));
    

    for(int i = 0; i<NBR_DE_TEXTURES; ++i){
        world->blocks[i].SrcR.x = X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i%11);
        world->blocks[i].SrcR.y = Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i/11);
        world->blocks[i].SrcR.h = TAILLE_TEXTURES;
        world->blocks[i].SrcR.w = TAILLE_TEXTURES;

        world->blocks[i].DestR.x =  0;
        world->blocks[i].DestR.y = 0;
        world->blocks[i].DestR.h = TAILLE_TEXTURES;
        world->blocks[i].DestR.w = TAILLE_TEXTURES;
    }

    world->joueur = calloc(1, sizeof(sprite_t));

    world->joueur->SrcR.x = 0;
    world->joueur->SrcR.y = 0;
    world->joueur->SrcR.w = 64;
    world->joueur->SrcR.h = 64+32;

    world->joueur->DestR.x = 350;
    world->joueur->DestR.y = 721 - (64+32) - 63*3;
    world->joueur->DestR.w = 64;
    world->joueur->DestR.h = 64+32;

    
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->DestR.x = x;
    sprite->DestR.y = y;
    sprite->DestR.w = w;
    sprite->DestR.h = h;
    sprite->v = v;
    sprite->is_visible = 1;
    sprite->is_deleted = 0;
}

void set_invisible(sprite_t *sprite){

}
void init_textures(world_t *world){

}

