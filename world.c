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
                        SIZE_TEXTURES, SIZE_TEXTURES, 0, 0, SIZE_TEXTURES, SIZE_TEXTURES, i, false);
        }

        world->player = calloc(1, sizeof(sprite_t));
        world->letter_e = calloc(1, sizeof(sprite_t));

        init_sprite(world->letter_e, 0, 0, 512, 512, 0, 0, 56, 56, 0, false);

        // Définition des boutons pour le menu
        world->buttons = calloc(4, sizeof(button_t));
        for (int i = 0; i < 4; ++i) {
            world->buttons[i].DestR.x = (1080 - 375 / 2) / 2;
            world->buttons[i].DestR.y = 300 + i * 90;
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

        world->counter_score_vie = 0;
    }

    world->cycles = 0;
    world->hearts = new_game ? 3 : world->hearts;
    world->counter_score_vie = game->score % 100;
    world->end = !new_game && !world->newLevel;
    world->menu = !new_game && !world->newLevel;
    world->go_menu = false;
    world->pause = false;
    world->newLevel = false;

    // Initialisation de l'image du joueur
    init_sprite(world->player, 4, 0, WIDTH_PLAYER, HEIGHT_PLAYER, 350, 720 - 3 * HEIGHT_PLAYER, WIDTH_PLAYER,
                HEIGHT_PLAYER, TEXTURE_INDEX_PLAYER, false);

    init_blocks(world);
}

