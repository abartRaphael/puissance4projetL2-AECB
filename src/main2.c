#include <stdio.h>
#include "../lib/fonc.h"
#include <stdlib.h>

/**
 * \file puissance4.c
 * \brief tp de L1 de puissance4
 * \date {9/02/2023}
*/


int main(){
	int choix;
	
	printf("Quel mode :\n\t1 : Mode normal\n\t2 : Mode creux\n");
	scanf("%i", &choix);
	
	if (choix == 1){
		mode_normal();
	}else{
		mode_creux();
	}
	
	
	return 0;
}
