#include <stdio.h>
#include "src/fonc.h"
//#include <stdlib.h>

/**
 * \file puissance4.c
 * \brief tp de L1 de puissance4
 * \date {9/02/2023}
*/




int main() {

    int c, 
        nbTours=1;

    t_pion grille[LIGNES][COLONNES], 
            couleur;



    printf("Charger partie sauvegardée? (1= oui) : ");
    scanf("%i", &c);

    if(c != 0) {
        chargerPartie(grille, &couleur, &nbTours);
    }
    else {
        //joueur rouge commence
        couleur = jaune;
        
        initGrille(grille);
    }



    do {

        afficherGrille(grille);

        //alterne la couleur de pion du joueur
        couleur = (couleur == rouge ? jaune : rouge);


        do{
            printf("==== Tour des ");
            switch(couleur) {
                case rouge: printf("rouges(X)"); break;
                case jaune: printf("jaunes(O)"); break;
            }
            printf(" ====\n");

            printf("Placer un pion dans quelle colonne? : ");
            scanf("%i", &c);

        }while(ajoutPion(grille, c-1, couleur));


        sauvegardeAuto(grille, couleur, nbTours);


        nbTours++;

    //la partie s'arrête quand il y a un 4 à la suite, ou quand les 42 pions ont été joués (tour n°42)
    }while(!estQuatreALaSuite(grille, c-1, couleur) 
        && nbTours <= (LIGNES*COLONNES));



    //fin de partie
    afficherGrille(grille);

    if(nbTours == (LIGNES*COLONNES)) {
        printf("match nul\n");
    }
    else {
        printf("les ");
        switch(couleur) {
                case rouge: printf("rouges(X)"); break;
                case jaune: printf("jaunes(O)"); break;
            }
        printf(" ont gagnés\n\n");
    }

    supprimerPartie();

    return 0;
}
