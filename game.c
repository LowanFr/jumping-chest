/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"

void init_game(game_t *game) {
    // Initialisation des paramètres
    game->endDate = (char *) malloc(sizeof(char) * 100);
    game->pseudo = (char *) malloc(sizeof(char) * 50);
    game->level = (char *) malloc(sizeof(char) * 10);
    game->score = 0;

    // Récupération de la date actuelle
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // Défini la date actuelle de lancement
    game->startDate = malloc(sizeof(char) * 100);
    sprintf(game->startDate, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec);

    // Défini le niveau
    sprintf(game->level, "classic");
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

void load_game(game_t *game) {
    FILE *fichier = NULL;
    char line[50];
    int size = 50;
    int step = 0;
    fichier = fopen("../backups/game.txt", "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        // Parcours toutes les lignes
        while (fgets(line, size, fichier) != NULL) {
            line[strcspn(line, "\r\n")] = 0;

            switch (step) {
                case 1:
                    game->score = atoi(line);
                    break;
                case 2:
                    sprintf(game->pseudo, "%s", line);
                    break;
                case 3:
                    sprintf(game->startDate, "%s", line);
                    break;
                case 4:
                    sprintf(game->endDate, "%s", line);
                    break;
                default:
                    if (strcmp(game->level, line) != 0) sprintf(game->level, "%s", line);
                    break;
            }
            step++;
        }

        fclose(fichier);
    }
}

void clean_game(game_t *game) {
    free(game->pseudo);
    free(game->level);
    free(game->startDate);
    free(game->endDate);
}
