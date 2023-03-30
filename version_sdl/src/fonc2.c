#include <stdio.h>
#include <stdlib.h>
// #include <IMG.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../lib/fonc2.h"
#ifndef H_FONCSDL_
	#include "../lib/foncSdl.h"
#endif /*H_FONCSDL_ */

 
/**
 * \file fonc2.c
 * \brief Corps des fonctions
 * \version 0.1
 * \date {9/02/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/


/**
	* Compteur de pieces creuses rouges
	*/
unsigned int cpt_rouge_creuse = NB_CREUSE;

/**
	* Compteur de pieces bloquantes rouges
	*/
unsigned int cpt_rouge_bloquante = NB_BLOQUANTE;

/**
	* Compteur de pieces creuses jaunes
	*/
unsigned int cpt_jaune_creuse = NB_CREUSE;

/**
	* Compteur de pieces bloquantes jaunes
	*/
unsigned int cpt_jaune_bloquante = NB_BLOQUANTE;



/**
 * \fn void initGrille(t_pion grilleDeValeurs[LIGNES][COLONNES])
 * \brief Remplit toutes les cases de la grille de puissance 4 avec la valeur "vide"
 * \param grilleDeValeurs grille de puissance 4
 */
void initGrille(t_pion grilleDeValeurs[LIGNES][COLONNES]) {

	for(int i=0 ; i<LIGNES ; i++) {
		for(int j=0 ; j<COLONNES ; j++) {

			grilleDeValeurs[i][j].couleur = vide;
			grilleDeValeurs[i][j].type = vide;
		}
	}
}



/**
 * \fn int estPleine(t_pion grilleDeValeurs[LIGNES][COLONNES], int c)
 * \brief Permet de savoir si une colonne est pleine, et donc on ne peut plus y ajouter de pions
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \return retourne 1 si on ne peut plus ajouter de pions à cette colonne, 0 sinon
 */
int estPleine(t_pion grilleDeValeurs[LIGNES][COLONNES], int c) {

	if(grilleDeValeurs[0][c].couleur == vide) {
		return 0;
	}
	else {
		return 1;
	}
}



/**
 * \fn int caseLibre(t_pion grilleDeValeurs[LIGNES][COLONNES], int c)
 * \brief Permet de savoir quelle case d'une colonne donnée est vide, et la plus basse
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \return retourne l'indice de la ligne où la case est vide, ou -1 si la colonne est pleine
 */
int caseLibre(t_pion grilleDeValeurs[LIGNES][COLONNES], int c) {

	//l commence à "LIGNES-1", qui est la ligne la plus basse
	int l=LIGNES-1;
	
	if(!estPleine(grilleDeValeurs, c)) {

		while(grilleDeValeurs[l][c].couleur != vide) {
			//quand il y a un pion dans la case, on fait remonter l
			l--;
		}

		return l;
	}

	return -1;
}



/**
 * \fn int ajoutPion(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief Permet d'ajouter un pion à la grille de jeu
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \param pion le pion joué
 * \return retourne 0 si le pion est bien ajouté à la grille, 1 sinon, avec un message d'erreur
 */
