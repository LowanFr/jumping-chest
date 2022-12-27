/**
 * @file game.c
 * @brief Exécutable concernant le module : game
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 7 Décembre 2022
 */
#include "game.h"

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
    char** result = calloc(sizeof(char*), 10); //copie du txt dans un tableau
    int *scores = calloc(sizeof(int), 10); //copie des scores pour le tri

    int i = 0;
    int len_result;

    fichier = fopen("../backups/leaderboard.txt", "r"); // Ouvre en mode lecture
    if (fichier != NULL) { // Fichier introuvable
        // Parcours toutes les lignes
        while (fgets(line, size, fichier) != NULL) {
            
            result[i] = calloc(sizeof(char), 50);
            snprintf(result[i], 50, "%s", line);
            len_result = strlen(result[i]);
            result[i][len_result - 1 ] = '\0'; //enleve à chaque fois le caractère \n 
            ++i;
        }

        fclose(fichier);
        len_result = i;

        int index_max = 0 ;

        
        char** score_e = calloc(sizeof(char*), 10); // Copie de result pour effectuer le tri
        char* score_c;

        for(int index = 0; index < len_result ; ++index){
            score_e[index] = calloc(sizeof(char), 50);
            snprintf(score_e[index], 50, "%s", result[index]);

            score_c = strtok(result[index], " ");
            score_c = strtok(NULL, score_c);
            scores[index] = (int) strtol(score_c, NULL, 10);
        }

        int score_max = scores[0];

        for(int j = 0; j < len_result ; ++j){
            for(int index = 0; index < len_result; ++index){
                if(scores[index] > score_max){
                    score_max = scores[index];
                    index_max = index;
                }
            }

            game->leaderboard[j] = calloc(sizeof(char), 50);


            snprintf(game->leaderboard[j], 50, "%s", score_e[index_max]);

            game->nbPseudoScore++;
            scores[index_max] = 0;
            score_max = 0;
        }
        for(int index = 0; index < len_result; ++index){
            free(score_e[index]);
            free(result[index]);
        }
        free(score_e);
        free(result);
        free(scores);
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
    for (int i = 0; i < 10; ++i)
        free(game->leaderboard[i]);

    free(game->leaderboard);
}
