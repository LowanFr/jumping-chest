#include "joueur.h"

void init_joueur(joueur_t *joueur){
    joueur->saut = false;
    joueur->tempsDepuisLeDebutDuSaut = 0;
}
/**
 * Ça déplace le joueur en fonction des touches appuyées
 *
 * @param touches le statut du clavier
 * @param DestR la destination du rectangle du joueur
 * @param joueur la structure du joueur
 */
void deplacement_joueur(etat_clavier_t *touches, joueur_t *joueur, sprite_t *sprite_joueur) {
    if(touches->left){
        sprite_joueur->DestR.x = sprite_joueur->DestR.x-sprite_joueur->v;
        
    }
    
    if(touches->right){
        sprite_joueur->DestR.x = sprite_joueur->DestR.x+sprite_joueur->v;

    }

    if(touches->space){
        if(joueur->saut == false){
            joueur->ground = sprite_joueur->DestR.y;
            joueur->tempsDepuisLeDebutDuSaut = 0;
            joueur->saut = true;
        }
    }

    if(joueur->saut == true){
        sprite_joueur->DestR.y = joueur->ground - VITESSE_Y_SAUT * joueur->tempsDepuisLeDebutDuSaut + 0.5 * GRAVITE * joueur->tempsDepuisLeDebutDuSaut * joueur->tempsDepuisLeDebutDuSaut;
        joueur->tempsDepuisLeDebutDuSaut++;
        if(sprite_joueur->DestR.y > joueur->ground){
            sprite_joueur->DestR.y = joueur->ground;
            joueur->saut = false;
        }
    }
}