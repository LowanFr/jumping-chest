//
// Created by Esteban Douillet on 19/10/2022.
//

#include "fonctions_fichiers.h"
#include <stdlib.h>
#include <stdio.h>

char** allouer_tab_2D(int n, int m) {
    char** tab = malloc(sizeof(char) * n); // Créer le tableau initial

    for (int i = 0; i < n; i++) { // Créer le nombre de lignes souhaitées
        tab[i] =  malloc(sizeof(char) * m);

        for (int j = 0; j < m; j++) { // Créer le nombre de colonnes souhaitées
            tab[i][j] = ' ';
        }
    }

    return tab;
}

void desallouer_tab_2D(char** tab, int n) {
    for (int i = 0; i < n; i++) { // Libère toutes les lignes
        free(tab[i]);
    }
    free(tab); // Libère le tableau
}

void afficher_tab_2D(char** tab, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", tab[i][j]); // Affichage chaque colonne de chaque ligne du tableau
        }
        printf("\n");
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol) {
    FILE* fichier = NULL;
    int caractere, countCol;
    fichier = fopen(nomFichier, "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        caractere= 0;
        countCol = 0;
        *nbLig = 1;
        *nbCol = 0;

        while (caractere != EOF) { // Le fichier n'est pas lu entièrement
            caractere = fgetc(fichier);
            if (caractere == '\n') {
                *nbLig = *nbLig + 1;
                if (countCol > *nbCol) {
                    *nbCol = countCol;
                }
                countCol = 0;
            } else if (caractere != '\r') {
                countCol++;
            }
        }
        fclose(fichier);
    }
}

char** lire_fichier(const char* nomFichier) {
    int colTerrain, rowTerrain;
    taille_fichier("terrain.txt", &rowTerrain, &colTerrain);

    FILE* fichier = NULL;
    char** tab = NULL;
    int caractere, column, row;
    fichier = fopen(nomFichier, "r"); // Ouvre en mode lecture

    if (fichier != NULL) { // Fichier introuvable
        tab = allouer_tab_2D(rowTerrain, colTerrain);
        caractere = 0;
        column = 0;
        row = 0;

        while (caractere != EOF) { // Le fichier n'est pas lu entièrement
            caractere = fgetc(fichier);
            if (caractere == '\n') {
                row++;
                column = 0;
            } else if (caractere != '\r') {
                tab[row][column] = caractere;
                column++;
            }
        }
        fclose(fichier);
    }

    return tab;
}