#ifndef H_FONCORDI_
#define H_FONCORDI_

#include "../lib/fonc2.h"
#define NB_COUPS 7
#define N 4
#define TOUR_RECHERCHE 7

/**
 * \fn int coupPossibleHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur) 
 * \brief vérifie si l'ordinateur à la possibilité de gagner horizontalement 
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite possible, -1 sinon
 */
int coupPossibleHorizontalOrdi(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur);

/**
 * \fn int coupPossibleVerticalOrdi(t_pion grille[LIGNES][COLONNES], int c, t_couleur couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner verticalement 
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur à joué
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, -1 sinon
 */
int coupPossibleVerticalOrdi(t_pion grille[LIGNES][COLONNES], int c, int l,t_couleur couleur);


/**
 * \fn int coupPossibleDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner sur la même DIAGONALE, en partant de la gauche/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur à joué
 * \param l indice de la ligne où l'ordinateur à joué
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, -1 sinon
 */
int coupPossibleDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur);


/**
 * \fn int coupPossibleDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si l'ordinateur à la possibilité de gagner sur la même DIAGONALE, en partant de la droite/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur à joué
 * \param l indice de la ligne où l'ordinateur à joué
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, -1 sinon
 */
int coupPossibleDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_couleur couleur);


/**
 * \fn int coupPossibleOrdi(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief appelle les quatre fonctions pour vérifier s'il y a un 4 possible pour l'ordinateur
 * \param grille grille de puissance 4
 * \param c indice de la colonne où l'ordinateur pourrait jouer
 * \param l indice de la ligne où l'ordinateur pourrait jouer
 * \param couleur la couleur du pion que l'ordinateur joue (rouge/jaune)
 * \return retourne la colonne à jouer s'il y a un 4 la suite, -1 sinon
 */
int coupPossibleOrdi(t_pion grille[LIGNES][COLONNES], int c, int l,t_couleur couleur);


/**
 * \fn int max_possible(int tab[], int taille, int *ind)
 * \brief cherche le maximum d'un tableau 
 * \param tab le tableau
 * \param ind l'indice ou se situe le max
 * \return renvoie le maximum du tableau
 * \return renvoie l'indice du maximum dans la variable ind
 */
int max_possible(int tab[N], int *ind);


/**
 * \fn int max_possible(int tab[], int taille)
 * \brief cherche le maximum d'un tableau 
 * \param tab le tableau
 * \param taille La taille du tableau
 * \return renvoie le maximum du tableau
 */
int max(int tab[], int taille);


/**
 * \fn int min(int tab[NB_COUPS])
 * \brief cherche le minimum d'un tableau
 * \param tab le tableau de valeur à comparer
 * \return la valeur mini
 */
int min(int tab[], int taille);

/**
 * \fn int ordi(t_pion jeu, t_pion adversaire)
 * \brief 
 * \param jeu la grille de jeu
 * \param joeur le joueur courant
 * \param avance le nombre de tour d'avance qui doit être rechercher
 * \return soit 1 si un coup est possible soit le minimum des coups possible
 */
int tour_joueur(t_pion jeu[LIGNES][COLONNES], t_pion joueur,int avance);

/**
 * \fn int ordi(t_pion jeu, t_pion adversaire)
 * \brief 
 * \param jeu la grille de jeu
 * \param adversaire le joueur courant
 * \param avance le nombre de tour d'avance
 * \return soit 1 si un coup est possible soit le maximum des coups possible
 */
int tour_ordi(t_pion jeu[LIGNES][COLONNES], t_pion adversaire, int avance);


/**
 * \fn tour_principal_ordi(t_pion grille[LIGNES][COLONNES], t_pion ordi,int avance)
 * \brief Joue le tour de l'ordinateur 
 * \param	grille la grille de jeu
 * \param ordi le pion de l'ordinateur
 * \param avance le nombre de tour d'avance qui doit être rechercher
 * \return retourne la colonne qui a été joué
 */
int tour_principal_ordi(t_pion grille[LIGNES][COLONNES], t_pion ordi,int avance);


 
 /**
 * \fn existe(int C[NB_COUPS], int recherche, int *ind)
 * \brief Vérifie si recherche existe dans le tableau C
 * \param C le tableau
 * \param recherche la valeur à rechercher
 * \param ind l'indice ou se trouve la valeur à rechercher
 * \return retourne 1 si la valeur est trouvé, 0 sinon
 */
int existe(int C[NB_COUPS], int recherche, int *ind);

/**
 * \fn contre_ordinateur()
 * \brief lance une partie contre l'ordinateur
 * \param Aucun parametre
 * \return retourne 0 si tout c'est bien passé
 */
int contre_ordinateur();

/**
 * \fn int copie_grille(t_pion grille_src[LIGNES][COLONNES],t_pion grille_dest[LIGNES][COLONNES])
 * \brief copie un tableau dans un autre 
 * \param grille_src la grille source
 * \param grille_dest la grille destination
 * \return renvoie 0 si tout c'est bien passé
 */
int copie_grille(t_pion grille_src[LIGNES][COLONNES],t_pion grille_dest[LIGNES][COLONNES]);

/**
 * \fn int coup_gagnant(t_pion grille[LIGNES][COLONNES], t_pion ordi, int *col)
 * \brief vérifie si un coup gagnant est faisable
 * \param grille la grille de jeu
 * \param ordi le pion du joueur courant
 * \param col la colonne à jouer
 * \return renvoie 1 si un coup gagnant est possible 0 sinon
 */
int coup_gagnant(t_pion grille[LIGNES][COLONNES], t_pion ordi, int *col);
#endif /*H_FONCORDI_ */



