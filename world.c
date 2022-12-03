/**
 * @file world.c
 * @brief Exécutable concernant le module : world
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */
#include "world.h"

void init_world(world_t *world) {
    world->end = true;
    world->textures = calloc(NUMBER_OF_TEXTURES, sizeof(sprite_t));
    world->cycles = 0;
    world->hearts = 3;
    world->scores = 0;
    world->buttons = calloc(4, sizeof(button_t));
    world->menu = true;
    world->pause = false;

    // Initialisation des images de tous les blocs
    for (int i = 1; i < NUMBER_OF_TEXTURES; ++i) {
        init_sprite(&world->textures[i], X_FIRST_TEXTURE + (SIZE_TEXTURES + SHIFT_TEXTURE) * ((i - 1) % 11),
                    Y_FIRST_TEXTURE + (SIZE_TEXTURES + SHIFT_TEXTURE) * ((i - 1) / 11),
                    SIZE_TEXTURES, SIZE_TEXTURES, 0, 0, SIZE_TEXTURES, SIZE_TEXTURES, i);
    }

    // Initialisation de l'image du joueur
    world->player = calloc(1, sizeof(sprite_t));
    init_sprite(world->player, 4, 0, WIDTH_PLAYER, HEIGHT_PLAYER, 350, 720 - 3 * HEIGHT_PLAYER, WIDTH_PLAYER,
                HEIGHT_PLAYER, TEXTURE_INDEX_PLAYER);

    world->map = malloc(sizeof(map_t));
    world->map->tab = lire_fichier("../assets/map.txt");

    // Récupération de la taille de la map
    taille_fichier("../assets/map.txt", &world->map->nb_row, &world->map->nb_col);

    // Initialisation de tous les blocs sur la map
    world->blocks = calloc(sizeof(sprite_t *), world->map->nb_row);
    for (int i = 0; i < world->map->nb_row; i++) {
        world->blocks[i] = calloc(sizeof(sprite_t), world->map->nb_col);
        for (int j = 0; j < world->map->nb_col; ++j) {
            sprite_t sprite;
            int textureIndex = world->map->tab[i][j];
            SDL_Rect SrcR = world->textures[textureIndex].SrcR;
            init_sprite(&sprite, SrcR.x, SrcR.y, SrcR.w, SrcR.h, j * SIZE_TEXTURES,
                        i * SIZE_TEXTURES, SIZE_TEXTURES, SIZE_TEXTURES, textureIndex);
            world->blocks[i][j] = sprite;
        }
    }
}

void init_cam(world_t *world, cam_t *cam, int w, int h) {
    cam->x = world->player->DestR.x - w / 2;
    cam->y = world->player->DestR.y - h / 2;
    cam->h = h;
    cam->w = w;
    world->cam = cam;
}

void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int textureIndex) {
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

    // Définition des mouvements des images
    sprite->saut = false;
    sprite->timeSinceJumpStart = 0;

    // Définition des autres paramètres de l'image
    sprite->v = SPEED_X_WALK;
    sprite->textureIndex = textureIndex;
    sprite->isright = true;
}

void repositioning_camera(world_t *world) {
    world->cam->x = world->player->prec.x - world->cam->w / 2;
    world->cam->y = world->player->prec.y - world->cam->h / 2;
}

void blob_movement(world_t *world, sprite_t *sprite) {
    sprite->prec = sprite->DestR;

    if (world->cycles % 180 == 0) {
        sprite->saut = true;
        sprite->ground = sprite->DestR.y;
        if (world->player->DestR.x >= sprite->DestR.x) sprite->isright = true;
        else sprite->isright = false;
    }

    // Vérifie si le blob ne saute pas (gravité)
    if (sprite->saut == false) {
        sprite->DestR.y += sprite->timeSinceJumpStart * GRAVITY;
        sprite->timeSinceJumpStart++;
    }
    // Vérifie la gravité lors d'un saut
    if (sprite->saut == true) {
        sprite->DestR.y = (int) round(sprite->ground - JUMP_BLOB_SPEED * sprite->timeSinceJumpStart
                                      +
                                      0.5 * GRAVITY * sprite->timeSinceJumpStart * sprite->timeSinceJumpStart);
        sprite->timeSinceJumpStart++;
        if (sprite->isright == true) sprite->DestR.x += sprite->v;
        else sprite->DestR.x -= sprite->v;
    }
}
