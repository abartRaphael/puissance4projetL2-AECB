#ifndef H_FONCMENU_
#define H_FONCMENU_

#include <SDL2/SDL.h>

#include "../lib/fonc2.h"


/**
 * \file foncMenu.h
 * \brief En-tête des fonctions des menus
 * \version 0.1
 * \date {11/04/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/



//typedef enum {principal=1, regles, mode, fin} menu_t;



/** \struct images_menu_s
 * \brief structure contenant des pointeurs sur toutes les textures d'images pour les menus
 */
typedef struct images_menus_s {
	SDL_Texture* bouton_back;
	SDL_Texture* bouton_contre_joueur;
	SDL_Texture* bouton_contre_ordinateur;
	SDL_Texture* bouton_jouer;
	SDL_Texture* bouton_mode_creux;
	SDL_Texture* bouton_mode_normal;
	SDL_Texture* bouton_quitter;
	SDL_Texture* bouton_regles;
    SDL_Texture* bouton_rejouer;
	SDL_Texture* regles;
	SDL_Texture* sound_off;
	SDL_Texture* sound_on;
	SDL_Texture* tache_bleue;
} images_menus_t;



/** \struct rect_menu_s
 * \brief structure contenant les rectangles où placer les images pour les menus
 */
typedef struct rect_menus_s {
	SDL_Rect rect_bouton_back;
	SDL_Rect rect_bouton_contre_joueur;
	SDL_Rect rect_bouton_contre_ordinateur;
	SDL_Rect rect_bouton_jouer;
	SDL_Rect rect_bouton_mode_creux;
	SDL_Rect rect_bouton_mode_normal;
	SDL_Rect rect_bouton_quitter;
	SDL_Rect rect_bouton_regles;
    SDL_Rect rect_bouton_rejouer;
    SDL_Rect rect_sound;
} rect_menus_t;



/**
 * \fn int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus )
 * \brief crée (alloue) les images des menus et les affecte à une structure images_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus, à remplir
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus );



/**
 * \fn int freeLesImagesMenu(images_menus_t* imagesMenus)
 * \brief free (désalloue) les images des menus dans une structure images_menus_t
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus, à désallouer
 */
void freeLesImagesMenu(images_menus_t* imagesMenus);



/**
 * \fn int initStructRectMenu( SDL_Renderer* renderer, rect_menus_t* rectMenus, int largeurWindow, int hauteurWindow ) {
 * \brief crée les images des menus et les affecte à une structure images_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus, à remplir
 * \param largeurWindow largeur actuelle de la fenêtre
 * \param hauteurWindow hauteur actuelle de la fenêtre
 */
void initStructRectMenu( SDL_Renderer* renderer, rect_menus_t* rectMenus, int largeurWindow, int hauteurWindow );



/**
 * \fn int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t menu_actuel )
 * \brief affiche le menu à l'écran, en fonction de menu_actuel
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus
 * \param menu_actuel type enum représentant le menu à afficher
 */
int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t* menu_actuel );



int gererMenus( SDL_Window* pWindow, SDL_Renderer* renderer, images_menus_t* imagesMenus, affichage_t* actuel, Mix_Music* musique );



Mix_Music* loadMusique(const char* path);



#endif /*H_FONCSDL_ */
