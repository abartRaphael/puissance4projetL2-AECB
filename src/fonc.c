#include "../lib/fonc.h"
#include <stdio.h>

/**
 * \fn void initGrille(t_pion grille[LIGNES][COLONNES])
 * \brief Remplit toutes les cases de la grille de puissance 4 avec la valeur "vide"
 * \param grille grille de puissance 4
 */
void initGrille(t_pion grille[LIGNES][COLONNES]) {

    for(int i=0 ; i<LIGNES ; i++) {
        for(int j=0 ; j<COLONNES ; j++) {

            grille[i][j] = vide;
        }
    }
}

/**
 * \fn int estPleine(t_pion grille[LIGNES][COLONNES], int c)
 * \brief Permet de savoir si une colonne est pleine, et donc on ne peut plus y ajouter de pions
 * \param grille grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \return retourne 1 si on ne peut plus ajouter de pions à cette colonne, 0 sinon
 */
int estPleine(t_pion grille[LIGNES][COLONNES], int c) {

    if(grille[0][c] == vide) {
        return 0;
    }
    else {
        return 1;
    }
}

/**
 * \fn int caseLibre(t_pion grille[LIGNES][COLONNES], int c)
 * \brief Permet de savoir quelle case d'une colonne donnée est vide, et la plus basse
 * \param grille grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \return retourne l'indice de la ligne où la case est vide, ou -1 si la colonne est pleine
 */
int caseLibre(t_pion grille[LIGNES][COLONNES], int c) {

    //l commence à "LIGNES-1", qui est la ligne la plus basse
    int l=LIGNES-1;
    
    if(!estPleine(grille, c)) {

        while(grille[l][c] != vide) {
            //quand il y a un pion dans la case, on fait remonter l
            l--;
        }

        return l;
    }

    return -1;
}

/**
 * \fn int ajoutPion(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief Permet d'ajouter un pion à la grille de jeu
 * \param grille grille de puissance 4
 * \param c indice de la colonne à vérifier
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 0 si le pion est bien ajouté à la grille, 1 sinon, avec un message d'erreur
 */
int ajoutPion(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur){

    int l;

    //test pour voir si la valeur entrée est dans le bon intervale
    if(c >= COLONNES || c < 0) {
        return 1;
    }

    l = caseLibre(grille, c);

    if(l != -1) {

        grille[l][c] = couleur;
        return 0;
    }

    printf("Cette colonne est pleine, recommencez\n");
    return 1;
}

/**
 * \fn int quatreALaSuiteHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur) 
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même LIGNE
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteHorizontal(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur) {

    int pionsALaSuite=0;

    //est-ce que le pion du centre est de la même couleur que celle du joueur qui a joué, déjà
    if(grille[l][3] == couleur) {

        //parcourir la ligne où le dernier pion a été joué
        for(int i=0 ; i<COLONNES ; i++) {

            if(grille[l][i] == couleur) {
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
 * \fn int quatreALaSuiteVertical(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même COLONNE
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteVertical(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur) {

    int pionsALaSuite=0;

    //parcourir la ligne où le dernier pion a été joué
    for(int i=0 ; i<LIGNES ; i++) {

        if(grille[i][c] == couleur) {
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
 * \fn int quatreALaSuiteDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la gauche/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale1(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur) {

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

        if(grille[y][x] == couleur) {
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
 * \fn int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur)
 * \brief vérifie si 4 pions de même couleur ou plus se trouvent sur la même DIAGONALE, en partant de la droite/haut
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param l indice de la ligne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int quatreALaSuiteDiagonale2(t_pion grille[LIGNES][COLONNES], int c, int l, t_pion couleur) {

    int pionsALaSuite=0, 
        x=c, 
        y=l;

    printf("x=%i\ny=%i\n", x, y);

    //décaler les "coordonnées" jusqu'à atteindre le bord (droit ou haut) de la grille
    while(x < COLONNES && y > 0) {
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

        if(grille[y][x] == couleur) {
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
 * \fn int estQuatreALaSuite(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur)
 * \brief appelle les quatre fonctions pour vérifier s'il y a un 4 à la suite après le dernier coup joué
 * \param grille grille de puissance 4
 * \param c indice de la colonne où le joueur à joué
 * \param couleur la couleur du pion du joueur qui le joue (rouge/jaune)
 * \return retourne 1 s'il y a un 4 la la suite, 0 sinon
 */
