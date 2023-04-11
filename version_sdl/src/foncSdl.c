#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "../lib/foncSdl.h"



/**
 * \file foncSdl.c
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
		fprintf(stderr, "Failed to load image at %s: %s\n", path, SDL_GetError());
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
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 * \return retourne 0 pour un succès
 */
int initDamier( SDL_Rect damier[LIGNES*COLONNES], SDL_Renderer* renderer, 
				int largeurRectGrille, int offsetGrilleX, int offsetGrilleY ) {


	int hauteur=largeurRectGrille; // carré


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

			SDL_RenderDrawRect( renderer, &damier[indice] ); // dessine les carrés les uns après les autres
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



/**
 * \fn void afficherPions(t_pion grilleDeValeurs[LIGNES][COLONNES], SDL_Renderer* renderer)
 * \brief Affiche les pions à l'écran
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param grilleDeValeurs matrice contenant les pièces jouées (t_pion)
 * \param coordonneesPions matrice contenant les coordonnées où placer l'image de pièce
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions
 * \param couleurDamier couleur de la grille, pour représenter des bordures
 */
void afficherPions( SDL_Renderer* renderer, 
					t_pion grilleDeValeurs[LIGNES][COLONNES], 
					SDL_Rect coordonneesPions[LIGNES][COLONNES], 
					images_pieces_t* images, 
					SDL_Color couleurDamier) {


	int err;

	for(int i=0 ; i<LIGNES ; i++) {
		for(int j=0 ; j<COLONNES ; j++) {
				
			switch (grilleDeValeurs[i][j].couleur ) 
			{
				case rouge:

					switch( grilleDeValeurs[i][j].type ) {
						case pleine:
							//remplir la case par la texture du pion de bonne couleur
							err = SDL_RenderCopy(renderer, images->pionRougePlein, NULL, &coordonneesPions[i][j]); 
							break;
						case creuse:
							err = SDL_RenderCopy(renderer, images->pionRougeCreux, NULL, &coordonneesPions[i][j]); 
							break;
						case bloquante:
							err = SDL_RenderCopy(renderer, images->pionRougeBloquant, NULL, &coordonneesPions[i][j]); 
							break;
						case no_type:
						default:
							break;
					}
					break;

				case jaune:

					switch( grilleDeValeurs[i][j].type ) {
						case pleine:
							//remplir la case par la texture du pion de bonne couleur
							err = SDL_RenderCopy(renderer, images->pionJaunePlein, NULL, &coordonneesPions[i][j]); 
							break;
						case creuse:
							err = SDL_RenderCopy(renderer, images->pionJauneCreux, NULL, &coordonneesPions[i][j]); 
							break;
						case bloquante:
							err = SDL_RenderCopy(renderer, images->pionJauneBloquant, NULL, &coordonneesPions[i][j]); 
							break;
						case no_type:
						default:
							break;
					}
					break;

				case rougeJaune:

					//case bloquante:
					err = SDL_RenderCopy(renderer, images->pionRougeJauneBloquant, NULL, &coordonneesPions[i][j]); 
					break;

				case jauneRouge:

					//case bloquante:
					err = SDL_RenderCopy(renderer, images->pionJauneRougeBloquant, NULL, &coordonneesPions[i][j]); 
					break;

				//case vide:
				//default:
					
			}

			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherPions : %s\n", SDL_GetError());
			}

		}
	}
}



/**
 * \fn int initStructTexturesPieces( SDL_Renderer* renderer, images_pieces_t* images, t_partie typeDePartie )
 * \brief crée (alloue) les images des pièces d'une partie normale et les affecte à une structure images_pieces_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions, à remplir
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int initStructTexturesPieces( SDL_Renderer* renderer, images_pieces_t* images, affichage_t typeDePartie ) {
	/** 
	 * Les textures ne sont pas faites pour une modification pixels par pixels. 
	 * Elles ont l’avantage d’êtres affichables rapidement, 
	 * de pouvoir être redimensionnée à la volée et copiée rapidement
	 */
	
	// autre solution -> IMG_Load();

	// charger les images de pièces pleines (rouge et jaune)
	images->pionRougePlein = loadImage("img/imagePieces/pionRouge.bmp",renderer);
	images->pionJaunePlein = loadImage("img/imagePieces/pionJaune.bmp",renderer);
	images->caseVide = loadImage("img/imagePieces/caseVide.bmp",renderer);

	if( typeDePartie == modeCreux ) {
		images->pionRougeCreux = loadImage("img/imagePieces/pieceRougeCreuse.bmp",renderer);
		images->pionJauneCreux = loadImage("img/imagePieces/pieceJauneCreuse.bmp",renderer);
		images->pionRougeBloquant = loadImage("img/imagePieces/pionRougeBloquante.bmp",renderer);
		images->pionJauneBloquant = loadImage("img/imagePieces/pionJauneBloquante.bmp",renderer);
		images->pionRougeJauneBloquant = loadImage("img/imagePieces/pionRougeDouble.bmp",renderer);
		images->pionJauneRougeBloquant = loadImage("img/imagePieces/pionJauneDouble.bmp",renderer);
	}
		
	return 0;
}