void init_blocks(world_t *world) {
    // Initialisation de tous les blocs sur la map
    for (int i = 0; i < world->map->nb_row; i++) {
        for (int j = 0; j < world->map->nb_col; ++j) {
            sprite_t sprite;
            int textureIndex = world->map->tab[i][j];
            SDL_Rect SrcR = world->textures[textureIndex].SrcR;
            init_sprite(&sprite, SrcR.x, SrcR.y, SrcR.w, SrcR.h, j * SIZE_TEXTURES,
                        i * SIZE_TEXTURES, SIZE_TEXTURES, SIZE_TEXTURES, textureIndex, false);
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

void init_sprite(sprite_t *sprite, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, int textureIndex,
                 bool print_e) {
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
    sprite->print_e = print_e;
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
        if (world->player->isAttacked == false) {
            if (sprite->isright == true) sprite->DestR.x += sprite->v;
            else sprite->DestR.x -= sprite->v;
        }

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

void new_level(SDL_Renderer *renderer, game_t *game, ressources_t *ressources) {
    char mapPathBlocks[100] = "../assets/classic.bmp";
    char mapPathBG[100] = "../assets/classic_bg.bmp";
    if (strcmp(game->level, "END") != 0) {
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
        if (strcmp(game->level, "classic") == 0) sprintf(game->level, "snow");
        else if (strcmp(game->level, "snow") == 0) sprintf(game->level, "lava");
        else
            sprintf(game->level, "END");

        // Vérifie si s'il y a un prochain niveau
        if (strcmp(game->level, "END") != 0) {
            clean_data(world);
            new_level(renderer, game, ressources);
            init_world(game, world, false);
        } else {
            new_level(renderer, game, ressources);
            sprintf(game->level, "classic");
            world->end = true;
            world->go_menu = true;
            world->cycles_pause = 0;
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

void export_blocks_in_map(world_t *world) {
    // Défini les dimensions
    int nb_col = world->map->nb_col;
    int nb_row = world->map->nb_row;

    // Vide la map
    for (int i = 0; i < nb_row; ++i) {
        for (int j = 0; j < nb_col; ++j) world->map->tab[i][j] = 0;
    }

    // Rempli la map
    for (int i = 0; i < nb_row; ++i) {
        for (int j = 0; j < nb_col; ++j) {
            // Redéfini la position dans le tab
            sprite_t *block = &world->blocks[i][j];
            int colIndex = block->DestR.x / block->DestR.w;
            int rowIndex = block->DestR.y / block->DestR.h;
            int textureIndex = world->map->tab[rowIndex][colIndex];

            // Vérifie que le bloc de destination est vide (ou que c'est un blob)
            if (textureIndex != 0 && block->textureIndex != 10 && block->textureIndex != 11) continue;

            // Redéfini la texture du bloc
            world->map->tab[rowIndex][colIndex] = block->textureIndex;
        }
    }
}

void save_world(world_t *world, char folder[100]) {
    // Crée le dossier des données du monde
    char worldFolder[150];
    sprintf(worldFolder, "%s/world", folder);

    // Crée le répertoire dédié
    mkdir(worldFolder, 0700);

    // Sauvegarde toutes les données du monde
    save_blocks(world, worldFolder);
    save_details(world, worldFolder);
    save_player(world, worldFolder);
}

void save_player(world_t *world, char folder[100]) {
    // Défini le chemin vers le fichier
    char playerFileName[100];
    sprintf(playerFileName, "%s/player.txt", folder);

    // Crée et ouvre le fichier en mode écriture
    FILE *playerFile = NULL;
    playerFile = fopen(playerFileName, "w");

    // Inscris les détails
    char player[100];
    sprintf(player, "%i\n%i\n%i\n%i\n%i\n%i\n%i\n%i\n%i", world->player->DestR.x, world->player->DestR.y,
            world->player->prec.x, world->player->prec.y, world->player->timeSinceJumpStart, world->player->isright,
            world->player->saut, world->player->ground, world->player->print_e);

    // Ajoute le contenu du fichier qui est fermé après
    fputs(player, playerFile);
    fclose(playerFile);
}

void save_details(world_t *world, char folder[100]) {
    // Défini le chemin vers le fichier
    char detailsFileName[100];
    sprintf(detailsFileName, "%s/details.txt", folder);

    // Crée et ouvre le fichier en mode écriture
    FILE *detailsFile = NULL;
    detailsFile = fopen(detailsFileName, "w");

    char details[100];
    sprintf(details, "%i\n%i\n%i\n%i\n%i\n%i", world->cycles, world->hearts, world->end, world->menu, world->pause,
            world->newLevel);

    // Ajoute le contenu du fichier qui est fermé après
    fputs(details, detailsFile);
    fclose(detailsFile);
}

void save_blocks(world_t *world, char folder[100]) {
    // Exporte les positions finales des blocs
    export_blocks_in_map(world);

    // Sauvegarder tous les blocs
    char blocksFiles[150];
    sprintf(blocksFiles, "%s/blocks.txt", folder);

    // Retranscris la matrice dans le fichier
    ecrire_fichier(blocksFiles, world->map->tab, world->map->nb_col, world->map->nb_row);
}

void load_world(world_t *world) {
    load_blocks(world);
    load_player(world);
    load_details(world);
}

void load_player(world_t *world) {
    FILE *fichier = NULL;
    char line[50];
    int size = 50;
    int step = 0;
    fichier = fopen("../backups/world/player.txt", "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        // Parcours toutes les lignes
        while (fgets(line, size, fichier) != NULL) {
            int value = (int) strtol(line, NULL, 10);

            switch (step) {
                case 0:
                    world->player->DestR.x = value;
                    break;
                case 1:
                    world->player->DestR.y = value;
                    break;
                case 2:
                    world->player->prec.x = value;
                    break;
                case 3:
                    world->player->prec.y = value;
                    break;
                case 4:
                    world->player->timeSinceJumpStart = value;
                    break;
                case 5:
                    world->player->isright = (bool) value;
                    break;
                case 6:
                    world->player->saut = (bool) value;
                    break;
                case 7:
                    world->player->ground = value;
                    break;
                default:
                    world->player->print_e = (bool) value;
                    break;
            }
            step++;
        }

        fclose(fichier);
    }
}

void load_blocks(world_t *world) {
    world->map->tab = lire_fichier("../backups/world/blocks.txt");
    init_blocks(world);
}

void load_details(world_t *world) {
    FILE *fichier = NULL;
    char line[50];
    int size = 50;
    int step = 0;
    fichier = fopen("../backups/world/details.txt", "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        // Parcours toutes les lignes
        while (fgets(line, size, fichier) != NULL) {
            int value = atoi(line);

            // Initialisation de l'image du joueur
            switch (step) {
                case 0:
                    world->cycles = value;
                    break;
                case 1:
                    world->hearts = value;
                    break;
                case 2:
                    world->end = (bool) value;
                    break;
                case 3:
                    world->menu = (bool) value;
                    break;
                default:
                    world->pause = (bool) value;
                    break;
            }

            step++;
        }

        fclose(fichier);
    }
}
