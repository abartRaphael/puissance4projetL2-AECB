#include "../lib/fonc_ordi.h"
#include "../lib/fonc2.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



/**
 * \fn int coupPossibleHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur) 
 * \brief vérifie si l'ordinateur à la possibilité de gagner horizontalement 
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la suite possible, sinon retourne le nombre de pion à la suite
 */
int coupPossibleHorizontalOrdi(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur) {

    int pionsALaSuite=0;


    //parcourir la ligne où le dernier pion a été joué
    for(int i=0 ; i<COLONNES ; i++) {

    	if(grille[l][i].couleur == couleur || grille[l][i].couleur == rougejaune ) {
               pionsALaSuite++;
      }else if(i == c){
         pionsALaSuite++;
      }else {
                pionsALaSuite = 0;
      }

      if(pionsALaSuite > 3) {
          return pionsALaSuite;
      }
    }

	return pionsALaSuite;
}

/**
 * \fn int coupPossibleVerticalOrdi(t_pion grille[LIGNES][COLONNES], int c, t_couleur couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner verticalement 
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, sinon retourne le nombre de pion à la suite
 */
int coupPossibleVerticalOrdi(t_pion grille[LIGNES][COLONNES], int c, int l,t_couleur couleur) {

    int pionsALaSuite=0;

    //parcourir la colonne où le dernier pion a été joué
    for(int i=0 ; i<LIGNES ; i++) {

        if(grille[i][c].couleur == couleur || grille[i][c].couleur == rougejaune) {
            pionsALaSuite++;
        }else if(i == l){
        	pionsALaSuite++;
        }else {
          pionsALaSuite = 0;
        }

        if(pionsALaSuite > 3) {
            return pionsALaSuite;
        }
    }
    
    return pionsALaSuite;
}

/**
 * \fn int coupPossibleDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner sur la même DIAGONALE, en partant de la gauche/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, sinon retourne le nombre de pion à la suite
 */
int coupPossibleDiagonale1Ordi(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur) {

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
        return -1;
    }


    //parcourir la diagonale où le dernier pion a été joué
    while(x < COLONNES && y < LIGNES) {

        if(grille[y][x].couleur == couleur || grille[y][x].couleur == rougejaune) {
            pionsALaSuite++;
        }
        else if(y == l){
        	pionsALaSuite++;
        }else {
            pionsALaSuite = 0;
        }

        x++;
        y++;

        if(pionsALaSuite > 3) {
            return pionsALaSuite;
        }
    }

    return pionsALaSuite;
}

/**
 * \fn int coupPossibleDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner sur la même DIAGONALE, en partant de la droite/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, sinon retourne le nombre de pion à la suite
 */
int coupPossibleDiagonale2Ordi(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur){
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
        return -1;
    }


    //parcourir la diagonale où le dernier pion a été joué
    while(x >= 0 && y < LIGNES) {

        if(grille[y][x].couleur == couleur || grille[y][x].couleur == rougejaune) {
            pionsALaSuite++;
        }else if(y == l){
        	pionsALaSuite++;
        }
        else {
            pionsALaSuite = 0;
        }

        x--;
        y++;

        if(pionsALaSuite > 3) {
            return pionsALaSuite;
        }
    }

    return pionsALaSuite;
}



/**
 * \fn int coupPossibleOrdi(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief appelle les quatre fonctions pour vérifier s'il y a un puissance 4 possible pour l'ordinateur
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, sinon retourne le nombre de pion à la suite
 */
int coupPossibleOrdi(t_pion grille[LIGNES][COLONNES], int c, int l,t_couleur couleur) {
    int coups;
    int tab[N];
    coups = coupPossibleHorizontalOrdi(grille, c, l, couleur);
    if(coups == 4 ) return coups;
    tab[0] = coups;
    coups = coupPossibleVerticalOrdi(grille, c, l,couleur);
    if(coups == 4) return coups;
    tab[1] = coups;
    coups = coupPossibleDiagonale1Ordi(grille, c, l, couleur);
    if(coups == 4) return coups;
    tab[2] = coups;
    coups = coupPossibleDiagonale2Ordi(grille, c, l, couleur);
    if(coups == 4) return coups;
    tab[3] = coups;
    
    return max(tab, N);
}





/**
 * \fn int max_possible(int tab[], int taille, int *ind)
 * \brief cherche le maximum d'un tableau 
 * \param tab le tableau
 * \param ind l'indice ou se situe le max
 * \return renvoie le maximum du tableau
 * \return renvoie l'indice du maximum dans la variable ind
 */
