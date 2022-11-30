/**
 * @file world.c
 * @brief Exécutable concernant le module : world
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */
#include "world.h"

void init_world(world_t *world) {
    world->end = false;
    world->blocks = calloc(NBR_DE_TEXTURES, sizeof(sprite_t));

    // Initialisation des images de tous les blocs
    for(int i = 1; i < NBR_DE_TEXTURES; ++i) {
        init_sprite(&world->blocks[i], X_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * ((i-1)%11),
                    Y_PREMIERE_TEXTURE + (TAILLE_TEXTURES + DECALAGE_TEXTURE) * ((i-1)/11),
                    TAILLE_TEXTURES,TAILLE_TEXTURES, 0, 0, TAILLE_TEXTURES,TAILLE_TEXTURES);
    }

    // Initialisation de l'image du joueur
    world->player = calloc(1, sizeof(sprite_t));
    init_sprite(world->player, 4, 0, LARGEUR_PLAYER, HAUTEUR_PLAYER, 350, 720 - 3 * HAUTEUR_PLAYER, LARGEUR_PLAYER, HAUTEUR_PLAYER);

    world->map = malloc(sizeof(map_t));
    world->map->tab = lire_fichier("../assets/map.txt");

    // Récupération de la taille de la map
    taille_fichier("../assets/map.txt", &world->map->nb_row, &world->map->nb_col);

    // Initialisation de tous les blocs sur la map
    world->map->DestR = calloc(sizeof(SDL_Rect*), world->map->nb_row);
    for (int i = 0; i < world->map->nb_row; i++) {
        world->map->DestR[i] =  calloc(sizeof(SDL_Rect), world->map->nb_col);
        for(int j = 0; j < world->map->nb_col; ++j){
            world->map->DestR[i][j].x = j*TAILLE_TEXTURES;
            world->map->DestR[i][j].y = i*TAILLE_TEXTURES;
            world->map->DestR[i][j].h = TAILLE_TEXTURES;
            world->map->DestR[i][j].w = TAILLE_TEXTURES;
        }
    }
}

void init_cam(world_t *world, cam_t *cam, int w, int h) {
    cam->x = world->player->DestR.x - w/2;
    cam->y = world->player->DestR.y - h/2;
    cam->h = h;
    cam->w = w;
    world->cam = cam;
}

void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    // Définition du rectangle de source
    sprite->SrcR.x = x1;
    sprite->SrcR.y = y1;
    sprite->SrcR.w = w1;
    sprite->SrcR.h = h1;

    // Définition de mon rectangle de destination
    sprite->DestR.x = x2;
    sprite->DestR.y = y2;
    sprite->DestR.w = w2;
    sprite->DestR.h = h2;

    // Définition des autres paramètres de l'image
    sprite->v = VITESSE_X_MARCHE;
}

void repositioning_camera(cam_t *camera, SDL_Rect *player) {
    camera->x = player->x - camera->w/2;
    camera->y = player->y - camera->h/2;
}
