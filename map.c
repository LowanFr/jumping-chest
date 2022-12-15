/**
 * @brief Exécutable des fonctions liées à la map?
 * @file map.c
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

int **allouer_tab_2D(int n, int m) {
    int **tab = calloc(sizeof(int *), n); // Créer le tableau initial

    for (int i = 0; i < n; i++) { // Créer le nombre de lignes souhaitées
        tab[i] = calloc(sizeof(int), m);
        for (int j = 0; j < m; j++) tab[i][j] = 0; // Créer le nombre de colonnes souhaitées
    }

    return tab;
}

void desallouer_tab_2D(int **tab, int n) {
    for (int i = 0; i < n; i++) free(tab[i]); // Libère toutes les lignes
    free(tab); // Libère le tableau
}

void taille_fichier(const char *nameFile, int *nbRows, int *nbColumns) {
    FILE *fichier = NULL;
    int caractere, countCol;
    fichier = fopen(nameFile, "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        caractere = 0;
        countCol = 0;
        *nbRows = 1;
        *nbColumns = 0;

        while (caractere != EOF) { // Le fichier n'est pas lu entièrement
            caractere = fgetc(fichier);
            if (caractere != ' ') {
                if (caractere == '\n') {
                    *nbRows = *nbRows + 1;
                    if (countCol > *nbColumns) *nbColumns = countCol;
                    countCol = 0;
                } else if (caractere != '\r') {
                    caractere = fgetc(fichier);
                    countCol++;
                }
            }

        }
        fclose(fichier);
    }
}

int **lire_fichier(const char *nameFile) {
    int colTerrain, rowTerrain;
    taille_fichier(nameFile, &rowTerrain, &colTerrain);

    FILE *fichier = NULL;
    int **tab = NULL;
    int column, row;
    fichier = fopen(nameFile, "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        tab = allouer_tab_2D(rowTerrain, colTerrain);

        char caractere[2] = " ";
        column = 0;
        row = 0;

        while (caractere[0] != EOF) { // Le fichier n'est pas lu entièrement
            caractere[0] = (char) fgetc(fichier);
            if (caractere[0] != ' ') {
                if (caractere[0] == '\n') {
                    row++;
                    column = 0;
                } else if (caractere[0] != '\r') {
                    if (row == rowTerrain || column == colTerrain) continue;
                    caractere[1] = (char) fgetc(fichier);
                    tab[row][column] = (int) strtol(caractere, NULL, 10);
                    column++;
                }
            }
        }
        fclose(fichier);
    }

    return tab;
}

void ecrire_fichier(const char *nameFile, int **tab, int nb_cols, int nb_rows) {
    FILE *fichier = NULL;
    fichier = fopen(nameFile, "w");

    for (int i = 0; i < nb_rows; i++) {
        for (int j = 0; j < nb_cols; ++j) {
            char textureIndex[10];
            sprintf(textureIndex, "%02d", tab[i][j]);
            fputs(textureIndex, fichier);
            if (j < nb_cols - 1) fputs(" ", fichier);
        }
        if (i < nb_rows - 1) fputs("\n", fichier);
    }
}
