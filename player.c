/**
 * @file player.c
 * @brief Exécutable concernant le module : player.
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */
#include "player.h"

void player_movement(keyboard_status_t *touches, sprite_t *player) {
    // Sauvegarde des coordonnées précédentes
    player->prec = player->DestR;

    // Vérifie le déplacement à gauche
    if (touches->left) player->DestR.x -= player->v;

    // Vérifie le déplacement à droite
    if (touches->right) player->DestR.x += player->v;

    // Vérifie un saut
    if (touches->space && player->timeSinceJumpStart == 0) {
        player->ground = player->DestR.y;
        player->saut = true;
    }

    // Vérifie si le joueur ne saute pas (gravité)
    if (player->saut == false) {
        player->DestR.y += player->timeSinceJumpStart * GRAVITY;
        player->timeSinceJumpStart++;
    }

    // Vérifie la gravité lors d'un saut
    if (player->saut == true) {
        player->DestR.y = (int) round(player->ground - JUMP_SPEED * player->timeSinceJumpStart
                                              +
                                              0.5 * GRAVITY * player->timeSinceJumpStart * player->timeSinceJumpStart);
        player->timeSinceJumpStart++;
    }
}

void handle_collision(world_t *world, sprite_t *player) {
    // Vérification des collisions avec les blocs qui entoure le joueur
    for (int i = player->DestR.y / SIZE_TEXTURES - 2;
         i <= player->DestR.y / SIZE_TEXTURES + 2; ++i) {
        for (int j = player->DestR.x / SIZE_TEXTURES - 1;
             j <= player->DestR.x / SIZE_TEXTURES + 1; ++j) {
            // Vérifie que le bloc existe
            if (i >= world->map->nb_row || i < 0 || j >= world->map->nb_col || j < 0) continue;

            sprite_t *sprite = &world->blocks[i][j];
            handle_collision_solidBlock(player, sprite);
            handle_collision_pieces(player, sprite);
        }
    }

}

void handle_collision_pieces(sprite_t *player, sprite_t *sprite) {
    // Vérifie que c'est une pièce
    int textureIndex = sprite->textureIndex;
    if (textureIndex < 6 || textureIndex > 9) return;

    // Récupère les deux rectangles
    SDL_Rect *block = &sprite->DestR;
    SDL_Rect *playerImg = &player->DestR;

    // Collision en bas
    bool condCollision1 = block->y < playerImg->y + playerImg->h && block->y + block->h > playerImg->y;
    bool condCollision2 = block->x < playerImg->x + playerImg->w && block->x + block->w > playerImg->x;

    // Vérifie qu'il y a une collision et que c'est bloc solide
    if (!condCollision1 || !condCollision2) return;

    // Collision
    sprite->textureIndex = 0;
}

void handle_collision_solidBlock(sprite_t *player, sprite_t *sprite) {
    // Vérifie que c'est un bloc solide
    int index = sprite->textureIndex;
    bool solidBlock =
            index == 1 || index == 2 || index == 3 || index == 12 || index == 13 || index == 14 || index == 23 ||
            index == 24 || index == 25 || index == 18 || index == 19 || index == 29 || index == 30;
    if (!solidBlock) return;

    // Récupère les deux rectangles
    SDL_Rect *block = &sprite->DestR;
    SDL_Rect *playerImg = &player->DestR;

    // Collision en bas
    bool condCollision1 = block->y < playerImg->y + playerImg->h && block->y + block->h > playerImg->y;
    bool condCollision2 = block->x < playerImg->x + playerImg->w && block->x + block->w > playerImg->x;

    // Vérifie qu'il y a une collision et que c'est bloc solide
    if (!condCollision1 || !condCollision2) return;

    // Collision en haut du bloc
    if (block->y < playerImg->y + playerImg->h && // Si le haut du bloc est en collision avec le bas du player
        playerImg->y < block->y && // Si le haut du joueur est bien inférieur au haut du bloc
        player->prec.y + player->prec.h <=
        block->y) { // Si la position précédente du bas du joueur est bien inférieure au haut du bloc
        player->saut = false;
        player->prec.y = block->y - player->prec.h;
        playerImg->y = player->prec.y;
        player->timeSinceJumpStart = 0;
    }

        // Collision à gauche du bloc
    else if (block->x < playerImg->x + playerImg->w && // Côté gauche du bloc est inférieur au côté droit du player
             block->x > playerImg->x && // Coté gauche du bloc est inférieur au côté droit du joueur
             player->prec.x + player->prec.w <=
             block->x) {  // Côté gauche précédent est bien inférieur ou égal au côté gauche du bloc
        player->prec.x = block->x - player->prec.w;
        playerImg->x = player->prec.x;

    }

        // Collision à droite du bloc
    else if (block->x + block->w > playerImg->x && // Ce côté droit du bloc est < au côté gauche du joueur
             block->x < playerImg->x && // Côté gauche du player est < au côté gauche du bloc
             player->prec.x >= block->x + block->w) { // Côté gauche précédent est bien > au côté droit du bloc
        player->prec.x = block->x + block->w;
        playerImg->x = player->prec.x;
    }

        // Collision en bas du bloc
    else if (block->y + block->h > playerImg->y && // Si collision "bas" du bloc et haut du player
             playerImg->y > block->y && // Si le haut du joueur est bien supérieur au haut du bloc
             player->prec.y >= block->y + block->h) {  // Si le précédent du joueur est en dehors du bloc
        player->saut = false;
        player->timeSinceJumpStart = 1; // = 1 évite de pouvoir re-sauter en dessous du bloc
        player->prec.y = block->y + block->h;
        playerImg->y = player->prec.y;
    }
}
