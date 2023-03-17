#include <stdio.h>
#include "../lib/fonc2.h"
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


/**
 * \file mainSdl.c
 * \brief fichier main de la version SDL du projet Puissance4++
 * \version 0.1
 * \date {17/03/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/



// fonctions SDL

// Cette structure permet de représenter un carré par sa couleur et un SDL_Rect. 
struct carre {
   SDL_Rect rect;
   Uint32 couleur;
};



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
 * \fn int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
 * \brief remplit la fenêtre avec une couleur de type SDL_Color
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param color couleur de type SDL_color {rouge, vert, bleu[, alpha]}
 * \return retourne 0 pour un succès, -1 pour une erreur
 */
int setWindowColor(SDL_Renderer *renderer, SDL_Color color) {

	if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
		return -1;
	if(SDL_RenderClear(renderer) < 0)
		return -1;
	return 0;  
}



void setPixel(SDL_Surface *surface, Uint8 r, Uint8 g, Uint8 b, Uint8 a, size_t x, size_t y) {
    
	Uint32 *pixels = surface->pixels; // Nos pixels sont sur 32 bits 
    Uint32 couleur = SDL_MapRGBA(surface->format, r, g, b, a);
    pixels[y * surface->w + x] = couleur;
}



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



int main(int argc, char** argv)
{
    // VARIABLES SDL
	//Le pointeur vers la fenetre
	SDL_Window* pWindow=NULL;
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer=NULL;
	SDL_Texture *texture=NULL;
	SDL_Surface *surface = NULL;

	// Une variables de couleur
	SDL_Color	noir = {0, 0, 0, 0}, 
				blanc = {255, 255, 255, 255}, 
				orange = {255, 127, 40, 255};
	SDL_Rect	damier[42], 
				slots[6][7];
	SDL_Event event;

	SDL_bool quit = SDL_FALSE;

	int nbLignes=6, 
		nbColonnes=7, 
		n = nbLignes*nbColonnes, // 42
		largeurRectGrille=51, 
		hauteur=largeurRectGrille, // carré
		offsetGrille=10, 
		espacementGrille=1, // les rectangles font 1 pixel d'épaisseur
        offset = 0, 
		largeurPiece = 50, 
		offsetJetons = offsetGrille+espacementGrille;

	//valeur toujours retournée à la fin du programme
	int statut = EXIT_FAILURE;


	

	//créer fenêtre ET renderer en même temps
	if( init(&pWindow, &renderer, 640, 480) != 0 )
	{
		goto Quit;
	}

//====

// On agit sur la fenêtre ici 

    // arrière-plan de la fenêtre tout noir
	setWindowColor(renderer, noir);



 // damier de rectangles tracés sur le renderer

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // dessiner en cyan


	for(int i=0, indice=0 ; i<nbLignes ; i++)
	{
		for(int j=0 ; j<nbColonnes ; j++, indice++) 
		{
			SDL_SetRenderDrawColor(renderer, indice*3, 255, indice*3, 255);

			//largeurRectGrille * le nombre de rectangles précédents
			//+ offsetGrille (décale l'ensemble de carrés par rapport au coin supérieur gauche de la fenêtre)
			// - i(ou j) (pour que les bordures des carrés se superposent)
			damier[indice].x = largeurRectGrille * j +offsetGrille - j;
			damier[indice].y = hauteur  * i +offsetGrille - i;
			damier[indice].w = largeurRectGrille;
			damier[indice].h = hauteur;

			//SDL_RenderDrawRect( renderer, &damier[indice] ); // dessine les carrés les uns après les autres
		}
	}

//====
	SDL_RenderDrawRects(renderer, damier, n); // autre méthode pour afficher plusieurs carrés


//====

	//texture = loadImage("<fichier>>.bmp",renderer);
		

	hauteur = largeurPiece;
	//remplir matrice "slots" de rectangles ayant des coordonnées permettant de placer une texture de jeton facilement (les valeurs doivent correspondre à la grille de jeu)
	for(int i=0 ; i<6 ; i++) {
		for(int j=0 ; j<7 ; j++) {
		
			slots[i][j].x = espacementGrille * j + largeurPiece * j + offsetJetons;
			slots[i][j].y = espacementGrille * i + hauteur * i + offsetJetons;
			slots[i][j].w = largeurPiece;
			slots[i][j].h = hauteur;
		}
	}


/*
	//affiche la texture sur tous les emplacements de slots
	for(int i=0 ; i<6 ; i++) {
		for(int j=0 ; j<7 ; j++) {
			
			SDL_RenderCopy(renderer, texture, NULL, &slots[i][j]); 
		}
	}
*/


	//affiche la texture à 2 endroits choisis
	SDL_RenderCopy(renderer, texture, NULL, &slots[5][0]); 
	SDL_RenderCopy(renderer, texture, NULL, &slots[5][2]); 


//====

	SDL_RenderPresent(renderer); // met à jour les dessins du Renderer sur l'écran !

//====

	// Boucle principale du programme
	while(!quit)
	{
		// Gestion_Évènements
    	SDL_WaitEventTimeout(&event, 50);
		// Analyse_Évènements
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if(event.type == SDL_MOUSEBUTTONUP)
		{
			//if(event.button.button == SDL_BUTTON_LEFT && event.button.clicks >= 2)
				//printf("Au moins un double clic gauche\n");
		}
		

		//SDL_Delay(50); // petite pause, pour les performances
	}
	// Fin Boucle



	statut = EXIT_SUCCESS;

// Quitter
Quit:
	if(texture) 
        SDL_DestroyTexture(texture);
	if(renderer) 
		SDL_DestroyRenderer(renderer);
	if(surface) 
		SDL_FreeSurface(surface);
	//if(format)
		//SDL_FreeFormat(format);
	if(pWindow) //Destruction de la fenetre
		SDL_DestroyWindow(pWindow);
	
	SDL_Quit();




	return statut;
}