int ajoutPion(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion pion){

	int l;

	//test pour voir si la valeur entrée est dans le bon intervale
	if(c >= COLONNES || c < 0) {
		return 1;
	}

	l = caseLibre(grilleDeValeurs, c);
	if(l != -1 && l != LIGNES-1) {
		switch(pion.type){
			case creuse :
				switch(grilleDeValeurs[l+1][c].type){
					case creuse : 
						if(grilleDeValeurs[l+1][c].couleur != pion.couleur){
							// pion creux jouée sur pion creux = pareil qu'une pion plein, elle devient bloquant à 2 couleurs (le pion joué a sa couleur au centre)
							if(pion.couleur == rouge) {
								grilleDeValeurs[l+1][c].couleur = jauneRouge;
							}
							else {
								grilleDeValeurs[l+1][c].couleur = rougeJaune;
							}
						}
						else{
							grilleDeValeurs[l+1][c].couleur = pion.couleur;
						}
						grilleDeValeurs[l+1][c].type = bloquante;
						break;
					case pleine : 
						if(grilleDeValeurs[l+1][c].couleur != pion.couleur){
							// pion creux jouée sur pion plein = devient bloquant à 2 couleurs, avec le pion plein au centre
							if(pion.couleur == rouge) {
								grilleDeValeurs[l+1][c].couleur = rougeJaune;
							}
							else {
								grilleDeValeurs[l+1][c].couleur = jauneRouge;
							}
						}
						else{
							// pion creux sur pion plein de même couleur
							grilleDeValeurs[l+1][c].couleur = pion.couleur;
						}
						grilleDeValeurs[l+1][c].type = bloquante;
						break;
					case bloquante : 
						// interraction classique, pion placée au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					default : printf("Impossible de voir ce message ajout_pion\n");
				}
				break;
			case pleine :
				switch(grilleDeValeurs[l+1][c].type){
					case creuse : 
						if(grilleDeValeurs[l+1][c].couleur != pion.couleur){
							// pion plein joué sur pion creux = devient bloquant à 2 couleurs, avec le pion plein au centre
							if(pion.couleur == rouge) {
								grilleDeValeurs[l+1][c].couleur = jauneRouge;
							}
							else {
								grilleDeValeurs[l+1][c].couleur = rougeJaune;
							}
						}
						else{
							// pion creux sur pion plein de même couleur
							grilleDeValeurs[l+1][c].couleur = pion.couleur;
						}
						grilleDeValeurs[l+1][c].type = bloquante;
						break;
					case pleine : 
						// interraction classique, pion placé au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					case bloquante : 
						// interraction classique, pion placé au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					default : printf("Impossible de voir ce message ajout_pion\n");
				}
				break;
			case bloquante :
				switch(grilleDeValeurs[l+1][c].type){
					case creuse : 
						// interraction classique, pion placé au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					case pleine : 
						// interraction classique, pion placé au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					case bloquante : 
						// interraction classique, pion placé au dessus du précédent
						grilleDeValeurs[l][c].couleur = pion.couleur;
						grilleDeValeurs[l][c].type = pion.type;
						break;
					default : printf("Impossible de voir ce message ajout_pion\n");
				}
				break;
			default : printf("Impossible de voir ce message ajout_pion\n");
		
		}
		return 0;
	}
	else{
		grilleDeValeurs[l][c].couleur = pion.couleur;
		grilleDeValeurs[l][c].type = pion.type;
		return 0;
	}
	printf("Cette colonne est pleine, recommencez\n");
	return 1;
}



