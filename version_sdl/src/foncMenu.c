#include <stdio.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_mixer.h>

#include "../lib/foncSdl.h"
#include "../lib/foncMenu.h"


/**
 * \file foncMenu.c
 * \brief Corps des fonctions des menus
 * \version 0.1
 * \date {11/04/2023}
 * \author ElGhoumari Soumia
 * \author Abart Raphaël
 * \author Coupé Xavier
*/




// La couleur du texte pour les boutons
// const SDL_Color TEXT_COLOR = {255, 255, 255};



SDL_Rect creerRect(int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x ;///Coordonnées x de l'angle haut gauche
	rectangle.y = y ;///Corddonnées y de l'angle haut gauche 
	rectangle.w = w ;///Longueur du rectangle
	rectangle.h = h ;///Hauteur
	return rectangle ;
	/**
	\return rectangle
	*/
}


/*
Mix_Music* loadMusique(char* path)
{
	// "../musique/musique.mp3"

	Mix_Music* musique = Mix_LoadMUS(path);
	if (musique == NULL) {
		printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}

	//Mix_PlayMusic(musique, -1);
}
*/


/**
 * \fn int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* images )
 * \brief crée (alloue) les images des menus et les affecte à une structure images_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus, à remplir
 */
int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus ) {
	/** 
	 * Les textures ne sont pas faites pour une modification pixels par pixels. 
	 * Elles ont l’avantage d’êtres affichables rapidement, 
	 * de pouvoir être redimensionnée à la volée et copiée rapidement
	 */
	
	// autre solution -> IMG_Load();


	// charger les images des arrière_plans
	imagesMenus->tache_bleue = loadImage("img/imageMenu/tache_bleue.bmp",renderer);
	imagesMenus->regles = loadImage("img/imageMenu/regles.bmp",renderer);

	// charger les images des boutons
	imagesMenus->bouton_back = loadImage("img/imageMenu/bouton_back.bmp",renderer);
	imagesMenus->bouton_contre_joueur = loadImage("img/imageMenu/bouton_contre_joueur.bmp",renderer);
	imagesMenus->bouton_contre_ordinateur = loadImage("img/imageMenu/bouton_contre_ordinateur.bmp",renderer);
	imagesMenus->bouton_jouer = loadImage("img/imageMenu/bouton_jouer.bmp",renderer);
	imagesMenus->bouton_mode_creux = loadImage("img/imageMenu/bouton_mode_creux.bmp",renderer);
	imagesMenus->bouton_mode_normal = loadImage("img/imageMenu/bouton_mode_normal.bmp",renderer);
	imagesMenus->bouton_quitter = loadImage("img/imageMenu/bouton_quitter.bmp",renderer);
	imagesMenus->bouton_regles = loadImage("img/imageMenu/bouton_regles.bmp",renderer);
	imagesMenus->bouton_rejouer = loadImage("img/imageMenu/bouton_rejouer.bmp",renderer);
	imagesMenus->sound_off = loadImage("img/imageMenu/sound_off.bmp",renderer);
	imagesMenus->sound_on = loadImage("img/imageMenu/sound_on.bmp",renderer);

		
	return 0;
}



/**
 * \fn int freeLesImagesMenu(images_menus_t* images)
 * \brief free (désalloue) les images des menus dans une structure images_menus_t
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus, à désallouer
 */
void freeLesImagesMenu(images_menus_t* imagesMenus) {

	if( imagesMenus->tache_bleue != NULL)
		SDL_DestroyTexture( imagesMenus->tache_bleue );
	if( imagesMenus->regles != NULL)
		SDL_DestroyTexture( imagesMenus->regles );
	if( imagesMenus->bouton_back != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_back );
	if( imagesMenus->bouton_contre_joueur != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_contre_joueur );
	if( imagesMenus->bouton_contre_ordinateur != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_contre_ordinateur );
	if( imagesMenus->bouton_jouer != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_jouer );
	if( imagesMenus->bouton_mode_creux != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_mode_creux );
	if( imagesMenus->bouton_mode_normal != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_mode_normal );
	if( imagesMenus->bouton_quitter != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_quitter );
	if( imagesMenus->bouton_rejouer != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_rejouer );
	if( imagesMenus->bouton_regles != NULL)
		SDL_DestroyTexture( imagesMenus->bouton_regles );
	if( imagesMenus->sound_off != NULL)
		SDL_DestroyTexture( imagesMenus->sound_off );
	if( imagesMenus->sound_on != NULL)
		SDL_DestroyTexture( imagesMenus->sound_on );
}



/**
 * \fn int initStructRectMenu( SDL_Renderer* renderer, rect_menus_t* rectMenus, int largeurWindow, int hauteurWindow )
 * \brief crée les rectangles où placer les images des menus et les ajoute à une structure rect_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus, à remplir
 * \param largeurWindow largeur actuelle de la fenêtre
 * \param hauteurWindow hauteur actuelle de la fenêtre
 */
