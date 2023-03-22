#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/foncSdl.h"



/**
 * \file foncSdl.h
 * \brief Corps des fonctions SDL
 * \version 0.1
 * \date {22/03/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/



/**
 * \fn int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height)
 * \brief initialise les systèmes de SDL, crée le pointeur sur fenêtre et le renderer
 * \param window pointeur sur pointeur de SDL_Window, va être rempli (à free avec SDL_DestroyRenderer() )
 * \param renderer pointeur sur pointeur de SDL_Renderer, va être rempli (à free avec SDL_DestroyWindow() )
 * \param width la largeur de la fenêtre
 * \param height la hauteur de la fenêtre
 * \return retourne 0 en cas de succès, -1 en cas d'échec
 */
int init(SDL_Window* * window, SDL_Renderer* * renderer, int width, int height) {
	
	// Initialisation simple 
	if ( SDL_InitSubSystem(SDL_INIT_VIDEO) != 0 ) {
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return -1;
	} 

	if( SDL_CreateWindowAndRenderer(width, 
								height, 
								SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, 
								window, 
								renderer) != 0 )
	{
		fprintf(stderr, "Erreur à la création de la fenetre et du renderer : %s\n", SDL_GetError());
		return -1;
	}

	return 0;
}



/**
 * \fn SDL_Texture* loadImage(char* path, SDL_Renderer* renderer)
 * \brief charge une image depuis un chemin donné, retourne une texture créée à partir de cette image
 * \param path chemin d'accès, relatif ou absolu, vers le fichier BITMAP UNIQUEMENT (.bmp) à ouvrir
 * \param renderer pointeur de SDL_Renderer, nécessaire pour créer une texture depuis une surface
 * \return retourne l'adresse d'une SDL_Texture dynamique créée à partir de cette image (à free avec SDL_DestroyTexture() ), ou NULL en cas d'échec
 */
SDL_Texture* loadImage(char* path, SDL_Renderer* renderer) {

	SDL_Surface* tempSurface = NULL;
	SDL_Texture* tempTexture = NULL;
	
	tempSurface = SDL_LoadBMP(path);
	if(!tempSurface)
	{
		fprintf(stderr, "Erreur SDL_LoadBMP : %s\n", SDL_GetError());
		return NULL;
	}

	tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface); // On libère la surface, on n’en a plus besoin 

	if(!tempTexture)
	{
		fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
		return NULL;
	}

	return tempTexture;
}



/**
 * \fn int setDrawColor(SDL_Renderer *renderer, SDL_Color color)
 * \brief change la couleur utilisée pour dessiner avec un SDL_Color
 * \param renderer pointeur de SDL_Renderer, nécessaire à SDL_SetRenderDrawColor
 * \param color couleur de type SDL_color {rouge, vert, bleu[, alpha]}
 * \return retourne 0 pour un succès, -1 pour une erreur
 */
int setDrawColor(SDL_Renderer *renderer, SDL_Color color) {

	if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
		return -1;

	return 0;  
}



void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y) {
	
	Uint32 *pixels = surface->pixels; // Nos pixels sont sur 32 bits 
	Uint32 couleur = SDL_MapRGBA(surface->format, r, g, b, a);
	pixels[y * surface->w + x] = couleur;
}



/**
 * \fn SDL_Surface *createSurfaceFromTexture(SDL_Texture* texture)
 * \brief crée un SDL_Surface à partir d'un SDL_Texture du même format
 * \param texture texture à utiliser pour en fait une Surface, nécessaire
 * \return retourne un SDL_Surface pour un succès, NULL pour une erreur
 */