/**
 * \fn int quatreALaSuiteHorizontal(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion couleur) 
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même LIGNE
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param pion le pion joué
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteHorizontal(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion pion) {

	int pionsALaSuite=0;

	//est-ce que le pion du centre est de la même couleur que celle du joueur qui a joué, déjà
	if(grilleDeValeurs[l][3].couleur == pion.couleur || grilleDeValeurs[l][3].couleur == rougeJaune) {

		//parcourir la ligne où le dernier pion a été joué
		for(int i=0 ; i<COLONNES ; i++) {

			if(grilleDeValeurs[l][i].couleur == pion.couleur || grilleDeValeurs[l][i].couleur == rougeJaune ) {
				pionsALaSuite++;
			}
			else {
				pionsALaSuite = 0;
			}

			if(pionsALaSuite > 3) {
				return 1;
			}
		}
	}

	return 0;
}

/**
 * \fn int quatreALaSuiteVertical(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même COLONNE
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param pion le pion joué
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteVertical(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion pion) {

	int pionsALaSuite=0;

	//parcourir la ligne où le dernier pion a été joué
	for(int i=0 ; i<LIGNES ; i++) {

		if(grilleDeValeurs[i][c].couleur == pion.couleur || grilleDeValeurs[i][c].couleur == rougeJaune) {
			pionsALaSuite++;
		}
		else {
			pionsALaSuite = 0;
		}

		if(pionsALaSuite > 3) {
			return 1;
		}
	}
	
	return 0;
}

/**
 * \fn int quatreALaSuiteDiagonale1(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la gauche/haut
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param pion le pion joué
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale1(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion pion) {

	int pionsALaSuite=0, 
		x=c, 
		y=l;

	//décaler les "coordonnées" jusqu'à atteindre le bord (gauche ou haut) de la grille
	while(x > 0 && y > 0) {
		x--;
		y--;
	}
	
	//coordonnées où un puissance 4 est impossible:
	//y = 3 4 5
	//x = 4 5 6
	if(x >= 4 || y >= 3) {
		return 0;
	}


	//parcourir la diagonale où le dernier pion a été joué
	while(x < COLONNES && y < LIGNES) {

		if(grilleDeValeurs[y][x].couleur == pion.couleur || grilleDeValeurs[y][x].couleur == rougeJaune) {
			pionsALaSuite++;
		}
		else {
			pionsALaSuite = 0;
		}

		x++;
		y++;

		if(pionsALaSuite > 3) {
			return 1;
		}
	}

	return 0;
}



/**
 * \fn int quatreALaSuiteDiagonale2(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la droite/haut
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param pion le pion joué
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale2(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, int l, t_pion pion) {

	int pionsALaSuite=0, 
		x=c, 
		y=l;

	//printf("x=%i\ny=%i\n", x, y);

	//décaler les "coordonnées" jusqu'à atteindre le bord (droit ou haut) de la grille
	while(x < (COLONNES-1) && y > 0) {
		x++;
		y--;
	}
	
	//coordonnées où un puissance 4 est impossible:
	//y = 3 4 5
	//x = 2 1 0
	if(x <= 2 || y >= 3) {
		return 0;
	}


	//parcourir la diagonale où le dernier pion a été joué
	while(x >= 0 && y < LIGNES) {

		if(grilleDeValeurs[y][x].couleur == pion.couleur || grilleDeValeurs[y][x].couleur == rougeJaune) {
			pionsALaSuite++;
		}
		else {
			pionsALaSuite = 0;
		}

		x--;
		y++;

		if(pionsALaSuite > 3) {
			return 1;
		}
	}

	return 0;
}



/**
 * \fn int estQuatreALaSuite(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief appelle les quatre fonctions pour vérifier s'il y a un 4 à la suite après le dernier coup joué
 * \param grilleDeValeurs grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param pion le pion joué
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int estQuatreALaSuite(t_pion grilleDeValeurs[LIGNES][COLONNES], int c, t_pion pion) {

	int l;//ligne où se trouve le dernier pion joué

	if(caseLibre(grilleDeValeurs, c) != -1) {
		l = caseLibre(grilleDeValeurs, c) + 1;
	}
	else {
		l = 0;
	}


	return quatreALaSuiteHorizontal(grilleDeValeurs, c, l, pion)
	|| quatreALaSuiteVertical(grilleDeValeurs, c, pion)
	|| quatreALaSuiteDiagonale1(grilleDeValeurs, c, l, pion)
	|| quatreALaSuiteDiagonale2(grilleDeValeurs, c, l, pion);
}



/**
 * \fn void sauvegardeAuto(t_pion grilleDeValeurs[LIGNES][COLONNES], t_pion couleur, int nbTours)
 * \brief Sauvegarde la configuration de la partie actuelle
 * \param grilleDeValeurs grille de puissance 4
 * \param pion le dernier pion joué
 * \param nbTours nombre de tours effectués
 */
void sauvegardeAuto(t_pion grilleDeValeurs[LIGNES][COLONNES], t_pion pion, int nbTours) {

	FILE* f;
	f = fopen("partie.txt", "w");

	//grille de jeu
	for(int i=0 ; i<LIGNES ; i++) {
		for(int j=0 ; j<COLONNES ; j++) {

			fprintf(f, "%i %i ", grilleDeValeurs[i][j].couleur, grilleDeValeurs[i][j].type);
		}
		fprintf(f, "\n");
	}

	//nombre de tours
	fprintf(f, "%i\n", nbTours);

	//couleur du dernier joueur à avoir joué
	fprintf(f, "%i\n", pion.couleur);

	fclose(f);
}



