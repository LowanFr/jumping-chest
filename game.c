/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"
#include <ctype.h>

void init_game(game_t *game) {
    // Initialisation des paramètres
    game->endDate = (char *) calloc(sizeof(char), 100);
    game->pseudo = (char *) calloc(sizeof(char), 50);
    game->level = (char *) malloc(sizeof(char) * 10);
    game->score = 0;
    game->enteringPseudo = false;
    game->nbPseudoScore = 0;
    load_leaderboard(game);
    
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

void load_leaderboard(game_t *game) {
    game->leaderboard = calloc(sizeof(char*), 10);
   
    FILE *fichier = NULL;
    char line[50];
    int size = 50;
    int step = 0;
    char** result = calloc(sizeof(char*), 10);
    int *scores = calloc(sizeof(int), 10);

    int i = 0;
    int len_result;
    int score_index = 0;
    int score;

    fichier = fopen("../backups/leaderboard.txt", "r"); // Ouvre en mode lecture
    if (fichier != NULL) { // Fichier introuvable
        // Parcours toutes les lignes
        while (fgets(line, size, fichier) != NULL) {
            
            result[i] = calloc(sizeof(char), 50);
            sprintf(result[i], "%s", line);
            len_result = strlen(result[i]);
            result[i][len_result - 1 ] = '\0';
            printf("%d\n", len_result);
            ++i;
        }
        fclose(fichier);
        len_result = i;

        int index_max = 0 ;
        int score_max = 0;
        
        char** score_e = calloc(sizeof(char), 10);
        char* score_c;

        for(int i = 0; i < len_result ; ++i){
            score_e[i] = calloc(sizeof(char), 50);
            strcpy(score_e[i], result[i]);
            score_c = strtok(result[i], " ");
            score_c = strtok(NULL, score_c);
            scores[i] = (int) strtol(score_c, NULL, 10);
            
        }

        score_max = scores[0];
        for(int j = 0; j < len_result ; ++j){
            for(int i = 0; i < len_result; ++i){
                if(scores[i] > score_max){
                    score_max = scores[i];
                    index_max = i;
                }
            }
        game->leaderboard[j] = score_e[index_max];
        game->nbPseudoScore++;
        scores[index_max] = 0;
        score_max = 0;
        }
    }
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
}

void clean_game(game_t *game) {
    free(game->pseudo);
    free(game->level);
    free(game->startDate);
    free(game->endDate);
    for(int i = 0; i < game->nbPseudoScore ; ++i){
        free(game->leaderboard[i]);
    }
    free(game->leaderboard);
}
