#include "world.h"

void init_data(world_t *world){
    world->sprites = calloc(NBR_DE_TEXTURES, sizeof(world->sprites)+sizeof(world->sprites));
    

    for(int i = 0; i<NBR_DE_TEXTURES; ++i){
        world->sprites[i].SrcR.x = X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i%11);
        world->sprites[i].SrcR.y = Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i/11);
        world->sprites[i].SrcR.h = TAILLE_TEXTURES;
        world->sprites[i].SrcR.w = TAILLE_TEXTURES;

        world->sprites[i].DestR.x = 0;
        world->sprites[i].DestR.y = 0;
        world->sprites[i].DestR.h = TAILLE_TEXTURES;
        world->sprites[i].DestR.w = TAILLE_TEXTURES;
        
    }
    
}


void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->v = v;
    sprite->is_visible = 1;
    sprite->is_deleted = 0;
}