/**
 * \fn void chargerPartie(t_pion grilleDeValeurs[LIGNES][COLONNES], t_pion* couleur, int* nbTours)
 * \brief Charge la configuration de la partie sauvegardée dans le fichier "partie.txt"
 * \param grilleDeValeurs grille de puissance 4
 * \param pion le dernier pion à avoir été joué
 * \param nbTours nombre de tours effectués
 */
void chargerPartie(t_pion grilleDeValeurs[LIGNES][COLONNES], t_pion* pion, int* nbTours) {

	int valeur;//placeholder
		int type;//Type du pion
		
	FILE* f;
	f = fopen("partie.txt", "r");

	//grille de jeu
	for(int i=0 ; i<LIGNES ; i++) {
		for(int j=0 ; j<COLONNES ; j++) {

			fscanf(f, "%i %i", &valeur, &type);

			switch(valeur) {
				case vide: grilleDeValeurs[i][j].couleur = vide; break;
				case rouge: grilleDeValeurs[i][j].couleur = rouge; break;
				case jaune: grilleDeValeurs[i][j].couleur = jaune; break;
				case rougeJaune : grilleDeValeurs[i][j].couleur = rougeJaune; break;
			}
			switch(type){
				case creuse : grilleDeValeurs[i][j].type = creuse; break;
				case pleine : grilleDeValeurs[i][j].type = pleine; break;
				case bloquante : grilleDeValeurs[i][j].type = bloquante; break;
			}
		}
	}

	//nombre de tours
	fscanf(f, "%i", nbTours);

	//couleur du dernier joueur à avoir joué
	fscanf(f, "%i", &valeur);

	switch(valeur) {
		case rouge: pion->couleur = rouge; break;
		case jaune: pion->couleur = jaune; break;
	}

	fclose(f);
}



/**
 * \fn void supprimerPartie()
 * \brief Supprime la partie sauvegardée dans le fichier "partie.txt", car la partie est finie
 */
void supprimerPartie() {

	FILE* f;
	f = fopen("partie.txt", "w");
	fclose(f);
	//Fonction remove
}



/**
 * \fn void decrementer_pion_special( t_couleur couleur, t_type type )
 * \brief Décrémente le compteur de pion spécial quand un pion spécial est joué
 * \param pion le dernier pion à avoir été joué
 * \return 1 si le pion peut être joué (le joueur possède encore de ce type de pion), 0 s'il n'en possède plus aucun
 */
int decrementer_pion_special( t_pion pion ) {

	if( pion.couleur == rouge ) {

		if( pion.type == creuse ) {
			if(cpt_rouge_creuse-- == 0)
				return(0);
		}
		else if( pion.type == bloquante){
				
			if(cpt_rouge_bloquante-- == 0)
				return(0);
		}
	}
	else if( pion.couleur == jaune) {

		if( pion.type == creuse ) {
			if(cpt_jaune_creuse-- == 0)
				return(0);
		}
		else if( pion.type == bloquante ){
			if(cpt_jaune_bloquante-- == 0)
				return(0);
		}
	}
	

	return(1);
}



/**
 * \fn int mode_creux()
 * \brief Lance une partie en mode creux
 */
