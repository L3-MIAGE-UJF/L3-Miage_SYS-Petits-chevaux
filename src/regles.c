#include <stdio.h>

#include "headers/jeu.h"

// calcul de la position du cheval selon les regles suivantes
// de l'ecurie (0) si le dé est à 6 on passe le cheval à la position de départ du joueur correspondant

int cest_mon_tour(int num_fils, struct_debuttour * debuttourlu) {
	return (debuttourlu->numerojoueur == num_fils) ? 1 : 0;
}

int nouvellePosition (int numJ, int position, int valeurDes){
	int newp;
	if (position==0 && valeurDes == 6){
		switch (numJ) {
			case 1:
				newp = 1;
				break;
			case 2:
				newp = 15;
				break;
			case 3:
				newp = 29;
				break;
			case 4:
				newp = 43;
				break;
		}
	}
	if(position!=0){
		newp = position + valeurDes;
	}
	
return newp;
}

// condition de victoire
// vrai ssi un des jouers à gagné
// pour l'instant si un des joueurs fait un tour complet
/*
int victoire (int numj, int position){

	if (position == 1 && numj == 1 ){
				printf("le joueur %d a gagné !",numj);
	}
	if (position == 2 && numj == 15 ){
				printf("le joueur %d a gagné !",numj);
	}
	if (position == 3 && numj == 29 ){
				printf("le joueur %d a gagné !",numj);
	}
	if (position == 4 && numj == 43 ){
				printf("le joueur %d a gagné !",numj);
	}
	debuttourlu->partieencours = 0; // il faut transmettre debutourlu ?
	return numj; 
} */
