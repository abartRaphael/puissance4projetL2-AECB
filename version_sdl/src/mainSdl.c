#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "../lib/fonc2.h"
#include "../lib/foncSdl.h"
#include "../lib/foncMenu.h"

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
	// Le pointeur vers la fenetre
	SDL_Window* pWindow=NULL;
	// Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer=NULL;

	Mix_Music* musique=NULL;
	
	// valeur toujours retournée à la fin du programme
	int statut = EXIT_FAILURE;

	//t_partie typeDePartie;
	affichage_t actuel=principal;
	images_menus_t imagesMenus;
	

	//créer fenêtre ET renderer en même temps
	if( init(&pWindow, &renderer, 666, 533) != 0 )
	{
		goto Quit;
	}

	// Initialisation de SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

		fprintf(stderr, "Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
		//goto Quit;
	}
	else {
		// bonne initialisation
		musique = loadMusique("../musique/musique.mp3");
	}


//====

// On agit sur la fenêtre ici 


	// menu principal

	while(actuel != quitter) {
		if( gererMenus( pWindow, renderer, &imagesMenus, &actuel, musique ) == -1 ) {
			fprintf(stderr, "Erreur gererMenus() : %s\n", SDL_GetError());
			goto Quit;
		}

		if( actuel != quitter ) {

			demarrer_partie(pWindow, renderer, actuel);
		}
	}




	statut = EXIT_SUCCESS;

// Quitter
Quit:

	freeLesImagesMenu(&imagesMenus);

	if(musique)
		Mix_FreeMusic(musique);
	Mix_CloseAudio();

	if(renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if(pWindow) {
		// Destruction de la fenetre
		SDL_DestroyWindow(pWindow);
	}

	SDL_Quit();

	printf("bonne fin de programme\n");


	return statut;
}


