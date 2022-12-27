/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"

void init_game(game_t *game) {
    // Initialisation des paramètres
    game->endDate = (char *) calloc(100, sizeof(char));
    game->pseudo = (char *) calloc(20, sizeof(char));
    game->level = (char *) calloc(10, sizeof(char));
    game->score = 0;
    game->nextLife = 100;
    game->enteringPseudo = false;
    game->leaderboardLength = 0;
    load_leaderboard(game);

    // Récupération de la date actuelle
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // Défini la date actuelle de lancement
    game->startDate = calloc(100, sizeof(char));
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

void load_leaderboard(game_t *game) {
    // Alloue la mémoire du TOP 5
    game->leaderboard = calloc(5, sizeof(char *));
    char *path = "../backups/leaderboard.txt";
    FILE *file = NULL;

    // Vérifie que le fichier existe
    file = fopen(path, "r");
    if (file == NULL) return;

    // Alloue la mémoire dans les tableaux en fonction du nombre de joueur
    int nbPlayers = getNbPlayers(path);
    char **lines = calloc(nbPlayers, sizeof(char *));
    int *scores = calloc(nbPlayers, sizeof(int));

    int size = 50;
    int index = 0;
    char *line = calloc(size, sizeof(char));

    // Parcours le fichier ligne par ligne
    while (fgets(line, size, file) != NULL) {
        lines[index] = calloc(size, sizeof(char));
        snprintf(lines[index], size, "%s", line);
        int len_result = (int) strlen(lines[index]);
        lines[index][len_result - 1] = '\0'; // enlève à chaque fois le caractère "\n"
        ++index;
    }
    fclose(file);

    char *string;
    for (int i = 0; i < index; ++i) {
        // Récupère le score à partir de la ligne
        sprintf(line, "%s", lines[i]);
        string = strtok(line, " ");
        string = strtok(NULL, string);
        scores[i] = (int) strtol(string, NULL, 10);
    }

    int scoreMax = scores[0];
    int indexMax = 0;

    // Parcours n fois (n ≤ 5) pour définir le TOP 5
    for (int i = 0; i < index && i < 5; ++i) {
        // Récupère le meilleur joueur
        for (int j = 0; j < index; ++j) {
            if (scores[j] > scoreMax) {
                scoreMax = scores[j];
                indexMax = j;
            }
        }

        // Sauvegarde le joueur
        game->leaderboard[i] = calloc(size, sizeof(char));
        snprintf(game->leaderboard[i], size, "%s", lines[indexMax]);
        game->leaderboardLength++;

        // Modifie le score pour qu'il ne puisse pas réapparaître
        scores[indexMax] = 0;
        scoreMax = 0;
    }

    // Libère la mémoire
    free(line);
    for (int j = 0; j < index; ++j) free(lines[j]);
    free(lines);
    free(scores);
}

void load_game(game_t *game) {
    FILE *fichier = NULL;
    char line[50];
    int size = 50;
    int step = 0;

    // Vérifie que le fichier existe
    fichier = fopen("../backups/game.txt", "r");
    if (fichier == NULL) return;

    // Parcours toutes les lignes
    while (fgets(line, size, fichier) != NULL) {
        line[strcspn(line, "\r\n")] = 0;

        // Sauvegarde la donnée correspondante
        switch (step) {
            case 1:
                game->score = (int) strtol(line, NULL, 10);
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

void clean_game(game_t *game) {
    free(game->pseudo);
    free(game->level);
    free(game->startDate);
    free(game->endDate);
    for (int i = 0; i < 10; ++i) free(game->leaderboard[i]);
    free(game->leaderboard);
}


int getNbPlayers(char *path) {
    FILE *file = NULL;
    int res = 0;

    // Vérifie que le fichier existe
    file = fopen(path, "r");
    if (file == NULL) return res;

    // Parcours le fichier ligne par ligne
    char *line = calloc(50, sizeof (char));
    while (fgets(line, 50, file) != NULL) res++;

    // Ferme le fichier
    fclose(file);

    return res;
}
