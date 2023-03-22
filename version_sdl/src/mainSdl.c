#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/fonc2.h"
#include "../lib/foncSdl.h"

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