int estQuatreALaSuite(t_pion grille[LIGNES][COLONNES], int c, t_pion couleur) {

    int l;//ligne où se trouve le dernier pion joué

    if(caseLibre(grille, c) != -1) {
        l = caseLibre(grille, c) + 1;
    }
    else {
        l = 0;
    }


    return quatreALaSuiteHorizontal(grille, c, l, couleur)
    || quatreALaSuiteVertical(grille, c, couleur)
    || quatreALaSuiteDiagonale1(grille, c, l, couleur)
    || quatreALaSuiteDiagonale2(grille, c, l, couleur);
}



/**
 * \fn void afficherGrille(t_pion grille[LIGNES][COLONNES])
 * \brief Affiche la grille de jeu
 * \param grille grille de puissance 4
 */
void afficherGrille(t_pion grille[LIGNES][COLONNES]) {

    printf("-----------------------------\n");

    for(int i=0 ; i<LIGNES ; i++) {

        printf("| ");

        for(int j=0 ; j<COLONNES ; j++) {

            if(grille[i][j] == rouge) {
                printf("X");
            }
            else if(grille[i][j] == jaune) {
                printf("O");
            }
            else {
                printf(" ");
            }

            printf(" | ");
        }

        printf("\n-----------------------------\n");
    }
}



/**
 * \fn void sauvegardeAuto(t_pion grille[LIGNES][COLONNES], t_pion couleur, int nbTours)
 * \brief Sauvegarde la configuration de la partie actuelle
 * \param grille grille de puissance 4
 * \param couleur couleur du dernier joueur à avoir joué
 * \param nbTours nombre de tours effectués
 */
void sauvegardeAuto(t_pion grille[LIGNES][COLONNES], t_pion couleur, int nbTours) {

    FILE* f;
    f = fopen("partie.txt", "w");

    //grille de jeu
    for(int i=0 ; i<LIGNES ; i++) {
        for(int j=0 ; j<COLONNES ; j++) {

            fprintf(f, "%i ", grille[i][j]);
        }
        fprintf(f, "\n");
    }

    //nombre de tours
    fprintf(f, "%i\n", nbTours);

    //couleur du dernier joueur à avoir joué
    fprintf(f, "%i\n", couleur);

    fclose(f);
}



/**
 * \fn void chargerPartie(t_pion grille[LIGNES][COLONNES], t_pion* couleur, int* nbTours)
 * \brief Charge la configuration de la partie sauvegardée dans le fichier "partie.txt"
 * \param grille grille de puissance 4
 * \param couleur couleur du dernier joueur à avoir joué
 * \param nbTours nombre de tours effectués
 */
void chargerPartie(t_pion grille[LIGNES][COLONNES], t_pion* couleur, int* nbTours) {

    int valeur;//placeholder

    FILE* f;
    f = fopen("partie.txt", "r");

    //grille de jeu
    for(int i=0 ; i<LIGNES ; i++) {
        for(int j=0 ; j<COLONNES ; j++) {

            fscanf(f, "%i", &valeur);

            switch(valeur) {
                case vide: grille[i][j] = vide; break;
                case rouge: grille[i][j] = rouge; break;
                case jaune: grille[i][j] = jaune; break;
            }
        }
    }

    //nombre de tours
    fscanf(f, "%i", nbTours);

    //couleur du dernier joueur à avoir joué
    fscanf(f, "%i", &valeur);

    switch(valeur) {
        case rouge: *couleur = rouge; break;
        case jaune: *couleur = jaune; break;
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
}

