#ifndef H_FONC2_
#define H_FONC2_

#define LIGNES 6	//!< nombre de lignes de la grille de puissance 4 (par défaut 6)
#define COLONNES 7	//!< nombre de colonnes de la grille de puissance 4 (par défaut 7)

#define NB_CREUSE 3		//!< nombre de pièces creuses que chaque joueur peut utiliser
#define NB_BLOQUANTE 3	//!< nombre de pièces bloquantes que chaque joueur peut utiliser

// rougeJaune : pièce rouge creuse (extérieur) sur pièce jaune pleine (intérieur)
// jauneRouge : pièce jaune creuse (extérieur) sur pièce rouge pleine (intérieur)
typedef enum{
	vide, 		//!< case vide de la grille
	rouge, 		//!< pièce rouge
	jaune, 		//!< pièce jaune
	rougeJaune,	//!< pièce rouge creuse à l'extérieur, jaune à l'intérieur
	jauneRouge	//!< pièce jaune creuse à l'extérieur, rouge à l'intérieur
} t_couleur;
typedef enum{no_type, creuse, pleine, bloquante} t_type;

typedef enum{
	quitter=-1, 
	modeNormal=1, 	//!< pour une partie de puissance 4 classique (un seul type de pièce)
	modeCreux		//!< pour une partie de puissance 4 avec des pièces creuses et bloquantes
} t_partie;

/**
 * \struct t_pion fonc2.h 
 * \brief Objet représentant un pion/pièce du jeu
 * avec sa couleur
 */
typedef struct{
	t_couleur couleur;
	t_type type;
}t_pion;

/**
 * \file fonc2.h
 * \brief En-tête des fonctions
 * \version 0.1
 * \date {9/02/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/


#include <SDL2/SDL.h>


/**
 * \fn void initGrille(t_pion grille[LIGNES][COLONNES])
 * \brief Remplit toutes les cases de la grille de puissance 4 avec la valeur "vide"
 * \param grille grille de puissance 4
 */
void initGrille(t_pion grille[LIGNES][COLONNES]);

/**
 * \fn int estPleine(t_pion grille[LIGNES][COLONNES], int c)
 * \brief Permet de savoir si une colonne est pleine, et donc on ne peut plus y ajouter de pions
 * \param grille : grille de puissance 4
 * \param c : indice de la colonne à vérifier
 * \return retourne 1 si on ne peut plus ajouter de pions à cette colonne, 0 sinon
 */
int estPleine(t_pion grille[LIGNES][COLONNES], int c);

/**
 * \fn int caseLibre(t_pion grille[LIGNES][COLONNES], int c)
 * \brief Permet de savoir quelle case d'une colonne donnée est vide, et la plus basse
 * \param grille grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \return retourne l'indice de la ligne où la case est vide, ou -1 si la colonne est pleine
 */
int caseLibre(t_pion grille[LIGNES][COLONNES], int c);

/**
 * \fn int ajoutPion(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief Permet d'ajouter un pion à la grille de jeu
 * \param grille grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 0 si le pion est bien ajouté à la grille, 1 sinon, avec un message d'erreur
 */
int ajoutPion(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur);

/**
 * \fn int quatreALaSuiteHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur) 
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même LIGNE
 * \param grille grille de puissance 4
 * \param l indice de la ligne où le joueur à joué
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteHorizontal(t_pion grille[LIGNES][COLONNES], int l, int c, t_pion couleur);

/**
 * \fn int quatreALaSuiteVertical(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même COLONNE
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteVertical(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur);

/**
 * \fn int quatreALaSuiteDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la gauche/haut
 * \param grille grille de puissance 4
 * \param l indice de la ligne où le joueur à joué
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale1(t_pion grille[LIGNES][COLONNES], int l, int c, t_pion couleur);

/**
 * \fn int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la droite/haut
 * \param grille grille de puissance 4
 * \param l indice de la ligne où le joueur à joué
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int l, int c, t_pion couleur);

/**
 * \fn int estQuatreALaSuite(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief appelle les quatre fonctions pour vérifier s'il y a un 4 à la suite après le dernier coup joué
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int estQuatreALaSuite(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur);

/**
 * \fn void sauvegardeAuto(t_pion grille[LIGNES][COLONNES], t_pion couleur, int nbTours)
 * \brief Sauvegarde la configuration de la partie actuelle
 * \param grille grille de puissance 4
 * \param couleur couleur du dernier joueur à avoir joué
 * \param nbTours nombre de tours effectués
 */
void sauvegardeAuto(t_pion grille[LIGNES][COLONNES], t_pion couleur, int nbTours);

/**
 * \fn void chargerPartie(t_pion grille[LIGNES][COLONNES], t_pion* couleur, int* nbTours)
 * \brief Charge la configuration de la partie sauvegardée dans le fichier "partie.txt"
 * \param grille grille de puissance 4
 * \param couleur couleur du dernier joueur à avoir joué
 * \param nbTours nombre de tours effectués
 */
void chargerPartie(t_pion grille[LIGNES][COLONNES], t_pion* couleur, int* nbTours);

/**
 * \fn void supprimerPartie()
 * \brief Supprime la partie sauvegardée dans le fichier "partie.txt", car la partie est finie
 */
void supprimerPartie();

/**
 * \fn int mode_creux()
 * \brief Lance une partie en mode creux
 */
int mode_creux();

/**
 * \fn int demarrer_partie( SDL_Window* pWindow, SDL_Renderer *renderer, t_partie typeDePartie )
 * \brief Lance une partie de puissance 4 normale ou en mode creux
 * \param pWindow pointeur de SDL_Window, pour récupérer les dimensions de la fenêtre
 * \param renderer pointeur de SDL_Renderer, nécessaire pour les fonctions SDL d'affichage
 * \param typeDePartie type enum, vaut soit modeNormal (1), soit modeCreux (2)
 */
int demarrer_partie( SDL_Window* pWindow, SDL_Renderer *renderer, t_partie typeDePartie );

/**
 * \fn void decrementer_pion_special( t_couleur couleur, t_type type )
 * \brief Décrémente le compteur de pion spécial quand un pion spécial est joué
 * \param pion le dernier pion à avoir été joué
 * \return 1 si le pion peut être joué (le joueur possède encore de ce type de pion), 0 s'il n'en possède plus aucun
 */
int decrementer_pion_special( t_pion pion );



#endif /*H_FONC2_ */

