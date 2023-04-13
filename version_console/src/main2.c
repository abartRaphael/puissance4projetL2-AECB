
#include <stdio.h>
#include "../lib/fonc2.h"
#include "../lib/fonc_ordi.h"
#include <stdlib.h>

/**
 * \file main2.c
 * \brief Projet Puissance4++
 * \version 0.1
 * \date {9/02/2023}
 * \author Abart Raphaël
 * \author ElGhoumari Soumia
 * \author Coupé Xavier
*/


int main(){
	int choix;
	
	printf("Quel mode :\n\t1 : Mode normal\n\t2 : Mode creux\n\t3 : Mode contre l'ordinateur\n");
	scanf("%i", &choix);
	if (choix == 1){
		mode_normal();
	}else if(choix == 2){
		mode_creux();
	}else{
		contre_ordinateur();
	}
	
	
	return 0;
}
