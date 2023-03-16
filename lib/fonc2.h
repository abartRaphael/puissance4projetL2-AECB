#ifndef H_FONC2_
#define H_FONC2_

#define LIGNES 6
#define COLONNES 7

#define NB_CREUSE 3
#define NB_BLOQUANTE 3


typedef enum{vide, rouge, jaune, rougejaune} t_couleur;
typedef enum{no_type, creuse , pleine,bloquante} t_type;

typedef struct{
	t_couleur couleur;
	t_type type;
}t_pion;





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
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur);

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
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur);

/**
 * \fn int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la droite/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur);

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
 * \fn void afficherGrille(t_pion grille[LIGNES][COLONNES])
 * \brief Affiche la grille de jeu
 * \param grille grille de puissance 4
 */
void afficherGrille(t_pion grille[LIGNES][COLONNES]);

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
 * \fn int mode_normal()
 * \brief Lance une partie en mode normal
 */
int mode_normal();


#endif /*H_FONC2_ */

