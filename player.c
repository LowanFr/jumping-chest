/**
 * @file player.c
 * @brief Exécutable concernant le module : player.
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */
#include "player.h"

void init_player(player_t *joueur, world_t *world) {
    joueur->sprite = world->player;
    joueur->saut = false;
    joueur->timeSinceJumpStart = 0;
}

void player_movement(keyboard_status_t *touches, player_t *player) {
    // Sauvegarde des coordonnées précédentes
    player->prec = player->sprite->DestR;

    // Vérifie le déplacement à gauche
    if (touches->left) player->sprite->DestR.x -= player->sprite->v;

    // Vérifie le déplacement à droite
    if (touches->right) player->sprite->DestR.x += player->sprite->v;

    // Vérifie un saut
    if (touches->space && player->timeSinceJumpStart == 0) {
        player->ground = player->sprite->DestR.y;
        player->saut = true;
    }

    // Vérifie si le joueur ne saute pas (gravité)
    if (player->saut == false) {
        player->sprite->DestR.y += player->timeSinceJumpStart * GRAVITY;
        player->timeSinceJumpStart++;
    }

    // Vérifie la gravité lors d'un saut
    if (player->saut == true) {
        player->sprite->DestR.y = (int) round(player->ground - JUMP_SPEED * player->timeSinceJumpStart
                                              +
                                              0.5 * GRAVITY * player->timeSinceJumpStart * player->timeSinceJumpStart);
        player->timeSinceJumpStart++;
    }
}

void handle_collision(world_t *world, player_t *player) {
    // Vérification des collisions avec les blocs qui entoure le joueur
    for (int i = player->sprite->DestR.y / SIZE_TEXTURES - 2;
         i <= player->sprite->DestR.y / SIZE_TEXTURES + 2; ++i) {
        for (int j = player->sprite->DestR.x / SIZE_TEXTURES - 1;
             j <= player->sprite->DestR.x / SIZE_TEXTURES + 1; ++j) {
            handle_collision_solidBlock(world, player, i, j);
            handle_collision_pieces(world, player, i, j);
        }
    }
}

void handle_collision_pieces(world_t *world, player_t *player, int i, int j) {
    // Vérifie que le bloc existe
    if (i >= world->map->nb_row || i < 0 || j >= world->map->nb_col || j < 0) return;

    int nb = world->map->tab[i][j];
    SDL_Rect DestR = world->blocks[i][j].DestR;

    // Collision en bas
    bool condCollision1 = DestR.y < player->sprite->DestR.y + player->sprite->DestR.h &&
                          DestR.y + DestR.h > player->sprite->DestR.y;
    bool condCollision2 = DestR.x < player->sprite->DestR.x + player->sprite->DestR.w &&
                          DestR.x + DestR.w > player->sprite->DestR.x;
    bool condCollision3 = nb >= 6 && nb <= 9;

    // Vérifie qu'il y a une collision et que c'est bloc solide
    if (!condCollision1 || !condCollision2 || !condCollision3) return;

    // Collision
    world->map->tab[i][j] = 0;
}


void handle_collision_solidBlock(world_t *world, player_t *player, int i, int j) {
    // Vérifie que le bloc existe
    if (i >= world->map->nb_row || i < 0 || j >= world->map->nb_col || j < 0) return;

    int nb = world->map->tab[i][j];
    SDL_Rect DestR = world->blocks[i][j].DestR;

    // Collision en bas
    bool condCollision1 = DestR.y < player->sprite->DestR.y + player->sprite->DestR.h &&
                          DestR.y + DestR.h > player->sprite->DestR.y;
    bool condCollision2 = DestR.x < player->sprite->DestR.x + player->sprite->DestR.w &&
                          DestR.x + DestR.w > player->sprite->DestR.x;
    bool condCollision3 = nb == 1 || nb == 2 || nb == 3 || nb == 12 || nb == 13 || nb == 14 || nb == 23 ||
                          nb == 24 || nb == 25 || nb == 18 || nb == 19 || nb == 29 || nb == 30;

    // Vérifie qu'il y a une collision et que c'est bloc solide
    if (!condCollision1 || !condCollision2 || !condCollision3) return;

    // Collision en haut du bloc
    if (DestR.y < player->sprite->DestR.y + player->sprite->DestR.h &&
        // Si le haut du bloc est en collision avec le bas du player
        player->sprite->DestR.y < DestR.y && // Si le haut du joueur est bien inférieur au haut du bloc
        player->prec.y + player->prec.h <=
        DestR.y) { // Si la position précédente du bas du joueur est bien inférieure au haut du bloc
        player->saut = false;
        player->prec.y = DestR.y - player->prec.h;
        player->sprite->DestR.y = player->prec.y;
        player->timeSinceJumpStart = 0;
    }

        // Collision à gauche du bloc
    else if (DestR.x < player->sprite->DestR.x + player->sprite->DestR.w &&
             // Côté gauche du bloc est inférieur au côté droit du player
             DestR.x > player->sprite->DestR.x && // Coté gauche du bloc est inférieur au côté droit du joueur
             player->prec.x + player->prec.w <=
             DestR.x) {  // Côté gauche précédent est bien inférieur ou égal au côté gauche du bloc
        player->prec.x = DestR.x - player->prec.w;
        player->sprite->DestR.x = player->prec.x;

    }

        // Collision à droite du bloc
    else if (DestR.x + DestR.w > player->sprite->DestR.x && // Ce côté droit du bloc est < au côté gauche du joueur
             DestR.x < player->sprite->DestR.x && // Côté gauche du player est < au côté gauche du bloc
             player->prec.x >= DestR.x + DestR.w) { // Côté gauche précédent est bien > au côté droit du bloc
        player->prec.x = DestR.x + DestR.w;
        player->sprite->DestR.x = player->prec.x;
    }

        // Collision en bas du bloc
    else if (DestR.y + DestR.h > player->sprite->DestR.y && // Si collision "bas" du bloc et haut du player
             player->sprite->DestR.y > DestR.y && // Si le haut du joueur est bien supérieur au haut du bloc
             player->prec.y >= DestR.y + DestR.h) {  // Si le précédent du joueur est en dehors du bloc
        player->saut = false;
        player->timeSinceJumpStart = 1; // = 1 évite de pouvoir re-sauter en dessous du bloc
        player->prec.y = DestR.y + DestR.h;
        player->sprite->DestR.y = player->prec.y;
    }
}
