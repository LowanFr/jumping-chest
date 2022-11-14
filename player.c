/**
 * @file player.c
 * @brief Exécutable concernant le module : player
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 14 Novembre 2022
 */
#include "player.h"

void init_player(player_t *joueur){
    joueur->saut = false;
    joueur->timeSinceJumpStart = 0;
}

void player_movement(keyboard_status_t *touches, player_t *player, sprite_t *sprite_player) {
    // Vérifie le déplacement à gauche
    if (touches->left) {
        sprite_player->DestR.x = sprite_player->DestR.x - sprite_player->v;
    }

    // Vérifie le déplacement à droite
    if (touches->right) {
        sprite_player->DestR.x = sprite_player->DestR.x + sprite_player->v;
    }

    // Vérifie un saut
    if (touches->space && player->saut == false) {
        player->ground = sprite_player->DestR.y;
        player->timeSinceJumpStart = 0;
        player->saut = true;
    }

    // Vérifie la gravité lors d'un saut
    if (player->saut == true){
        sprite_player->DestR.y = player->ground - VITESSE_Y_SAUT * player->timeSinceJumpStart
                + 0.5 * GRAVITE * player->timeSinceJumpStart * player->timeSinceJumpStart;
        player->timeSinceJumpStart++;

        if (sprite_player->DestR.y > player->ground){
            sprite_player->DestR.y = player->ground;
            player->saut = false;
        }
    }
}