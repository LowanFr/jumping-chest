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
    // Alloue la mémoire de la matrice
    int **tab = calloc(sizeof(int *), n);

    // Alloue la mémoire de toutes les lignes et initialise la matrice
    for (int i = 0; i < n; i++) {
        tab[i] = calloc(sizeof(int), m);
        for (int j = 0; j < m; j++) tab[i][j] = 0;
    }

    return tab;
}

void desallouer_tab_2D(int **tab, int n) {
    for (int i = 0; i < n; i++) free(tab[i]);
    free(tab);
}

void taille_fichier(const char *nameFile, int *nbRows, int *nbColumns) {
    FILE *fichier = NULL;

    // Vérifie que le fichier s'ouvre
    fichier = fopen(nameFile, "r");
    if (fichier == NULL) return;

    int caractere = 0;
    int countCol = 0;
    *nbRows = 1;
    *nbColumns = 0;

    // Parcours le fichier
    while (caractere != EOF) {
        caractere = fgetc(fichier);

        // Séparateur
        if (caractere == ' ') continue;

        if (caractere == '\n') { // Ajoute une ligne à chaque \n
            *nbRows = *nbRows + 1;
            if (countCol > *nbColumns) *nbColumns = countCol;
            countCol = 0;
        } else if (caractere != '\r') { // Ajoute une colonne pour chaque caractère sur une ligne
            caractere = fgetc(fichier);
            countCol++;
        }
    }

    fclose(fichier);
}

int **lire_fichier(const char *nameFile) {
    int **tab = NULL;

    // Vérifie que le fichier s'ouvre
    FILE *fichier = NULL;
    fichier = fopen(nameFile, "r");
    if (fichier == NULL) return tab;

    // Récupère la taille du fichier et alloue la matrice
    int colTerrain, rowTerrain;
    taille_fichier(nameFile, &rowTerrain, &colTerrain);
    tab = allouer_tab_2D(rowTerrain, colTerrain);

    char caractere[2] = " ";
    int column = 0;
    int row = 0;

    // Parcours le fichier
    while (caractere[0] != EOF) {
        caractere[0] = (char) fgetc(fichier);
        if (caractere[0] == ' ') continue;

        if (caractere[0] == '\n') { // Nouvelle ligne
            row++;
            column = 0;
        } else if (caractere[0] != '\r') { // Nouvelle colonne
            // Vérifie les dépassements
            if (row == rowTerrain || column == colTerrain) continue;

            // Défini la valeur dans la matrice
            caractere[1] = (char) fgetc(fichier);
            tab[row][column] = (int) strtol(caractere, NULL, 10);
            column++;
        }
    }

    fclose(fichier);
    return tab;
}

void ecrire_fichier(const char *nameFile, int **tab, int nb_cols, int nb_rows) {
    // Vérifie que le fichier s'ouvre
    FILE *fichier = NULL;
    fichier = fopen(nameFile, "w");
    if (fichier == NULL) return;

    // Écris la matrice dans le fichier
    for (int i = 0; i < nb_rows; i++) {
        // Ajoute les colonnes
        for (int j = 0; j < nb_cols; ++j) {
            char textureIndex[10];
            sprintf(textureIndex, "%02d", tab[i][j]);
            fputs(textureIndex, fichier);
            if (j < nb_cols - 1) fputs(" ", fichier);
        }

        // Nouvelle ligne
        if (i < nb_rows - 1) fputs("\n", fichier);
    }

    fclose(fichier);
}
