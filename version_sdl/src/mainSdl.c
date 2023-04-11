#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

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
	
	//valeur toujours retournée à la fin du programme
	int statut = EXIT_FAILURE;

	t_partie typeDePartie;
	

	//créer fenêtre ET renderer en même temps
	if( init(&pWindow, &renderer, 640, 480) != 0 )
	{
		goto Quit;
	}

//====

// On agit sur la fenêtre ici 


	// menu principal


	// lancement de partie normale

	//typeDePartie = modeNormal;
	typeDePartie = modeCreux;

	demarrer_partie(pWindow, renderer, typeDePartie);






	statut = EXIT_SUCCESS;

// Quitter
Quit:

	if(renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if(pWindow) {
		// Destruction de la fenetre
		SDL_DestroyWindow(pWindow);
	}

	SDL_Quit();

	//printf("bonne fin de programme\n");


	return statut;
}


