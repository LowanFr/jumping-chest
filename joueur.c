#include "joueur.h"

/**
 * Ça déplace le joueur en fonction des touches appuyées
 *
 * @param touches le statut du clavier
 * @param DestR la destination du rectangle du joueur
 * @param joueur la structure du joueur
 */
void deplacement_joueur(etat_clavier_t *touches, joueur_t *joueur, sprite_t *sprite_joueur) {
    if(touches->left){
        sprite_joueur->x = sprite_joueur->x-VITESSE_X_MARCHE;
    }

    if(touches->right){
        sprite_joueur->x = sprite_joueur->x+VITESSE_X_MARCHE;
    }

    if(touches->space){
        if(joueur->saut == false){
            joueur->ground = sprite_joueur->y;
            joueur->tempsDepuisLeDebutDuSaut = 0;
            joueur->saut = true;
        }
    }

    if(joueur->saut == true){
        sprite_joueur->y = joueur->ground - VITESSE_Y_SAUT * joueur->tempsDepuisLeDebutDuSaut + 0.5 * GRAVITE * joueur->tempsDepuisLeDebutDuSaut * joueur->tempsDepuisLeDebutDuSaut;
        joueur->tempsDepuisLeDebutDuSaut++;
        if(sprite_joueur->y > joueur->ground){
            sprite_joueur->y = joueur->ground;
            joueur->saut = false;
        }
    }
}