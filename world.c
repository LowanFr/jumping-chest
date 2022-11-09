#include "world.h"

void init_textures(world_t *world){
    world->textures = calloc(NBR_DE_TEXTURES, sizeof(world->textures->DestR)+sizeof(world->textures->SrcR));
    

    for(int i = 0; i<NBR_DE_TEXTURES; ++i){
        world->textures[i].SrcR.x = X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i%11);
        world->textures[i].SrcR.y = Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i/11);
        world->textures[i].SrcR.h = TAILLE_TEXTURES;
        world->textures[i].SrcR.w = TAILLE_TEXTURES;

        world->textures[i].DestR.x = 0;
        world->textures[i].DestR.y = 0;
        world->textures[i].DestR.h = TAILLE_TEXTURES;
        world->textures[i].DestR.w = TAILLE_TEXTURES;
        
    }
}