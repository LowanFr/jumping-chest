
#include "logique.h"

void init_textures(world_t *world){
    world->textures = malloc(sizeof(world->textures) * NBR_DE_TEXTURES);
    int x = 0;
    int y = 0;

    for(int i = 0; i<NBR_DE_TEXTURES; ++i){
        world->textures[i].SrcR.x = X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i%11);
        world->textures[i].SrcR.y = Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * (i/11);
        world->textures[i].SrcR.h = TAILLE_TEXTURES;
        world->textures[i].SrcR.w = TAILLE_TEXTURES;
    }
}