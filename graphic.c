/**
 * @file graphic.c
 * @brief Exécutable du module de la partie graphique.
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "graphic.h"
#include <dirent.h>

SDL_Texture *load_image(const char *fileName, SDL_Renderer *renderer) {
    // Charge l'image à partir du chemin
    SDL_Surface *surface = SDL_LoadBMP(fileName);

    // Converti la surface en texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void clean_ressources(ressources_t *ressources) {
    clean_texture(ressources->background);
    clean_texture(ressources->player);
    clean_texture(ressources->blocks);
}

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources) {
    ressources->background = load_image("../assets/classic_bg.bmp", renderer);
    ressources->player = load_image("../assets/player.bmp", renderer);
    ressources->blocks = load_image("../assets/classic.bmp", renderer);
    ressources->exit = load_image("../assets/exit-button.bmp", renderer);
    ressources->save = load_image("../assets/save-button.bmp", renderer);
    ressources->resume = load_image("../assets/resume-button.bmp", renderer);
    ressources->newGame = load_image("../assets/new-button.bmp", renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, ressources_t *ressources, keyboard_status_t *keyboard) {
    // Vide le moteur de rendu
    clear_renderer(renderer);

    // Affiche l'arrière-plan
    SDL_RenderCopy(renderer, ressources->background, NULL, NULL);

    // Affiche tous les blocs présents sur la caméra (et un peu plus haut pour les sauts des blobs)
    for (int i = 0; i < world->map->nb_row; ++i) {
        for (int j = 0; j < world->map->nb_col; ++j) {
            SDL_Rect block = world->blocks[i][j].DestR;
            bool onCamera = block.y <= world->cam->y + world->cam->h &&
                            block.y + block.h >= world->cam->y - SIZE_TEXTURES * 4 &&
                            block.x <= world->cam->x + world->cam->w &&
                            block.x + block.w >= world->cam->x;

            // Affiche le bloc s'il y a une collision entre celui-ci et la caméra
            if (onCamera) {
                handle_animations(world, &world->blocks[i][j]);
                block.x -= world->cam->x;
                block.y -= world->cam->y;

                // Gérer les flips des blobs ainsi que leur déplacement/collisions
                if (world->blocks[i][j].textureIndex == 10 || world->blocks[i][j].textureIndex == 11) {
                    blob_movement(world, &world->blocks[i][j]);
                    handle_collision(world, &world->blocks[i][j]);

                    // Affiche le joueur selon la caméra
                    SDL_RendererFlip flip =
                            world->blocks[i][j].DestR.x < world->player->DestR.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
                    SDL_RenderCopyEx(renderer, ressources->blocks,
                                     &world->textures[world->blocks[i][j].textureIndex].SrcR, &block, 0., NULL, flip);
                } else
                    SDL_RenderCopy(renderer, ressources->blocks,
                                   &world->textures[world->blocks[i][j].textureIndex].SrcR, &block);
            }
        }
    }

    // Incrémente le nombre de cycles
    world->cycles++;

    // Affiche le joueur selon la caméra
    SDL_RendererFlip flip = keyboard->lastIsLeft == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_Rect block = world->player->DestR;
    block.x -= world->cam->x;
    block.y -= world->cam->y;
    SDL_RenderCopyEx(renderer, ressources->player, &world->player->SrcR, &block, 0., NULL, flip);

    // Met à jour l'écran
    update_screen(renderer);
}

void handle_animations(world_t *world, sprite_t *block) {
    // Anime les pièces tous les 30 cycles
    if (world->cycles % 30 == 0) coin_animations(block);
}

void coin_animations(sprite_t *block) {
    // Itère l'image de la pièce
    if (block->textureIndex >= 6 && block->textureIndex <= 9) {
        block->textureIndex++;
        if (block->textureIndex == 10) block->textureIndex = 6; // Recommence le cycle
    }
}

void refresh_menu(world_t *world, SDL_Renderer *renderer, ressources_t *ressources) {
    // Vide le moteur de rendu
    clear_renderer(renderer);

    // Affiche l'arrière-plan
    SDL_RenderCopy(renderer, ressources->background, NULL, NULL);

    bool save = false;
    struct dirent *dir;
    DIR *d = opendir("../backups");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".gitkeep") == 0 || strcmp(dir->d_name, "..") == 0 ||
                strcmp(dir->d_name, ".") == 0)
                continue;
            save = true;
        }
        closedir(d);
    }

    for (int i = 0; i < 4; i++) {
        if (world->menu) {
            SDL_Rect DestR;
            DestR.x = (1080 - 375 / 2) / 2;
            DestR.y = i != 3 ? 220 + i * 90 : 310;
            DestR.w = 375;
            DestR.h = 75;

            // Affiche le bouton
            if (i == 0 && save) SDL_RenderCopy(renderer, ressources->resume, NULL, &DestR);
            else if (i == 1) SDL_RenderCopy(renderer, ressources->newGame, NULL, &DestR);
            else if (i == 2) SDL_RenderCopy(renderer, ressources->exit, NULL, &DestR);

            // Défini le bouton
            world->buttons[i].enable = i < 3;
            world->buttons[i].DestR = DestR;
            world->buttons[i].type = i;
        }

        if (world->pause) {
            SDL_Rect DestR;
            DestR.x = (1080 - 375 / 2) / 2;
            DestR.y = i != 3 ? 220 + i * 90 : 310;
            DestR.w = 375;
            DestR.h = 75;

            // Affiche le bouton
            if (i == 0) SDL_RenderCopy(renderer, ressources->resume, NULL, &DestR);
            else if (i == 2) SDL_RenderCopy(renderer, ressources->exit, NULL, &DestR);
            else if (i == 3) SDL_RenderCopy(renderer, ressources->save, NULL, &DestR);

            // Défini le bouton
            world->buttons[i].enable = i < 3;
            world->buttons[i].DestR = DestR;
            world->buttons[i].type = i;
        }
    }

    // Met à jour l'écran
    update_screen(renderer);
}
