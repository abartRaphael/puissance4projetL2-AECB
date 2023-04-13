#include <stdio.h>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

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



/**
 * \fn SDL_Rect creerRect(int x, int y, int w, int h)
 * \brief crée un "SDL_Rect" à partir de ses 4 champs
 * \param x coordonnée horizontale du rectangle à partir du bord gauche de la fenêtre
 * \param y coordonnée verticale du rectangle à partir du bord haut de la fenêtre
 * \param w longueur du rectangle
 * \param h hauteur du rectangle
 * \return retourne un "SDL_Rect"
 */
SDL_Rect creerRect(int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x ;///Coordonnées x de l'angle haut gauche
	rectangle.y = y ;///Corddonnées y de l'angle haut gauche 
	rectangle.w = w ;///Longueur du rectangle
	rectangle.h = h ;///Hauteur
	return rectangle ;
}



/**
 * \fn Mix_Music* loadMusique(const char* path)
 * \brief charge une musique à partir d'un fichier
 * \param path chemin d'accès, relatif ou absolu, vers le fichier de musique (.mp3) à ouvrir
 * \return retourne un pointeur sur un type "Mix_Music", utilisé pour les fonctions "SDL_mixer"
 */
Mix_Music* loadMusique(const char* path)
{
	// "../musique/musique.mp3"

	Mix_Music* musique = Mix_LoadMUS(path);
	if (musique == NULL) {
		printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}

	return musique;
}



/**
 * \fn int initStructTexturesMenu( SDL_Renderer* renderer, images_menus_t* images )
 * \brief crée (alloue) les images des menus et les affecte à une structure images_menus_t
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus, à remplir
 * \return retourne 1 pour un succès, 0 pour une erreur
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

		
	return(imagesMenus->tache_bleue && imagesMenus->regles && imagesMenus->bouton_back
		&& imagesMenus->bouton_contre_joueur && imagesMenus->bouton_contre_ordinateur
		&& imagesMenus->bouton_jouer && imagesMenus->bouton_mode_creux
		&& imagesMenus->bouton_mode_normal && imagesMenus->bouton_quitter
		&& imagesMenus->bouton_regles && imagesMenus->bouton_rejouer
		&& imagesMenus->sound_off && imagesMenus->sound_on);
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
 * \fn int initStructRectMenu( SDL_Renderer* renderer, rect_menus_t* rectMenus, int l, int h )
 * \brief crée les rectangles où placer les images des menus et les ajoute à une structure rect_menus_t
 * \param pWindow pointeur de SDL_Window, pour récupérer les dimensions de la fenêtre
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus, à remplir
 */
void initStructRectMenu( SDL_Window* pWindow, SDL_Renderer* renderer, rect_menus_t* rectMenus ) {

	// La largeur et la hauteur de la fenêtre du menu
	int l, 
		h;

	SDL_GetWindowSize(pWindow, &l, &h);

	rectMenus->rect_bouton_jouer = 				creerRect(l/4,	h/5+10,		l/2,	h/6);
	rectMenus->rect_bouton_regles = 			creerRect(l/4,	(h/5)*2+10,	l/2,	h/6);
	rectMenus->rect_bouton_quitter = 			creerRect(l/4,	(h/5)*3+10,	l/2,	h/6);    

	rectMenus->rect_bouton_mode_normal = 		creerRect(l/4,	h/4+30,		l/2,	h/6);
	rectMenus->rect_bouton_mode_creux = 		creerRect(l/4,	(h/4)*2+30,	l/2,	h/6);

	rectMenus->rect_bouton_rejouer = 			creerRect(l/4,	h/4+30,		l/2,	h/6);
	rectMenus->rect_bouton_quitter_fin = 		creerRect(l/4,	(h/4)*2+30,	l/2,	h/6);    

	rectMenus->rect_bouton_back = 				creerRect(10,	10,			40,		40); // Position de l'icône en haut à gauche de la fenêtre

	rectMenus->rect_sound = 					creerRect(l-60,	h-60,		60,		60); // Position de l'icône en bas à droite de la fenêtre

	// inutilisé
	//rectMenus->rect_bouton_contre_joueur = 		creerRect(l/4,	h/5,	l/4,	h/6);
	//rectMenus->rect_bouton_contre_ordinateur = 	creerRect(l/4,	(h/5)*2,l/2,	h/6); 

	// pas utile
	//SDL_Rect bouton_sound_off_rect = 			creerRect(580, 420, 50, 50); // Position de l'icône en bas à droite de la fenêtre
	//SDL_Rect regles_rect = 					creerRect(0, 0, l, h);
}



