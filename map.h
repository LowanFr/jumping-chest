#ifndef MAP_H
#define MAP_H

/**
 * @brief Header des fonctions liées à la map
 * @file map.h
 * @authors SCHNEIDER Paul, DOUILLET Esteban
 * @date 28 Novembre 2022
 */

/**
 * @briefAllouer un tableau de caractères de taille n × m
 * @param n Largeur
 * @param m Longueur
 * @return Initialiser ce tableau avec le caractère espace
 */
int **allouer_tab_2D(int n, int m);

/**
 * Libérer un tableau à deux dimensions, de n lignes
 * @param tab Le tableau à deux dimensions
 * @param n Nombre de lignes
 */
void desallouer_tab_2D(int **tab, int n);

/**
 * Afficher le contenu d’un tableau de caractères de taille n × m
 * @param tab Tableau de caractères
 * @param n Largeur
 * @param m Longueur
 */
void afficher_tab_2D(int **tab, int n, int m);

/**
 * Compter le nombre max de ligne / colonne
 * @param nomFichier Nom du fichier
 * @param nbLig Nombre de ligne
 * @param nbCol Nombre de colonne
 */
void taille_fichier(const char *nomFichier, int *nbLig, int *nbCol);

/**
 * Lire un fichier
 * @param nomFichier Le nom du fichier
 * @return Tableau qui contient les caractères du fichier
 */
int **lire_fichier(const char *nomFichier);

#endif
