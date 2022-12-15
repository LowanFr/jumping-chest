#ifndef MAP_H
#define MAP_H

/**
 * @brief Header des fonctions liées à la map.
 * @file map.h
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 30 Novembre 2022
 */

/**
 * @brief Alloue un tableau de caractères de taille n × m.
 * @param n La largeur
 * @param m La longueur
 * @return Le tableau alloué
 */
int **allouer_tab_2D(int n, int m);

/**
 * @brief Libère un tableau à deux dimensions, de n lignes.
 * @param tab Le tableau à deux dimensions
 * @param n Le nombre de lignes
 */
void desallouer_tab_2D(int **tab, int n);

/**
 * @brief Affiche le contenu d’un tableau de caractères de taille n × m.
 * @param tab Le tableau de caractères
 * @param n La largeur du tableau
 * @param m La hauteur du tableau
 */
void afficher_tab_2D(int **tab, int n, int m);

/**
 * @brief Compte le nombre max de ligne / colonne.
 * @param nameFile Le nom du fichier
 * @param nbRows Le nombre de ligne
 * @param nbColumns Le nombre de colonne
 */
void taille_fichier(const char *nameFile, int *nbRows, int *nbColumns);

/**
 * @brief Lis un fichier.
 * @param nameFile Le nom du fichier
 * @return Un tableau qui contient les caractères du fichier
 */
int **lire_fichier(const char *nameFile);

/**
 * Écris une matrice d'entier dans un fichier
 * @param nameFile Le chemin vers le fichier
 * @param tab La matrice d'entier
 * @param nb_cols Le nombre de colonne
 * @param nb_rows Le nombre de ligne
 */
void ecrire_fichier(const char *nameFile, int **tab, int nb_cols, int nb_rows);

#endif