int mode_creux() {

	// va être fusionné

	
	  int types;
	int c, nbTours=0;

	t_pion grilleDeValeurs[LIGNES][COLONNES], 
			pionJoueur;



	printf("Charger partie sauvegardée? (1= oui) : ");
	scanf("%i", &c);

	if(c != 0) {
		chargerPartie(grilleDeValeurs, &pionJoueur, &nbTours);
	}
	else {
		//joueur rouge commence
		pionJoueur.couleur = jaune;
		
		initGrille(grilleDeValeurs);
	}
	


	do {

		//afficherPions(renderer, grilleDeValeurs, coordonneesPions, images, arrierePlan);

		//alterne la couleur de pion du joueur
		pionJoueur.couleur = (pionJoueur.couleur == rouge ? jaune : rouge);


		do{
			
			printf("==== Tour des ");
			switch(pionJoueur.couleur) {
				case rouge: printf("rouges(X)"); break;
				case jaune: printf("jaunes(O)"); break;
				default : printf("Impossible de voir ce message\n");
			}
			printf(" ====\n");
			
			printf("Placer un pion dans quelle colonne? : ");
			scanf("%i", &c);
			
			

			do{
				printf("De quel type ? \n");
  			  printf("1 : creuse\n");
				printf("2 : pleine\n");
  			  printf("3 : bloquante\n");
 			  	scanf("%i", &types);
  			  if(types == 1){
  			  	pionJoueur.type = creuse;
  			  	
  			  	// Mets à jour le nombre de pièces spéciales
  			  	if (pionJoueur.couleur == rouge && cpt_rouge_creuse != 0){
  			  		cpt_rouge_creuse--;
  			  	}else if(pionJoueur.couleur == jaune && cpt_jaune_creuse != 0){
  			  		cpt_jaune_creuse--;
  			  	}else{
  			  		printf("Vous n'avez plus de pièce creuse \n");
  			  		types = -1;
  			  	}
  			  }
  			  else if(types == 2){
  			  	pionJoueur.type = pleine;
  			  }
  			  else if(types == 3){
  			  	pionJoueur.type = bloquante;

  			  	// Mets à jour le nombre de pièces spéciales
  			  	if (pionJoueur.couleur == rouge && cpt_rouge_bloquante != 0){
  			  		cpt_rouge_bloquante--;
  			  	}else if(pionJoueur.couleur == jaune && cpt_jaune_bloquante != 0){
  			  		cpt_jaune_bloquante--;
  			  	}else{
  			  		printf("Vous n'avez plus de pièce bloquante \n");
  			  		types = -1;
  			  	}
  			  }
  			  else{
  			  	printf("Erreur lors de la saisie veuillez ressaisir \n");
  			  	
  			  } 
			}while(types <1 ||types > 3);
			
			
				
		}while(ajoutPion(grilleDeValeurs, c-1, pionJoueur));

		nbTours++;
		

		sauvegardeAuto(grilleDeValeurs, pionJoueur, nbTours);


	//la partie s'arrête quand il y a un 4 à la suite, ou quand les 42 pions ont été joués (tour n°42)
	}while(!estQuatreALaSuite(grilleDeValeurs, c-1, pionJoueur) 
		&& nbTours < (LIGNES*COLONNES));



	//fin de partie
	//afficherPions(renderer, grilleDeValeurs, coordonneesPions, images, arrierePlan);
	

	if(nbTours == (LIGNES*COLONNES)) {
		printf("match nul\n");
	}
	else {
		printf("les ");
		switch(pionJoueur.couleur) {
				case rouge: printf("rouges(X)"); break;
				case jaune: printf("jaunes(O)"); break;
				default : printf("Impossible de voir ce message\n");
			}
		printf(" ont gagnés\n\n");
	}

	supprimerPartie();
		cpt_rouge_creuse = NB_CREUSE;
		cpt_rouge_bloquante = NB_BLOQUANTE;
		cpt_jaune_creuse = NB_CREUSE;
		cpt_jaune_bloquante = NB_BLOQUANTE;
	return 0;
}