SDL_Surface *createSurfaceFromTexture(SDL_Texture* texture)
{
	Uint32 format_pixels;
	SDL_Surface* surface = NULL;
	void* pixels = NULL;
	int pitch, w, h;

	if( SDL_QueryTexture(texture, &format_pixels, NULL, &w, &h) != 0 )
	{
		fprintf(stderr, "SDL_QueryTexture: %s.\n", SDL_GetError());
		goto query_texture_fail;
	}

	if( SDL_LockTexture(texture, NULL, &pixels, &pitch) != 0 )
	{
		fprintf(stderr, "SDL_LockTexture: %s.\n", SDL_GetError());
		goto lock_texture_fail;
	}

	surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * sizeof(Uint32), 
												 format_pixels);
	if(NULL == surface)
		fprintf(stderr, "Erreur SDL_CreateRGBSurfaceWithFormatFrom : %s.\n", SDL_GetError());

	SDL_UnlockTexture(texture);
lock_texture_fail:
query_texture_fail:
	return surface;
}



/**
 * \fn int initDamier( SDL_Rect* damier[LIGNES*COLONNES], SDL_Renderer* renderer, SDL_Color couleur, int largeurRectGrille, int offsetGrilleX, int offsetGrilleY )
 * \brief remplit un tableau de SDL_Rect avec des coordonnées, qui représentent les 42 cases d'une grille de puissance4
 * \param damier tableau des coordonnées des rectangles de la grille
 * \param renderer pointeur de SDL_Renderer, nécessaire à setDrawColor
 * \param couleur couleur des rectangles de la grille à afficher
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 * \return retourne 0 pour un succès
 */
int initDamier( SDL_Rect damier[LIGNES*COLONNES], SDL_Renderer* renderer, SDL_Color couleur, 
				int largeurRectGrille, int offsetGrilleX, int offsetGrilleY ) {


	int hauteur=largeurRectGrille, // carré



	// couleur de la grille
	setDrawColor(renderer, couleur);


	for(int i=0, indice=0 ; i<LIGNES ; i++)
	{
		for(int j=0 ; j<COLONNES ; j++, indice++) 
		{
			//largeurRectGrille * le nombre de rectangles précédents
			//+ offsetGrille (décale l'ensemble de carrés par rapport au coin supérieur gauche de la fenêtre)
			// - i(ou j) (pour que les bordures des carrés se superposent)
			damier[indice].x = largeurRectGrille * j +offsetGrilleX - j;
			damier[indice].y = hauteur  * i +offsetGrilleY - i;
			damier[indice].w = largeurRectGrille;
			damier[indice].h = hauteur;

			//SDL_RenderDrawRect( renderer, &damier[indice] ); // dessine les carrés les uns après les autres
		}
	}

	// SDL_RenderDrawRects(renderer, damier, n); // autre méthode pour afficher plusieurs carrés

	return 0;
}



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
							int largeurRectGrille, int offsetGrilleX, int offsetGrilleY) {

	int espacementGrille = 1, // les rectangles font 1 pixel d'épaisseur (constante))
		offsetJetonsX = offsetGrilleX+espacementGrille, // décalage du point en haut à gauche de la grille à afficher, mais pour les pièces, sur l'axe horizontal
		offsetJetonsY = offsetGrilleY+espacementGrille, // décalage du point en haut à gauche de la grille à afficher, mais pour les pièces, sur l'axe vertical
		largeurPiece = largeurRectGrille-2, // -1 pour la bordure gauche, -1 pour la bordure droite
		hauteur = largeurPiece;


	//remplir matrice "slots" de rectangles ayant des coordonnées permettant de placer une texture de jeton facilement (les valeurs doivent correspondre à la grille de jeu)
	for(int i=0 ; i<6 ; i++) {
		for(int j=0 ; j<7 ; j++) {
		
			coordonneesPions[i][j].x = espacementGrille * j + largeurPiece * j + offsetJetonsX;
			coordonneesPions[i][j].y = espacementGrille * i + hauteur * i + offsetJetonsY;
			coordonneesPions[i][j].w = largeurPiece;
			coordonneesPions[i][j].h = hauteur;
		}
	}

	return 0;
}