int max_possible(int tab[N], int *ind){
	int i = 0;
	int max = -1;
	(*ind) = tab[0];
	for(i = 0; i < N; i++){
		if(tab[i] > max){
			max = tab[i];
			(*ind) = i;
		}
	}
	return max;
}


/**
 * \fn int copie_grille(t_pion grille_src[LIGNES][COLONNES],t_pion grille_dest[LIGNES][COLONNES])
 * \brief copie un tableau dans un autre 
 * \param grille_src la grille source
 * \param grille_dest la grille destination
 * \return renvoie 0 si tout c'est bien passé
 */
int copie_grille(t_pion grille_src[LIGNES][COLONNES],t_pion grille_dest[LIGNES][COLONNES]){
	int i = 0, j= 0;
	
	for(i = 0; i < LIGNES; i++){
		for(j = 0; j < COLONNES; j++){
			grille_dest[i][j] = grille_src[i][j];
		}
	}
	return 0;
}


/**
 * \fn int coup_gagnant(t_pion grille[LIGNES][COLONNES], t_pion ordi, int *col)
 * \brief vérifie si un coup gagnant est faisable
 * \param grille la grille de jeu
 * \param ordi le pion du joueur courant
 * \param col la colonne à jouer
 * \return renvoie 1 si un coup gagnant est possible 0 sinon
 */
int coup_gagnant(t_pion grille[LIGNES][COLONNES], t_pion ordi, int *col){
	int i = 0;
	int coup,l;
	for(i=0;i< NB_COUPS;i++){
		l = caseLibre(grille, i);
		if (l != -1){
			coup = coupPossibleOrdi(grille, i, l, ordi.couleur);
			if(coup == 4){
				*col = i;
				return 1;
			}
		}
	}
	return 0;
}

/**
 * \fn int max_possible(int tab[], int taille)
 * \brief cherche le maximum d'un tableau 
 * \param tab le tableau
 * \param taille La taille du tableau
 * \return renvoie le maximum du tableau
 */
int max(int tab[], int taille){
	int i = 0;
	int max = -7;
	for(i = 0; i < taille; i++){
		if(tab[i] > max){
			max = tab[i];
		}
		
	}
	return max;
}


/**
 * \fn int min(int tab[], int taille)
 * \brief cherche le minimum d'un tableau
 * \param tab le tableau de valeur à comparer
 * \param taille La taille du tableau
 * \return la valeur mini
 */
int min(int tab[], int taille){
	int i = 0;
	int mini = 7;//Valeur arbitraire
	for(i = 0; i <taille; i++){
		mini = tab[i] < mini ? tab[i] :mini;
	}
	return mini;
}

/**
 * \fn int ordi(t_pion jeu, t_pion adversaire)
 * \brief 
 * \param jeu la grille de jeu
 * \param adversaire le joueur courant
 * \param avance le nombre de tour d'avance
 * \return soit 1 si un coup est possible soit le maximum des coups possible
 */
int tour_ordi(t_pion jeu[LIGNES][COLONNES], t_pion adversaire, int avance){
	if(avance == 0){
		return 0;
	}
	int C[NB_COUPS];
	int i;
	t_pion copie[LIGNES][COLONNES] ;  
	if(coup_gagnant(jeu, adversaire, &i)){
		return 1;
	}else{
		for(i = 0; i< NB_COUPS; i++){
			copie_grille(jeu, copie);//On copie la grille de jeu
			
			if(caseLibre(copie,i) != -1){//Verifie que la colonne est disponible
				ajoutPion(copie,i,adversaire);
				if(adversaire.couleur == jaune){ //Change la couleur en fonction de la couleur du joueur
					adversaire.couleur = rouge;
					C[i] = tour_joueur(copie, adversaire,avance-1);
				}else{
					adversaire.couleur = jaune;
					C[i] = tour_joueur(copie,adversaire,avance-1);
				}
			}else{
				C[i] = 0;
			}
		}
	}
	return max(C,NB_COUPS);
}

/**
 * \fn int ordi(t_pion jeu, t_pion adversaire)
 * \brief 
 * \param jeu la grille de jeu
 * \param joeur le joueur courant
 * \param avance le nombre de tour d'avance qui doit être rechercher
 * \return soit 1 si un coup est possible soit le minimum des coups possible
 */
