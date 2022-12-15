/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"

void init_game(game_t *game) {
    // Initialisation des paramètres
    game->endDate = malloc(sizeof(char) * 100);
    game->pseudo = malloc(sizeof(char) * 50);
    game->score = 0;
    game->level = "classic";

    // Récupération de la date actuelle
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // Défini la date actuelle de lancement
    game->startDate = malloc(sizeof(char) * 100);
    sprintf(game->startDate, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/**
 * Sauvegarde l'état de la partie
 * @param folder  Le dossier de sauvegarde
 */
void save_game(game_t *game, char folder[100]) {
    // Défini le chemin vers le fichier
    char gameFileName[100];
    sprintf(gameFileName, "%s/game.txt", folder);

    // Ouvre le fichier en mode écriture
    FILE *gameFile = NULL;
    gameFile = fopen(gameFileName, "w");

    // Défini le contenu du fichier de sauvegarde
    char gameFileContent[300];
    sprintf(gameFileContent, "%s\n%i\n%s\n%s\n%s", game->level, game->score, game->pseudo, game->startDate,
            game->endDate);

    // Ajoute le contenu du fichier qui est fermé après
    fputs(gameFileContent, gameFile);
    fclose(gameFile);
}

void clean_game(game_t *game) {
    free(game->pseudo);
    free(game->startDate);
    free(game->endDate);
}