/**
 * \fn int freeLesImagesPieces(images_pieces_t* images)
 * \brief free (désalloue) les images des pièces dans une structure images_pieces_t
 * \param images structure contenant des pointeurs sur toutes les textures d'images de pions, à désallouer
 */
void freeLesImagesPieces(images_pieces_t* images) {

	if( images->pionRougePlein != NULL )
		SDL_DestroyTexture( images->pionRougePlein );
	if( images->pionRougeCreux != NULL)
		SDL_DestroyTexture( images->pionRougeCreux );
	if( images->pionJaunePlein != NULL)
		SDL_DestroyTexture( images->pionJaunePlein );
	if( images->pionJauneCreux != NULL)
		SDL_DestroyTexture( images->pionJauneCreux );
	if( images->pionJauneBloquant != NULL)
		SDL_DestroyTexture( images->pionJauneBloquant );
	if( images->pionRougeBloquant != NULL)
		SDL_DestroyTexture( images->pionRougeBloquant );
	if( images->pionRougeJauneBloquant != NULL)
		SDL_DestroyTexture( images->pionRougeJauneBloquant );
	if( images->pionJauneRougeBloquant != NULL)
		SDL_DestroyTexture( images->pionJauneRougeBloquant );
}



/**
 * \fn int getColonneClick( SDL_Rect damier[7], int largeurRectGrille, Sint32 x )
 * \brief 
 * \param damier tableau des coordonnées des rectangles de la grille
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param x position horizontale de la souris au moment du clic, par rapport à la fenêtre
 */
int getColonneClick( SDL_Rect damier[7], int largeurRectGrille, Sint32 x ) {
	// TODO fonction qui déduit dans quelle colonne le joueur a cliqué

	if( x < damier[0].x
	 || (damier[6].x + largeurRectGrille ) < x ) {
		// hors de la grille
		return -1;
	}


	for( int i=1 ; i<7 ; i++ ) {

		if( x <= damier[i].x ) {
			// colonne i
			return i;
		}
	}

	//if( x <= (damier[6].x + largeurRectGrille ) ) {
		// colonne 7
		// par élimination, à partir d'ici, ça ne peut être que la colonne 7
		return 7;
	//}
}



/**
 * \fn void afficherDamier( SDL_Renderer* renderer, SDL_Rect damier[42], SDL_Color couleur )
 * \brief dessine tous les rectangles contenu dans "damier", en "couleur", et l'affiche à l'écran
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param damier tableau des coordonnées des rectangles de la grille
 * \param couleur couleur des rectangles de la grille à afficher
 */
void afficherDamier( SDL_Renderer* renderer, SDL_Rect damier[42], images_pieces_t* images, SDL_Color couleur ) {

	setDrawColor(renderer, couleur);

	if( SDL_RenderDrawRects( renderer, damier, 42 ) == -1 ) {
		fprintf(stderr, "Erreur SDL_RenderDrawRects : %s\n", SDL_GetError());
	}


	for(int i=0 ; i<42 ; i++) {
		// remplir la case par un rectangle de la même couleur que la grille
		setDrawColor(renderer, couleur);
		SDL_RenderFillRect(renderer, &damier[i]);

		// puis placer un rond blanc, pour représenter un trou
		SDL_RenderCopy(renderer, images->caseVide, NULL, &damier[i]); 
	}
}



/**
 * \fn int dimensionGrilleDynamique( int largeurWindow, int hauteurWindow, int* largeurRectGrille, int* offsetGrilleX, int* offsetGrilleY )
 * \brief calcule les valeurs de largeurRectGrille, offsetGrilleX et offsetGrilleY, d'après les dimensions de la fênetre, pour bien afficher la grille de jeu en prenant la place nécessaire
 * \param largeurWindow largeur actuelle de la fenêtre
 * \param hauteurWindow hauteur actuelle de la fenêtre
 * \param largeurRectGrille largeur des rectangles (carrés) qui composent la grille à afficher
 * \param offsetGrilleX décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal
 * \param offsetGrilleY décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical
 */
void dimensionGrilleDynamique( int largeurWindow, int hauteurWindow, int* largeurRectGrille, int* offsetGrilleX, int* offsetGrilleY ) 
{
	int hauteurGrille,largeurGrille, diff;

	if (largeurWindow > hauteurWindow)
	{
		(*largeurRectGrille) = (hauteurWindow) / 6 + 0.5 ;
		largeurGrille = (*largeurRectGrille) * 7 ;
		diff = largeurWindow - largeurGrille;
		(*offsetGrilleX) = diff / 2;
		(*offsetGrilleY) = 0;
	} 
	else if (largeurWindow < hauteurWindow)
	{
		(*largeurRectGrille) = (largeurWindow) / 7 + 0.5;
		hauteurGrille = (*largeurRectGrille) * 6;
		diff = hauteurWindow - hauteurGrille;
		(*offsetGrilleX) = 0;
		(*offsetGrilleY) = diff / 2;
	} 
	else {
		(*largeurRectGrille) = (largeurWindow) / 7 + 0.5 ;
		hauteurGrille = (*largeurRectGrille) * 6;
		diff = hauteurWindow - hauteurGrille;
		(*offsetGrilleX) = 0;
		(*offsetGrilleY) = diff / 2;

	}
}