/**
 * @file player.c
 * @brief Exécutable concernant le module : player
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 14 Novembre 2022
 */
#include "player.h"

void init_player(player_t *joueur, world_t *world){
    joueur->sprite = world->player;
    joueur->saut = false;
    joueur->timeSinceJumpStart = 0;
}

void player_movement(keyboard_status_t *touches, player_t *player) {
    // Vérifie le déplacement à gauche
    if (touches->left) {
        player->sprite->DestR.x = player->sprite->DestR.x - player->sprite->v;
    }

    // Vérifie le déplacement à droite
    if (touches->right) {
        player->sprite->DestR.x = player->sprite->DestR.x + player->sprite->v;
    }

    // Vérifie un saut
    if (touches->space && player->saut == false) {
        player->ground = player->sprite->DestR.y;
        player->timeSinceJumpStart = 0;
        player->saut = true;
    }

    // Vérifie la gravité lors d'un saut
    if (player->saut == true){
        player->sprite->DestR.y = player->ground - VITESSE_Y_SAUT * player->timeSinceJumpStart
                + 0.5 * GRAVITE * player->timeSinceJumpStart * player->timeSinceJumpStart;
        player->timeSinceJumpStart++;

        if (player->sprite->DestR.y > player->ground){
            player->sprite->DestR.y = player->ground;
            player->saut = false;
        }
    }
}

void handle_collision(world_t *world, player_t *player) {
    handle_collision_solidBlock(world, player);
}


void handle_collision_solidBlock(world_t *world, player_t *player) {
    for (int i = 0; i < NBR_DE_TEXTURES; i++) {
        sprite_t texture = world->blocks[i];

        // Collision en bas
        bool condCollision1 = texture.DestR.y >= player->sprite->DestR.y &&
                     texture.DestR.y + texture.DestR.h <= player->sprite->DestR.y;
        bool condCollision2 = texture.DestR.x >= player->sprite->DestR.x &&
                texture.DestR.x + world->blocks[i].DestR.w <= player->sprite->DestR.x;

        // Une collision entre le joueur et le block
        if (condCollision1 && condCollision2) {
            if (texture.DestR.y > player->sprite->DestR.y) { // Collision en bas du block
                // todo: Système de chute + arrêt du saut
                player->saut = false;
            }
        }

    }
}