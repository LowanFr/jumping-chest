#ifndef __SDL2_LIGHT__H__
#define __SDL2_LIGHT__H__

#include <SDL.h>

/**
 * \brief La fonction nettoie le renderer et la fenêtre du jeu en mémoire
 * \param renderer le renderer à nettoyer
 * \param window la fenêtre à nettoyer
*/
void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);

/**
 * \brief La fonction charge une image  et renvoie la texture correspondante
 * \param path est le chemin du fichier image. Le fichier doit être obligatoirement du BMP.
 * \param renderer le renderer
 * \return la surface SDL contenant l'image. Elle renvoie NULL si le chargement a échoué
 * (ex. le fichier path n'existe pas)
*/
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);

/**
 * \brief La fonction initialise la SDL.
 * Elle crée la fenêtre du jeu ainsi que le renderer
 *  \param window la fenêtre du jeu
 *  \param renderer le renderer
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 * \return -1 en cas d'erreur, 0 sinon
*/
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
 * \brief La fonction nettoie une texture en mémoire
 * \param texture la texture à nettoyer
*/
void clean_texture(SDL_Texture *texture);

/**
 * \brief La fonction permet d'appliquer une texture sur le renderer à une position donnée. La hauteur et la largeur est la même que celle de la texture.
 * \param texture  la texture que l'on va appliquer
 * \param renderer le renderer qui va recevoir la texture
 * \param x l'abscisse sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
 * \param y l'ordonnée sur le renderer de l'endroit où est appliquée texture (point en haut à gauche de la surface)
*/
void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y);

/**
 * \brief La fonction vide le contenu graphique du renderer lié à l'écran de jeu
 * \param renderer le renderer de l'écran
*/
void clear_renderer(SDL_Renderer *renderer);

/**
 * \brief La fonction met à jour l'écran avec le contenu du renderer
 * \param renderer le renderer de l'écran
*/
void update_screen(SDL_Renderer *renderer);

/**
 * \brief La fonction met le programme en pause pendant un laps de temps
 * \param time ce laps de temps en milliseconde
*/
void pause(int time);

#endif
