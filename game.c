/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"

void init_game(game_t *game) {
    // Initialisation des paramètres
    game->startDate = calloc(100, sizeof(char));
    game->endDate = calloc(100, sizeof(char));
    game->pseudo = calloc(20, sizeof(char));
    game->level = calloc(10, sizeof(char));
    game->score = 0;
    game->nextLife = 100;
    game->enteringPseudo = false;
    game->leaderboardLength = 0;
    load_leaderboard(game);

    // Récupération de la date actuelle
    struct tm now = getDate();

    // Défini la date actuelle de lancement et le niveau
    sprintf(game->startDate, "%d-%02d-%02d %02d:%02d:%02d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
            now.tm_hour, now.tm_min, now.tm_sec);
    sprintf(game->level, "classic");
}

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

    // Alloue la mémoire dans les tableaux en fonction du nombre de joueurs et crée le classement
    int nbPlayers = getNbPlayers(path);
    char **players = getPlayers(path, nbPlayers);
    int *scores = getScores(players, nbPlayers);
    setLeaderboard(game, players, scores, nbPlayers);

    // Libère la mémoire
    for (int j = 0; j < nbPlayers; ++j) free(players[j]);
    free(players);
    free(scores);
}

void load_game(game_t *game) {
    FILE *fichier = NULL;
    int size = LINE_SIZE;
    char *line = calloc(size, sizeof(char));
    int step = 0;

    // Vérifie que le fichier existe
    fichier = fopen("../backups/game.txt", "r");
    if (fichier == NULL) return;

    // Parcours toutes les lignes
    while (fgets(line, size, fichier) != NULL) {
        line[strcspn(line, "\r\n")] = 0;
        setGameData(game, line, step);
        step++;
    }

    free(line);
    fclose(fichier);
}

void setGameData(game_t *game, char *line, int step) {
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
}

void clean_game(game_t *game) {
    free(game->pseudo);
    free(game->level);
    free(game->startDate);
    free(game->endDate);
    for (int i = 0; i < 5; ++i) free(game->leaderboard[i]);
    free(game->leaderboard);
}


int getNbPlayers(char *path) {
    FILE *file = NULL;
    int res = 0;

    // Vérifie que le fichier existe
    file = fopen(path, "r");
    if (file == NULL) return res;

    // Parcours le fichier ligne par ligne
    int lineSize = LINE_SIZE;
    char line[lineSize];
    while (fgets(line, lineSize, file) != NULL) res++;

    // Ferme le fichier
    fclose(file);

    return res;
}

char **getPlayers(char *path, int nbPlayers) {
    FILE *file = NULL;

    // Vérifie que le fichier existe
    file = fopen(path, "r");
    if (file == NULL) return NULL;

    // Alloue la mémoire pour chaque joueur
    int lineSize = LINE_SIZE;
    char **lines = calloc(nbPlayers, sizeof(char *));
    char line[lineSize];
    int index = 0;

    // Parcours le fichier ligne par ligne
    while (fgets(line, lineSize, file) != NULL) {
        lines[index] = calloc(lineSize, sizeof(char));
        snprintf(lines[index], lineSize, "%s", line);
        lines[index++][strcspn(line, "\r\n")] = 0;
    }

    // Ferme le fichier
    fclose(file);
    return lines;
}

int *getScores(char **players, int nbPlayers) {
    char line[LINE_SIZE];
    int *scores = calloc(nbPlayers, sizeof(int));

    char *string;
    for (int i = 0; i < nbPlayers; ++i) {
        // Récupère le score à partir de la ligne
        sprintf(line, "%s", players[i]);
        string = strtok(line, " ");
        string = strtok(NULL, string);
        scores[i] = (int) strtol(string, NULL, 10);
    }

    return scores;
}

void setLeaderboard(game_t *game, char **players, int *scores, int nbPlayers) {
    int lineSize = LINE_SIZE;
    int scoreMax = scores[0];
    int indexMax = 0;

    // Parcours n fois (n ≤ 5) pour définir le TOP 5
    for (int i = 0; i < nbPlayers && i < 5; ++i) {
        // Récupère le meilleur joueur
        for (int j = 0; j < nbPlayers; ++j) {
            if (scores[j] > scoreMax) {
                scoreMax = scores[j];
                indexMax = j;
            }
        }

        // Sauvegarde le joueur
        game->leaderboard[i] = calloc(lineSize, sizeof(char));
        snprintf(game->leaderboard[i], lineSize, "%s", players[indexMax]);
        game->leaderboardLength++;

        // Modifie le score pour qu'il ne puisse pas réapparaître
        scores[indexMax] = 0;
        scoreMax = 0;
    }
}

struct tm getDate() {
    time_t date = time(NULL);
    return *localtime(&date);
}