/**
 * \fn int demarrer_partie(SDL_Window* pWindow, SDL_Renderer *renderer)
 * \brief Lance une partie en mode normal
 * \param pWindow pointeur de SDL_Window, pour récupérer les dimensions de la fenêtre
 * \param renderer pointeur de SDL_Renderer, nécessaire pour les fonctions SDL d'affichage
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int demarrer_partie( SDL_Window* pWindow, SDL_Renderer* renderer, t_partie typeDePartie ) {

	// variables sdl

	images_t images;
	SDL_Surface *surface = NULL;

	// variables de couleur
	SDL_Color	noir = {0, 0, 0, 255}, 
				blanc = {255, 255, 255, 255}, 
				cyan = {0, 255, 255, 255}, 
				arrierePlan = noir; // couleur d'arrière-plan de la fenêtre

	SDL_Rect	damier[LIGNES*COLONNES], // rectangles qui forment la grille (visuel)
				coordonneesPions[LIGNES][COLONNES]; //coordonnées où insérer les images des pions
	
	SDL_Event event;
	SDL_bool	quit = SDL_FALSE, // variable pour quitter la boucle d'évènement (fermer le programme)
				play = SDL_FALSE; // vrai quand un joueur a joué (cliqué)


	int largeurWindow, 
		hauteurWindow, 
		largeurRectGrille=51, // largeur des rectangles (carrés) qui composent la grille à afficher (à définir dynamiquement)
		offsetGrilleX=100, // décalage du point en haut à gauche de la grille à afficher, sur l'axe horizontal (à définir dynamiquement)
		offsetGrilleY=50, // décalage du point en haut à gauche de la grille à afficher, sur l'axe vertical (à définir dynamiquement)
		
		colonneCliquee, 
		nbTours=0, 
		restePionSpecial=1;

	t_pion	grilleDeValeurs[LIGNES][COLONNES], // représentation de la grille de jeu dans le code (pour les fonctions) avec la structure t_pion
			pionJoueur;


	// * récupérer les dimension de la fenêtre, pour ensuite créer la grille dynamiquement
	SDL_GetWindowSize(pWindow, &largeurWindow, &hauteurWindow);

	// TODO fonction qui, d'après les dimensions de la fênetre, calcule les valeurs de largeurRectGrille, offsetGrilleX et offsetGrilleY
	dimensionGrilleDynamique(	largeurWindow, hauteurWindow, 
								&largeurRectGrille, &offsetGrilleX, &offsetGrilleY);


	// * initialisations

	initDamier( damier, renderer, 
				largeurRectGrille, offsetGrilleX, offsetGrilleY );

	initCoordonneesPions(   coordonneesPions, 
							largeurRectGrille, offsetGrilleX, offsetGrilleY);

	initStructTexturesNormal( renderer, &images );
	


	// arrière-plan de la fenêtre
	setDrawColor(renderer, arrierePlan);
	SDL_RenderClear(renderer);
	//SDL_RenderPresent(renderer); // met à jour les dessins du Renderer sur l'écran


/*
	// demande de charger une partie
	printf("Charger partie sauvegardée? (1= oui) : ");
	scanf("%i", &colonneCliquee);

	if(colonneCliquee != 0) {
		chargerPartie(grilleDeValeurs, &pionJoueur, &nbTours);
	}
	else {*/
		// * joueur rouge commence
		pionJoueur.couleur = jaune;
		
		initGrille(grilleDeValeurs);
	//}



	afficherDamier( renderer, damier, cyan );


	do {

		afficherPions(renderer, grilleDeValeurs, coordonneesPions, &images, arrierePlan);
		SDL_RenderPresent(renderer); // met à jour les dessins du Renderer sur l'écran

		// * alterne la couleur de pion du joueur
		pionJoueur.couleur = (pionJoueur.couleur == rouge ? jaune : rouge);
		//pionJoueur.type = 2 ;// En mode normal, on ne joue que des pièces pleines




		// * Boucle d'attente d'action d'utilisateur
		while(!quit && !play)
		{
			// * Gestion_Évènements
			SDL_WaitEventTimeout(&event, 200);

			// * Analyse_Évènements
			if(event.type == SDL_QUIT) {
				quit = SDL_TRUE;
				goto Quit;
			}
			else if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
				// * la fenêtre a été redimensionnée

				//printf("event.window.data1 = %d\nevent.window.data2 = %d",event.window.data1,event.window.data2);

				// * recalculer les dimensions de la grille
				dimensionGrilleDynamique( event.window.data1, event.window.data2, &largeurRectGrille, &offsetGrilleX, &offsetGrilleY);

				// * réinitialiser les valeurs de la grille dans le damier
				initDamier( damier, renderer, 
				largeurRectGrille, offsetGrilleX, offsetGrilleY );

				initCoordonneesPions(   coordonneesPions, 
							largeurRectGrille, offsetGrilleX, offsetGrilleY);

				
				// * réafficher arrière-plan de la fenêtre
				setDrawColor(renderer, arrierePlan);
				SDL_RenderClear(renderer);
				// * réafficher damier
				afficherDamier( renderer, damier, cyan );
				// * réafficher les pions
				afficherPions(renderer, grilleDeValeurs, coordonneesPions, &images, arrierePlan);


				SDL_RenderPresent(renderer); // met à jour les dessins du Renderer sur l'écran
			}
			else if(event.button.type == SDL_MOUSEBUTTONDOWN)
			{
				while( event.button.type != SDL_MOUSEBUTTONUP)
				{
					// * attendre que le clic soit relaché
					SDL_WaitEvent(&event);
				} 

				colonneCliquee = -1;
				colonneCliquee = getColonneClick( damier, largeurRectGrille, event.button.x );
				//printf("colonneCliquee = %d\n", colonneCliquee);

				if(event.button.button == SDL_BUTTON_LEFT) {
					//printf("clic gauche\n");

					// * click gauche = pion plein
					pionJoueur.type = pleine;
				}
				else if(typeDePartie == modeCreux
					&&	event.button.button == SDL_BUTTON_RIGHT) {
					//printf("clic droit\n");

					// * click droit = pion creux
					pionJoueur.type = creuse;

					// * vérifier si le joueur possède encore le pion qu'il veut jouer
				}
				else if(typeDePartie == modeCreux
					&&	event.button.button == SDL_BUTTON_MIDDLE) {
					//printf("clic molette\n");

					// * click molette = pion bloquant
					pionJoueur.type = bloquante;
				}

				restePionSpecial = decrementer_pion_special(pionJoueur);

				if( colonneCliquee != -1	// * si le joueur a bien cliqué dans la grille
				&&	!estPleine(grilleDeValeurs, colonneCliquee-1)	// * si la colonne cliquée n'est pas déjà pleine
				&&	restePionSpecial )	// * si le joueur possède encore le pion qu'il veut jouer
				{
					// * le coup est bon et peut être joué
					play = SDL_TRUE;
				}
				
				if( restePionSpecial == 0 ) {
					printf("Vous n'avez plus de pion ");
					if(pionJoueur.type == creuse) 
					{
						printf("creux\n");
					}
					else //if(pionJoueur.type == bloquant) 
					{
						printf("bloquant\n");
					}
				}
			}
			//SDL_Delay(50); // petite pause, pour les performances

		}
		// Fin Boucle
		play = SDL_FALSE;


		if(!quit) {
			
			ajoutPion(grilleDeValeurs, colonneCliquee-1, pionJoueur);

			nbTours++;
		}

		//sauvegardeAuto(grilleDeValeurs, pionJoueur, nbTours);


		// * la partie s'arrête quand il y a un 4 à la suite, 
		// * quand les 42 pions ont été joués (tour n°42), 
		// * ou quand la fenêtre se ferme
	}while(!quit
		&& !estQuatreALaSuite(grilleDeValeurs, colonneCliquee-1, pionJoueur) 
		&& nbTours < (LIGNES*COLONNES));



	// * fin de partie
	//afficherPions(renderer, grilleDeValeurs, coordonneesPions, images, arrierePlan);
	
	if(!quit) {
		if(nbTours == (LIGNES*COLONNES)) {
			// * quand match nul
			printf("match nul\n");
		}
		else {
			// * quand un gagnant
			printf("les ");
			switch(pionJoueur.couleur) {
					case rouge: printf("rouges(X)"); break;
					case jaune: printf("jaunes(O)"); break;
					default : printf("Impossible de voir ce message\n");
				}
			printf(" ont gagnés\n\n");
		}

		//supprimerPartie();
		cpt_rouge_creuse = NB_CREUSE;
		cpt_rouge_bloquante = NB_BLOQUANTE;
		cpt_jaune_creuse = NB_CREUSE;
		cpt_jaune_bloquante = NB_BLOQUANTE;
	}

	


// * Quitter
Quit:
	freeLesImages(&images);

	if(surface) {
		SDL_FreeSurface(surface);
	}
	//if(format) {
		//SDL_FreeFormat(format);
	//}


	return 0;
}