void initStructRectMenu( SDL_Renderer* renderer, rect_menus_t* rectMenus, int largeurWindow, int hauteurWindow ) {

	rectMenus->rect_bouton_back = 				creerRect(10, 10, 40, 40); // Position de l'icône en haut à gauche de la fenêtre
	rectMenus->rect_bouton_contre_joueur = 		creerRect(largeurWindow/4, 100, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_bouton_contre_ordinateur = 	creerRect(largeurWindow/4, 200, largeurWindow/2, hauteurWindow/3); 
	rectMenus->rect_bouton_jouer = 				creerRect(largeurWindow/4, 80, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_bouton_mode_creux = 		creerRect(largeurWindow/4, 200, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_bouton_mode_normal = 		creerRect(largeurWindow/4, 100, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_bouton_quitter = 			creerRect(largeurWindow/4, 160, largeurWindow/2, hauteurWindow/3);    
	rectMenus->rect_bouton_regles = 			creerRect(largeurWindow/4, 240, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_bouton_rejouer = 			creerRect(largeurWindow/4, 80, largeurWindow/2, hauteurWindow/3);
	rectMenus->rect_sound = 					creerRect(580, 420, 50, 50); // Position de l'icône en bas à droite de la fenêtre

	//SDL_Rect bouton_sound_off_rect = 			creerRect(580, 420, 50, 50); // Position de l'icône en bas à droite de la fenêtre
	//SDL_Rect regles_rect = 					creerRect(0, 0, largeurWindow, hauteurWindow);
}



/**
 * \fn int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t* menu_actuel )
 * \brief affiche le menu à l'écran, en fonction de menu_actuel
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus
 * \param menu_actuel type enum représentant le menu à afficher
 */
int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t* menu_actuel ) {

	int err;

	SDL_Color noir = {0, 0, 0, 0};

	setDrawColor(renderer, noir);
	SDL_RenderClear(renderer);

	switch(*menu_actuel) {
		case principal:
			err = SDL_RenderCopy(renderer, imagesMenus->tache_bleue, NULL, NULL);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_jouer, NULL, &rectMenus->rect_bouton_jouer);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_quitter, NULL, &rectMenus->rect_bouton_quitter);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_regles, NULL, &rectMenus->rect_bouton_regles);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			break;
		case regles:
			err = SDL_RenderCopy(renderer, imagesMenus->regles, NULL, NULL);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_back, NULL, &rectMenus->rect_bouton_back);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			break;
		case mode:
			err = SDL_RenderCopy(renderer, imagesMenus->tache_bleue, NULL, NULL);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_mode_normal, NULL, &rectMenus->rect_bouton_mode_normal);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_mode_creux, NULL, &rectMenus->rect_bouton_mode_creux);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_back, NULL, &rectMenus->rect_bouton_back);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			break;
		case fin:
			err = SDL_RenderCopy(renderer, imagesMenus->tache_bleue, NULL, NULL);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_rejouer, NULL, &rectMenus->rect_bouton_rejouer);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_quitter, NULL, &rectMenus->rect_bouton_quitter);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			break;
	}

	//if(musique_active)
	if(1) {
		err = SDL_RenderCopy(renderer, imagesMenus->sound_on, NULL, &rectMenus->rect_sound);
		if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
		}
	}
	else {
		err = SDL_RenderCopy(renderer, imagesMenus->sound_off, NULL, &rectMenus->rect_sound);
		if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
		}
	}
	return 0;
}



int menuPrincipal( SDL_Window* pWindow, SDL_Renderer* renderer, images_menus_t* imagesMenus, affichage_t* actuel ) {


	// La largeur et la hauteur de la fenêtre du menu
	int largeurWindow, 
		hauteurWindow, 
		err = 0, 
		continuer = 1, 
		musique_active = 1;

	SDL_Event event;
	SDL_Point clic;

	//menu_t menu_actuel = principal; 
	rect_menus_t rectMenus;



	//initialisations
	SDL_GetWindowSize(pWindow, &largeurWindow, &hauteurWindow);

	initStructTexturesMenu(	renderer, imagesMenus );

	initStructRectMenu(	renderer, &rectMenus, largeurWindow, hauteurWindow );




	// Boucle principale du menu

	while(continuer) {
		// Gestion des événements
		SDL_WaitEventTimeout(&event, 200);

		if( afficherMenu( renderer, imagesMenus, &rectMenus, actuel ) == -1 ) {
			return -1;
		}
		
		SDL_RenderPresent(renderer);

		if (event.type == SDL_QUIT) {
			// L'utilisateur a cliqué sur le bouton de fermeture de la fenêtre
			continuer = 0;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) 
		{
			clic.x = event.button.x;
			clic.y = event.button.y;

			switch(*actuel) {

				case principal:
					// menu principal à l'écran

					if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_quitter) ) {
						// Le bouton "Quitter" a été cliqué
						*actuel = quitter;
						continuer = 0;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_jouer) ) {
						// Le bouton "Jouer" a été cliqué
						*actuel = mode;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_regles) ) {
						// Le bouton "Regles" a été cliqué
						*actuel = regles;
					}
					break;
				
				
				case regles:
					if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_back) ) {
						// Le bouton "Back" a été cliqué
						*actuel = principal;
					}
					break;
					
				case mode:
					if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_back) ) {
						// Le bouton "Back" a été cliqué
						*actuel = principal;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_mode_normal) ) {
						// Le bouton "Mode Classique" a été cliqué
						*actuel = modeNormal;
						continuer = 0;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_mode_creux) ) {
						// Le bouton "Mode Creux" a été cliqué
						*actuel = modeCreux;
						continuer = 0;
					}

					break;
				case fin:
					if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_rejouer) ) {
						// Le bouton "Rejouer" a été cliqué
						*actuel = mode;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_quitter) ) {
						// Le bouton "Quitter" a été cliqué
						*actuel = quitter;
						continuer = 0;
					}
					break;
			}
			
		
			// dans tous les cas
			if( SDL_PointInRect(&clic, &rectMenus.rect_sound) ) {
				// Le bouton "mute" à été cliqué
				if(musique_active)
				{
					//Mix_HaltMusic(); // Si la musique est active, on la coupe
					musique_active = 0;
				}
				else
				{
					//Mix_PlayMusic(musique, -1); // Si la musique est inactive, on la joue en boucle
					musique_active = 1;
				}
			}
		}
	}

	return err;
}
