/**
 * @file graphic.c
 * @brief Exécutable du module de la partie graphique.
 * @author Esteban DOUILLET, SCHNEIDER Paul
 * @date 30 Novembre 2022
 */
#include "graphic.h"
#include <dirent.h>

void clean_ressources(ressources_t *ressources) {
    clean_texture(ressources->background);
    clean_texture(ressources->player);
    clean_texture(ressources->blocks);
    clean_texture(ressources->exit);
    clean_texture(ressources->save);
    clean_texture(ressources->resume);
    clean_texture(ressources->newGame);
    clean_texture(ressources->letter_e);
    clean_font(ressources->score);
}

void init_ressources(SDL_Renderer *renderer, ressources_t *ressources, game_t *game) {
    if (strcmp(game->level, "classic") != 0) clean_ressources(ressources);

    // Récupère les assets en fonction du niveau
    char blocks[100];
    char background[100];
    sprintf(blocks, "../assets/%s.bmp", game->level);
    sprintf(background, "../assets/%s_bg.bmp", game->level);

    ressources->blocks = load_image(blocks, renderer);
    ressources->background = load_image(background, renderer);
    ressources->player = load_image("../assets/player.bmp", renderer);
    ressources->exit = load_image("../assets/button-exit.bmp", renderer);
    ressources->save = load_image("../assets/button-save.bmp", renderer);
    ressources->resume = load_image("../assets/button-resume.bmp", renderer);
    ressources->newGame = load_image("../assets/button-new.bmp", renderer);
    ressources->letter_e = load_image("../assets/lettre.bmp", renderer);
    ressources->score = load_font("../assets/font.ttf", 200);
}

void refresh_graphics(SDL_Renderer *renderer, game_t *game, world_t *world, ressources_t *ressources,
                      keyboard_status_t *keyboard) {
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
                    handle_collision(game, world, &world->blocks[i][j], keyboard);

                    // Affiche le joueur selon la caméra
                    SDL_RendererFlip flip =
                            world->blocks[i][j].DestR.x < world->player->DestR.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

                    SDL_RenderCopyEx(renderer, ressources->blocks,
                                     &world->textures[world->blocks[i][j].textureIndex].SrcR, &block, 0., NULL, flip);
                } else {
                    if (world->blocks[i][j].textureIndex == 4 && world->blocks[i][j].print_e == true) {
                        world->letter_e->DestR.x = block.x + 4;
                        world->letter_e->DestR.y = block.y - 50;

                        SDL_RenderCopy(renderer, ressources->letter_e,
                                       &world->letter_e->SrcR, &world->letter_e->DestR);
                    }
                    SDL_RenderCopy(renderer, ressources->blocks,
                                   &world->textures[world->blocks[i][j].textureIndex].SrcR, &block);
                }
            }
        }
    }
    // Affichage du score
    char buff[20];
    sprintf(buff, "SCORE : %d", game->score);

    apply_text(renderer, 10, 10, 150, 50, buff, ressources->score);

    if (world->counter_score_vie >= 100) {
        world->hearts++;
        world->counter_score_vie = 0;
    }

    // Affichage des vies

    for (int i = 0; i < world->hearts; ++i) {
        SDL_Rect pos_lives;
        pos_lives.x = SCREEN_W - 100 - i * (WIDTH_PLAYER + 20);
        pos_lives.y = 10;
        pos_lives.w = WIDTH_PLAYER * 0.7;
        pos_lives.h = HEIGHT_PLAYER * 0.7;
        SDL_RenderCopy(renderer, ressources->player,
                       &world->player->SrcR, &pos_lives);
    }




    // Incrémente le nombre de cycles
    if (world->cycles == 180) world->cycles = 0;
    else world->cycles++;

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
    if (world->cycles % 60 == 0) blobs_animations(block);
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

    // Affichage du menu

    if (world->menu) {
        int x = SCREEN_W / 2 - 800 / 2;
        int y = SCREEN_H / 8;
        apply_text(renderer, x, y, 800, 100, "Super (Mario) Bros", ressources->score);
        apply_text(renderer, x + 400, y + 100, 200, 50, "(lite)", ressources->score);
    }
    if (world->pause && world->cycles_pause < 400) {
        int x = SCREEN_W / 2 - 800 / 2;
        int y = SCREEN_H / 8;
        apply_text(renderer, x, y, 800, 100, "En pause..", ressources->score);
    }
    if (world->cycles_pause % 500 == 0) world->cycles_pause = 0;

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
            // Affiche le bouton
            world->buttons[i].DestR.y = 300 + i * 90;
            if (i == 0 && save) SDL_RenderCopy(renderer, ressources->resume, NULL, &world->buttons[i].DestR);
            else if (i == 1) SDL_RenderCopy(renderer, ressources->newGame, NULL, &world->buttons[i].DestR);
            else if (i == 2) SDL_RenderCopy(renderer, ressources->exit, NULL, &world->buttons[i].DestR);
            world->buttons[3].enable = false;
            world->buttons[1].enable = true;
        }

        if (world->pause) {
            //Incrementation du cycle de pause
            world->cycles_pause++;
            // Affiche le bouton
            world->buttons[i].DestR.y = i != 3 ? 300 + i * 90 : 300 + 90;
            if (i == 0) SDL_RenderCopy(renderer, ressources->resume, NULL, &world->buttons[i].DestR);
            else if (i == 2) SDL_RenderCopy(renderer, ressources->exit, NULL, &world->buttons[i].DestR);
            else if (i == 3) SDL_RenderCopy(renderer, ressources->save, NULL, &world->buttons[i].DestR);
            world->buttons[3].enable = true;
            world->buttons[1].enable = false;
        }
    }

    // Met à jour l'écran
    update_screen(renderer);
}

void blobs_animations(sprite_t *block) {
    // Itère l'image de la pièce
    if (block->textureIndex >= 10 && block->textureIndex <= 11) {
        block->textureIndex++;
        if (block->textureIndex == 12) block->textureIndex = 10; // Recommence le cycle
    }
}