/**
 * \fn int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t* menu_actuel )
 * \brief affiche le menu à l'écran, en fonction de menu_actuel
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus
 * \param menu_actuel type enum représentant le menu à afficher
 * \return 0 pour un succès, -1 pour une erreur
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
			err = SDL_RenderCopy(renderer, imagesMenus->bouton_quitter, NULL, &rectMenus->rect_bouton_quitter_fin);
			if(err == -1) {
				fprintf(stderr, "Erreur SDL_RenderCopy, dans afficherMenu : %s\n", SDL_GetError());
				return err;
			}
			break;

		case modeNormal:
		case modeCreux:
		default:
			printf("Mauvaise valeur d'état dans (*menu_actuel) : %d\n", *menu_actuel);
	}

	if( Mix_PlayingMusic() ) {
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



/**
 * \fn int afficherMenu( SDL_Renderer* renderer, images_menus_t* imagesMenus, rect_menus_t* rectMenus, affichage_t menu_actuel )
 * \brief affiche le menu à l'écran, en fonction de menu_actuel
 * \param pWindow pointeur de SDL_Window, pour récupérer les dimensions de la fenêtre
 * \param renderer pointeur de SDL_Renderer, nécessaire
 * \param imagesMenus structure contenant des pointeurs sur toutes les textures d'images des menus
 * \param rectMenus structure contenant les rectangles où placer les images pour les menus
 * \param actuel type enum représentant le menu à afficher en premier
 * \param musique pointeur de Mix_Music, pour relancer la musique quand on appuie sur le bouton Mute une 2e fois
 * \return 0 pour un succès, -1 pour une erreur
 */
int gererMenus( SDL_Window* pWindow, SDL_Renderer* renderer, images_menus_t* imagesMenus, affichage_t* actuel, Mix_Music* musique ) {

	SDL_Event event;
	SDL_Point clic;

	//menu_t menu_actuel = principal; 
	rect_menus_t rectMenus;



	// initialisations

	// initialiser toutes les images
	if( initStructTexturesMenu( renderer, imagesMenus ) == 0 ) {
		fprintf(stderr, "Erreur loadImage, dans initStructTexturesMenu : %s\n", SDL_GetError());
		return -1;
	}

	// créer les rectangles où placer les images
	initStructRectMenu(	pWindow, renderer, &rectMenus );




	// Boucle principale du menu

	while( *actuel == principal 
		|| *actuel == regles 
		|| *actuel == mode
		|| *actuel == fin ) {
		// Gestion des événements
		SDL_WaitEventTimeout(&event, 200);

		if( afficherMenu( renderer, imagesMenus, &rectMenus, actuel ) == -1 ) {
			return -1;
		}
		
		SDL_RenderPresent(renderer);

		if (event.type == SDL_QUIT) {
			// L'utilisateur a cliqué sur le bouton de fermeture de la fenêtre
			*actuel = quitter;
		}
		else if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
			// * la fenêtre a été redimensionnée

			//printf("event.window.data1 = %d\nevent.window.data2 = %d",event.window.data1,event.window.data2);

			// * recalculer les rectangles où placer les images
			initStructRectMenu(	pWindow, renderer, &rectMenus );

			// * réafficher le menu
			if( afficherMenu( renderer, imagesMenus, &rectMenus, actuel ) == -1 ) {
				return -1;
			}

			SDL_RenderPresent(renderer); // met à jour les dessins du Renderer sur l'écran
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
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_mode_creux) ) {
						// Le bouton "Mode Creux" a été cliqué
						*actuel = modeCreux;
					}

					break;
				case fin:
					if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_rejouer) ) {
						// Le bouton "Rejouer" a été cliqué
						*actuel = mode;
					}
					else if( SDL_PointInRect(&clic, &rectMenus.rect_bouton_quitter_fin) ) {
						// Le bouton "Quitter" a été cliqué
						*actuel = quitter;
					}
					break;
				
				case modeNormal:
				case modeCreux:
				case quitter:
				default:
					printf("Mauvaise valeur d'état dans (*actuel) : %d\n", *actuel);
			}
			
		
			// dans tous les cas:
			if( SDL_PointInRect(&clic, &rectMenus.rect_sound) ) {
				// Le bouton "mute" à été cliqué
				if( Mix_PlayingMusic() )
				{
					// Si la musique est active, on la coupe
					Mix_HaltMusic();
				}
				else
				{
					// Si la musique est inactive, on la joue en boucle
					if( Mix_PlayMusic(musique, -1) == -1 ) {
						fprintf(stderr, "Erreur Mix_PlayMusic, dans gererMenus : %s\n", Mix_GetError());
						return -1;
					}

				}
			}
		}
	}

	return 0;
}
