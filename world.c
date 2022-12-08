/**
 * @file world.c
 * @brief Exécutable concernant le module : world
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */
#include "world.h"

void init_world(game_t *game, world_t *world, bool new_game) {
    if (!new_game) {
        // Initialisation des images de tous les blocs
        world->textures = calloc(NUMBER_OF_TEXTURES, sizeof(sprite_t));
        for (int i = 1; i < NUMBER_OF_TEXTURES; ++i) {
            init_sprite(&world->textures[i], X_FIRST_TEXTURE + (SIZE_TEXTURES + SHIFT_TEXTURE) * ((i - 1) % 11),
                        Y_FIRST_TEXTURE + (SIZE_TEXTURES + SHIFT_TEXTURE) * ((i - 1) / 11),
                        SIZE_TEXTURES, SIZE_TEXTURES, 0, 0, SIZE_TEXTURES, SIZE_TEXTURES, i);
        }

        world->player = calloc(1, sizeof(sprite_t));

        // Définition des boutons pour le menu
        world->buttons = calloc(4, sizeof(button_t));
        for (int i = 0; i < 4; ++i) {
            world->buttons[i].DestR.x = (1080 - 375 / 2) / 2;
            world->buttons[i].DestR.y = i != 3 ? 220 + i * 90 : 310;
            world->buttons[i].DestR.w = 375;
            world->buttons[i].DestR.h = 75;
            world->buttons[i].type = i;
            world->buttons[i].enable = i < 3;
        }

        // Défini le nom de la carte
        char mapPath[100];
        sprintf(mapPath, "../assets/map-%s.txt", game->level);

        // Récupération de la carte
        world->map = malloc(sizeof(map_t));
        world->map->tab = lire_fichier(mapPath);

        // Récupération de la taille de la map
        taille_fichier(mapPath, &world->map->nb_row, &world->map->nb_col);

        // Initialisation de tous les blocs sur la map
        world->blocks = calloc(sizeof(sprite_t *), world->map->nb_row);
        for (int i = 0; i < world->map->nb_row; i++) world->blocks[i] = calloc(sizeof(sprite_t), world->map->nb_col);
    }

    world->cycles = 0;
    world->hearts = 3;
    world->end = !new_game && !world->newLevel;
    world->menu = !new_game;
    world->pause = false;
    world->newLevel = false;

    // Initialisation de l'image du joueur
    init_sprite(world->player, 4, 0, WIDTH_PLAYER, HEIGHT_PLAYER, 350, 720 - 3 * HEIGHT_PLAYER, WIDTH_PLAYER,
                HEIGHT_PLAYER, TEXTURE_INDEX_PLAYER);

    // Initialisation de tous les blocs sur la map
    for (int i = 0; i < world->map->nb_row; i++) {
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
    sprite->isAttacked = false;
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

void clean_data(world_t *world) {
    // Libère toute la mémoire utilisée pour le monde
    desallouer_tab_2D(world->map->tab, world->map->nb_row);
    for (int i = 0; i < world->map->nb_row; i++) free(world->blocks[i]); // Libère toutes les lignes
    free(world->buttons);
    free(world->blocks);
    free(world->map);
    free(world->textures);
    free(world->player);
}

void new_level(SDL_Renderer *renderer, game_t *game, ressources_t *ressources, bool restart) {
    char mapPathBlocks[100] = "../assets/classic.bmp";
    char mapPathBG[100] = "../assets/classic_bg.bmp";
    if (!restart) {
        // Défini le nom de la carte
        sprintf(mapPathBlocks, "../assets/%s.bmp", game->level);
        sprintf(mapPathBG, "../assets/%s_bg.bmp", game->level);
    }

    // Défini les ressources liées à l'image
    ressources->blocks = load_image(mapPathBlocks, renderer);
    ressources->background = load_image(mapPathBG, renderer);
}

void refresh_level(SDL_Renderer *renderer, game_t *game, ressources_t *ressources, world_t *world) {
    // Mise à jour du niveau si besoin avec les nouvelles textures
    if (world->newLevel) {
        // Pause pendant 2sec
        SDL_Delay(2000);

        // Modifie les textures en fonction du niveau
        if (strcmp(game->level, "classic") == 0) game->level = "snow";
        else if (strcmp(game->level, "snow") == 0) game->level = "lava";
        else game->level = "END";

        // Vérifie si s'il y a un prochain niveau
        if (strcmp(game->level, "END") != 0) {
            clean_data(world);
            new_level(renderer, game, ressources, false);
            init_world(game, world, false);
        } else {
            new_level(renderer, game, ressources, true);
            game->level = "classic";
            world->end = true;
            world->menu = true;
        }
    }
}

SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer) {
    // Charge l'image à partir du chemin
    SDL_Surface *surface = SDL_LoadBMP(fileName);

    // Converti la surface en texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
