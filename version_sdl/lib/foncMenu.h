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



typedef enum {principal=1, regles, mode} menu_t;



/** \struct images_menu_s
 * \brief structure contenant des pointeurs sur toutes les textures d'images pour les menus
 */
typedef struct images_menus_s {
	SDL_Texture* bouton_back;
	SDL_Texture* bouton_contre_joueur;
	SDL_Texture* bouton_contre_ordinateur;
	SDL_Texture* bouton_jouer;
	SDL_Texture* bouton_quitter;
	SDL_Texture* bouton_regles;
	SDL_Texture* regles;
	SDL_Texture* sound_off;
	SDL_Texture* sound_on;
	SDL_Texture* tache_bleue;
} images_menus_t;



/**
 * \fn int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* images )
 * \brief crée (alloue) les images des menus et les affecte à une structure images_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param images structure contenant des pointeurs sur toutes les textures d'images des menus, à remplir
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* images );



/**
 * \fn int freeLesImagesMenu(images_menus_t* images)
 * \brief free (désalloue) les images des menus dans une structure images_menus_t
 * \param images structure contenant des pointeurs sur toutes les textures d'images des menus, à désallouer
 */
void freeLesImagesMenu(images_menus_t* images);



#endif /*H_FONCSDL_ */