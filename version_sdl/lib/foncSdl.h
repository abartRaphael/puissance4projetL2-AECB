#ifndef H_FONCSDL_
#define H_FONCSDL_

#include <SDL2/SDL.h>

#include "../lib/fonc2.h"


/**
 * \file foncSdl.h
 * \brief En-tête des fonctions SDL
 * \version 0.1
 * \date {22/03/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/


// ces fonctions et structures ne seront peut-être pas toutes utilisées

/** \struct images_s
 * \brief structure contenant des pointeurs sur toutes les textures d'images de pions
 */
typedef struct images_s {
	SDL_Texture* pionRougePlein;
	SDL_Texture* pionRougeCreux;
	SDL_Texture* pionJaunePlein;
	SDL_Texture* pionJauneCreux;
	SDL_Texture* pionJauneBloquant;
	SDL_Texture* pionRougeBloquant;
	SDL_Texture* pionRougeJauneBloquant;
	SDL_Texture* pionJauneRougeBloquant;
	SDL_Texture* caseVide;
} images_t;



/**
 * \fn int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height)
 * \brief initialise les systèmes de SDL, crée le pointeur sur fenêtre et le renderer
 * \param window pointeur sur pointeur de SDL_Window, va être rempli (à free avec SDL_DestroyRenderer() )
 * \param renderer pointeur sur pointeur de SDL_Renderer, va être rempli (à free avec SDL_DestroyWindow() )
 * \param width la largeur de la fenêtre
 * \param height la hauteur de la fenêtre
 * \return retourne 0 en cas de succès, -1 en cas d'échec
 */
int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height);



/**
 * \fn SDL_Texture* loadImage(char* path, SDL_Renderer* renderer)
 * \brief charge une image depuis un chemin donné, retourne une texture créée à partir de cette image
 * \param path chemin d'accès, relatif ou absolu, vers le fichier BITMAP UNIQUEMENT (.bmp) à ouvrir
 * \param renderer pointeur de SDL_Renderer, nécessaire pour créer une texture depuis une surface
 * \return retourne l'adresse d'une SDL_Texture dynamique créée à partir de cette image (à free avec SDL_DestroyTexture() ), ou NULL en cas d'échec
 */
SDL_Texture* loadImage(char* path, SDL_Renderer* renderer);



/**
 * \fn int setDrawColor(SDL_Renderer *renderer, SDL_Color color)
 * \brief change la couleur utilisée pour dessiner avec un SDL_Color
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param color couleur de type SDL_color {rouge, vert, bleu[, alpha]}
 * \return retourne 0 pour un succès, -1 pour une erreur
 */
int setDrawColor(SDL_Renderer *renderer, SDL_Color color);



void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y);



SDL_Surface *createSurfaceFromTexture(SDL_Texture* texture);



/**
 * \fn int initDamier( SDL_Rect* damier[LIGNES*COLONNES], SDL_Renderer* renderer, SDL_Color couleur, int largeurRectGrille, int offsetGrilleX, int offsetGrilleY )
 * \brief remplit un tableau de SDL_Rect avec des coordonnées, qui représentent les 42 cases d'une grille de puissance4
 * \param damier tableau 
 * \param renderer pointeur de SDL_Renderer, nécessaire à setDrawColor
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 * \return retourne 0 pour un succès
 */
int initDamier( SDL_Rect damier[LIGNES*COLONNES], SDL_Renderer* renderer, 
				int largeurRectGrille, int offsetGrilleX, int offsetGrilleY );



/**
 * \fn int initCoordonneesPions(SDL_Rect* coordonneesPions[LIGNES][COLONNES], int offsetGrilleX, int offsetGrilleY, int largeurPiece)
 * \brief remplit un tableau de SDL_Rect avec des coordonnées, qui représentent les emplacements des pièces de jeu, dans chaque cases d'une grille de puissance4
 * \param coordonneesPions matrice des coordonnées des pions 
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 * \return retourne 0 pour un succès
 */
int initCoordonneesPions(   SDL_Rect coordonneesPions[LIGNES][COLONNES], 
							int largeurRectGrille, int offsetGrilleX, int offsetGrilleY);



/**
 * \fn void afficherPions(t_pion grilleDeValeurs[LIGNES][COLONNES], SDL_Renderer* renderer)
 * \brief Affiche les pions à l'écran
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param grilleDeValeurs matrice contenant les pièces jouées (t_pion)
 * \param coordonneesPions matrice contenant les coordonnées où placer l'image de pièce
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions
 * \param arrierePlan couleur de l'arrière-plan de la fenêtre
 */
void afficherPions( SDL_Renderer* renderer, 
					t_pion grilleDeValeurs[LIGNES][COLONNES], 
					SDL_Rect coordonneesPions[LIGNES][COLONNES], 
					images_t* images, 
					SDL_Color arrierePlan);



/**
 * \fn int initStructTextures( SDL_Renderer* renderer, images_t* images, t_partie typeDePartie )
 * \brief crée (alloue) les images des pièces d'une partie normale et les affecte à une structure images_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions, à remplir
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int initStructTextures( SDL_Renderer* renderer, images_t* images, t_partie typeDePartie );



/**
 * \fn int getColonneClick( SDL_Rect damier[7], int largeurRectGrille, Sint32 x )
 * \brief 
 * \param damier tableau des coordonnées des rectangles de la grille
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param x position horizontale de la souris au moment du clic, par rapport à la fenêtre
 */
int getColonneClick( SDL_Rect damier[7], int largeurRectGrille, Sint32 x );



/**
 * \fn void afficherDamier( SDL_Renderer* renderer, SDL_Rect damier[42], SDL_Color couleur )
 * \brief dessine tous les rectangles contenu dans "damier", en "couleur", et l'affiche à l'écran
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param damier tableau des coordonnées des rectangles de la grille
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions
 * \param couleur couleur des rectangles de la grille à afficher
 */
void afficherDamier( SDL_Renderer* renderer, SDL_Rect damier[42], images_t* images, SDL_Color couleur );



/**
 * \fn int freeLesImages(images_t* images)
 * \brief free (désalloue) les images des pièces dans une structure images_t
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions, à désallouer
 */
void freeLesImages(images_t* images);



/**
 * \fn int dimensionGrilleDynamique( int largeurWindow, int hauteurWindow, int* largeurRectGrille, int* offsetGrilleX, int* offsetGrilleY )
 * \brief calcule les valeurs de largeurRectGrille, offsetGrilleX et offsetGrilleY, d'après les dimensions de la fênetre, pour bien afficher la grille de jeu en prenant la place nécessaire
 * \param largeurWindow largeur actuelle de la fenêtre
 * \param hauteurWindow hauteur actuelle de la fenêtre
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 */
void dimensionGrilleDynamique( int largeurWindow, int hauteurWindow, int* largeurRectGrille, int* offsetGrilleX, int* offsetGrilleY );




#endif /*H_FONCSDL_ */