int tour_joueur(t_pion jeu[LIGNES][COLONNES], t_pion joueur,int avance){
	if(avance == 0){
		return 0;
	}
	int C[NB_COUPS];
	int i;
	t_pion copie[LIGNES][COLONNES] ;
	if(coup_gagnant(jeu, joueur, &i)){
		return -1;
	}else{
		for(i = 0; i < NB_COUPS; i++){
			copie_grille(jeu, copie);//On copie la grille de jeu
			if(caseLibre(copie,i) != -1){
				ajoutPion(copie,i,joueur);
				if(joueur.couleur == jaune){
					joueur.couleur = rouge;
					C[i] = tour_ordi(copie,joueur,avance-1);
				}else{
					joueur.couleur = jaune;
					C[i] = tour_ordi(copie,joueur,avance-1);
				}
			}else{
					C[i] = 0;
			}
		}
	}
	return min(C, NB_COUPS);
}

/**
 * \fn tour_principal_ordi(t_pion grille[LIGNES][COLONNES], t_pion ordi,int avance)
 * \brief Joue le tour de l'ordinateur 
 * \param	grille la grille de jeu
 * \param ordi le pion de l'ordinateur
 * \param avance le nombre de tour d'avance qui doit être rechercher
 * \return retourne la colonne qui a été joué
 */
int tour_principal_ordi(t_pion grille[LIGNES][COLONNES], t_pion ordi,int avance){
	int C[NB_COUPS];
	int i;
	t_pion copie[LIGNES][COLONNES] ;
	if(coup_gagnant(grille, ordi, &i)){
		ajoutPion(grille,i, ordi);
		return i;
	}else{
		for(i = 0; i <NB_COUPS; i++){
			copie_grille(grille,copie); //On copie la grille du jeu
			if(caseLibre(copie,i) != -1){
				ajoutPion(copie,i,ordi);
				if(ordi.couleur == jaune){
					ordi.couleur = rouge;
					C[i] = tour_joueur(copie, ordi,avance);
					ordi.couleur = jaune;
				}else{
					ordi.couleur = jaune;
					C[i] = tour_joueur(copie, ordi,avance);
					ordi.couleur = rouge;
				}
			}else{
				C[i] = 0;
			}
		}
		if(existe(C,1, &i)){
			ajoutPion(grille,i, ordi);
		}else{
			do{
				i = rand()%NB_COUPS+1;
			}while(caseLibre(grille,i) == -1);
					ajoutPion(grille,i,ordi);
		}
		return i;
	}

}

/**
 * \fn existe(int C[NB_COUPS], int recherche, int *ind)
 * \brief Vérifie si recherche existe dans le tableau C
 * \param C le tableau
 * \param recherche la valeur à rechercher
 * \param ind l'indice ou se trouve la valeur à rechercher
 * \return retourne 1 si la valeur est trouvé, 0 sinon
 */
int existe(int C[NB_COUPS], int recherche, int *ind){
	int i = 0;
	for(i = 0; i < NB_COUPS; i++){
		if(C[i] == recherche){
			*ind = i;
			return 1;
		}
	}
	return 0;
}


/**
 * \fn contre_ordinateur()
 * \brief lance une partie contre l'ordinateur
 * \param Aucun parametre
 * \return retourne 0 si tout c'est bien passé
 */
int contre_ordinateur(){	
	int c, nbTours=0,victoire = 0;
	char choix; /*Choix de la couleur*/
  t_pion grille[LIGNES][COLONNES];
  t_pion Joueur, Ordi;

	srand(time(NULL));
	initGrille(grille);
	
	printf("Quelle couleur souhaitez-vous ? (r pour rouge) (j pour jaune) : ");
	scanf("%c", &choix);
	
	if( choix == 'r'){
		Joueur.couleur = rouge;
		Ordi.couleur = jaune;
	}else{
		Joueur.couleur = jaune;
		Ordi.couleur = rouge;
	}
	/*Le mode normal ne contient que des pièces pleines*/
	Joueur.type = 2;
	Ordi.type = 2;
	
	do{
	  do{
	  	printf("Placer un pion dans quelle colonne? : ");
	    scanf("%i", &c);
	  }while(ajoutPion(grille, c-1, Joueur));
	  	afficherGrille(grille);
	  	
	  	if(estQuatreALaSuite(grille, c-1,Joueur)){
	  		printf("Vous avez gagné\n");
	  		victoire = 1;
	  	}else{
	  		
	  		printf("--------- Tour de L'adversaire --------\n");
	  		
	  		
				c = tour_principal_ordi(grille, Ordi,TOUR_RECHERCHE);//L'ordi joue et on récupère la colonne jouée
				
				if(estQuatreALaSuite(grille, c,Ordi)){
					printf("L'adversaire a gagné\n");
					victoire = 1;
				}
			}
			afficherGrille(grille);
			nbTours += 2;
		
	}while(!victoire && nbTours !=LIGNES*COLONNES);
	
	if (!victoire){
		printf("Match Nul\n");
	}
            
  return 0;
}


