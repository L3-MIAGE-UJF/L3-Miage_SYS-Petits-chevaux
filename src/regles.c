#include <stdio.h>

#include "headers/jeu.h"

// calcul de la position du cheval selon les regles suivantes
// de l'ecurie (0) si le dé est à 6 on passe le cheval à la position de départ du joueur correspondant

int cest_mon_tour(int num_fils, struct_debuttour * debuttourlu) {
	return (debuttourlu->numerojoueur == num_fils) ? 1 : 0;
}

int nouvelle_position(int num_fils, int positionjoueur, int resultatde) {
	int nouvelle_position=0;
	
	// Ajouter toutes les regles de deplacement
	if (positionjoueur==0 && resultatde == 6){
		switch (num_fils) {
			case 1:
				nouvelle_position = 1;
			break;
			
			case 2:
				nouvelle_position = 15;
			break;
			
			case 3:
				nouvelle_position = 29;
			break;
			
			case 4:
				nouvelle_position = 43;
			break;
		}
	}
	else if (positionjoueur!=0) {
		//nouvelle position du joueur, limité a sa case limite (bridage)
		switch (num_fils) {
			case 1:
				if (positionjoueur + resultatde > 56) {
					nouvelle_position=56;
				}
				else{
					nouvelle_position = positionjoueur + resultatde;
				}
			break;
			
			case 2:
				if ((positionjoueur + resultatde) > 56) { 
					positionjoueur = (positionjoueur + resultatde) % 56;
					if (positionjoueur > 14) {
						nouvelle_position=14;
					}
					else {
						nouvelle_position=positionjoueur;
					}
				}
				else{
					nouvelle_position = positionjoueur + resultatde;
				}
			break;
			
			case 3:
				if ((positionjoueur + resultatde) > 56) { 
					positionjoueur = (positionjoueur + resultatde) % 56;
					if (positionjoueur > 28) {
						nouvelle_position=28;
					}
					else {
						nouvelle_position=positionjoueur;
					}
				}
				else{
					nouvelle_position = positionjoueur + resultatde;
				}
			break;
			
			case 4:

				if ((positionjoueur + resultatde) > 56) { 

					positionjoueur = (positionjoueur + resultatde) % 56;

					if (positionjoueur > 42) {

						nouvelle_position=42;
					}
					else {
						nouvelle_position=positionjoueur;
					}
				}
				else{

					nouvelle_position = positionjoueur + resultatde;
				}
			break;
		}
	}
	return nouvelle_position;
}

int le_joueur_a_gagne(struct_retourjeu * retourjeulu) {
	int joueuragagne=0;
	
	switch (retourjeulu->numerojoueur) {
			case 1:
				joueuragagne = (retourjeulu->positionjoueur==56) ? 1 : 0;
			break;
			
			case 2:
				joueuragagne = (retourjeulu->positionjoueur==14) ? 1 : 0;
			break;
			
			case 3:
				joueuragagne = (retourjeulu->positionjoueur==28) ? 1 : 0;
			break;
			
			case 4:
				joueuragagne = (retourjeulu->positionjoueur==42) ? 1 : 0;
			break;
	}
	
	return joueuragagne;
}
/*
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
*/

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
