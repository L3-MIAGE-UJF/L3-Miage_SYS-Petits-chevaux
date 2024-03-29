/**
 * \file	regles.c
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Fonctions relatives aux regles pour le jeu Petits chevaux.
 */
 
#include <stdio.h>
#include "headers/jeu.h"

/**
 * \brief      Indique au joueur si c'est a son tour de jouer.
 * \details    Celon la valeur renvoyée le joueur effectuera son tour ou non.
 * \param    num_fils	Correspond au numéro du fils appelant la fonction.
 * \param    debuttourlu	Correspond a la structure que le joueur a recu dans le pipe par le père.
 * \return    Int Renvoie 0 si ce n'est pas au fils de jouer et 1 si c'est son tour.
 */
 
int cest_mon_tour(int num_fils, struct_debuttour * debuttourlu) {
	return (debuttourlu->numerojoueur == num_fils) ? 1 : 0;
}

/**
 * \brief      Donne la position de joueur sur l'escalier.
 * \details    Donne une nouvelle position selon la position et le numero de joueur transmis. Mais cette fonction est appellée dans le cas ou le joueur est devant ou sur l'escalier.
 * \param    num_fils	Correspond au numéro du fils appelant la fonction.
 * \param    positionjoueur	Correspond a la position du fils appelant la fonction.
 * \param    resultatde		Correspond a la valeur du lance de des du joueur.
 * \return    Int Renvoie 0 si ce n'est pas au fils de jouer et 1 si c'est son tour.
 */

int position_escalier(int num_fils, int *positionjoueur, int resultatde){
	int nouvelleP;
	nouvelleP = *positionjoueur;
	switch (num_fils) {
			case 1:
				if (*positionjoueur == 56 && resultatde == 1)
					nouvelleP =  57 ;
				if(*positionjoueur == 57 && resultatde == 2)
					nouvelleP = 58 ;
				if(*positionjoueur == 58 && resultatde == 3)
					nouvelleP = 59 ;
				if(*positionjoueur == 59 && resultatde == 4)
					nouvelleP = 60 ;
				if(*positionjoueur == 60 && resultatde == 5)
					nouvelleP = 61 ;
				if(*positionjoueur == 61 && resultatde == 6)
					nouvelleP = 61 ; // a gagné
			break;
			
			case 2:
				 if(*positionjoueur == 14 && resultatde == 1) 
				 	nouvelleP = 63;
				 if(*positionjoueur == 63 && resultatde == 2) 
					nouvelleP = 64;
				 if(*positionjoueur == 64 && resultatde == 3)
					nouvelleP = 65;
				 if(*positionjoueur == 65 && resultatde == 4) 
					nouvelleP = 66;
				 if(*positionjoueur == 66 && resultatde == 5) 
					nouvelleP = 67;
				 if(*positionjoueur == 67 && resultatde == 6) 
					nouvelleP = 68; // a gagné
			break;
			
			case 3:
				if(*positionjoueur == 28 && resultatde == 1) 
					nouvelleP = 69;
				if(*positionjoueur == 69 && resultatde == 2)
					nouvelleP = 70;
				if(*positionjoueur == 70 && resultatde == 3)
				nouvelleP = 71;
				if(*positionjoueur == 71 && resultatde == 4)
				nouvelleP = 72;
				if(*positionjoueur == 72 && resultatde == 5)
					nouvelleP = 73;
				if(*positionjoueur == 73 && resultatde == 6)
				nouvelleP = 74; // a gagné
			break;
			
			case 4:
				if(*positionjoueur == 42 && resultatde == 1)
					nouvelleP = 75;
				if(*positionjoueur == 75 && resultatde == 2)
					nouvelleP = 76;
				if(*positionjoueur == 76 && resultatde == 3)
					nouvelleP = 77;
				if(*positionjoueur == 77 && resultatde == 4)
					nouvelleP = 78;
				if(*positionjoueur == 78 && resultatde == 5)
					nouvelleP = 79;
				if(*positionjoueur == 79 && resultatde == 6)
					nouvelleP = 80; // a gagné
			break;
		}
	return nouvelleP;
}

/**
 * \brief      Donne une nouvelle position pour un joueur.
 * \details    Donne une nouvelle position selon la position et le numero de joueur transmis.
 * \param    num_fils	Correspond au numéro du fils appelant la fonction.
 * \param    positionjoueur	Correspond a la position du fils appelant la fonction.
 * \param    resultatde		Correspond a la valeur du lance de des du joueur.
 * \return    Int Renvoie 0 si ce n'est pas au fils de jouer et 1 si c'est son tour.
 */

int nouvelle_position(int num_fils, int positionjoueur, int resultatde, int *danslescalier ) {
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
				// si le joueur est à sa dernière case ou qu'il est dans son escalier alors il doit faire un score particulier pour avancer
				if ( positionjoueur == 56 || danslescalier[1] == 1) {
					danslescalier[1] = 1;
					nouvelle_position = position_escalier(num_fils, &positionjoueur, resultatde);
				}
				else{
					// si le joueur a un resultat de dé qui doit le faire passer par sa case de départ alors il doit reculer plutot que faire plus d'un tour. ( ici on il s'arrete devant son escalier)
					 
					if (positionjoueur + resultatde > 56) {
						nouvelle_position=56;
					}
					else{
						// avancement normal sur le plateau
						nouvelle_position = positionjoueur + resultatde;
					}
				}
			break;
			
			case 2:
				if ( positionjoueur == 14 || danslescalier[2] == 1) {
					danslescalier[2] = 1;
					nouvelle_position = position_escalier(num_fils, &positionjoueur, resultatde);
				}
				else{
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
				}
			break;
			
			case 3:
				if ( positionjoueur == 28 || danslescalier[3] == 1) {
					danslescalier[3] = 1;
					nouvelle_position = position_escalier(num_fils, &positionjoueur, resultatde);
				}
				else{
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
				}
			break;
			
			case 4:
				if ( positionjoueur == 42 || danslescalier[4] == 1) {
					danslescalier[4] = 1;
					nouvelle_position = position_escalier(num_fils, &positionjoueur, resultatde);
				}
				else{

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
				}
			break;
		}
	}
	return nouvelle_position;
}

/**
 * \brief      Indique si il y a conflit entre deux joueurs.
 * \details    Selon le resultat du jeu et la position des fils cela detecte et change la position d'un cavalier si il sont sur la meme case.
 * Le nouveau cheval prend la place du précédent sur la case. Et renvoie le précédent dans l'écurie.
 * \param    pendantjeulu Structure contenant toutes les informations transmises après la phase de jeu.
 * \return    Int Renvoie 0 si il n'a pas encore gagné et 1 si il est vainqueur.
 */

void conflit_entre_deux_joueur(struct_pendantjeu * pendantjeulu, int * positionjoueur){
	// si la position du joueur courant est égale à la position du joueur en lecture, ce dernier est renvoyé à l'enclos
	if (pendantjeulu->positionjoueur==*positionjoueur && *positionjoueur!=0) {
		//printf("%d ecrase a la case %d ! \n ", pendantjeulu->numerojoueur, *positionjoueur); 
		*positionjoueur = 0;
		
	}
}

/**
 * \brief      Indique si le joueur a gagné.
 * \details    Selon le resultat du jeu d'un fils, cela indique si ce fils a gagné
 * \param    retourjeulu Structure contenant toutes les informations importantes sur le jeu et le joueur qui vient de jouer.
 * \return    Int Renvoie 0 si il n'a pas encore gagné et 1 si il est vainqueur.
 */

int le_joueur_a_gagne(struct_retourjeu * retourjeulu) {
	int joueuragagne=0;
	
	switch (retourjeulu->numerojoueur) {
			case 1:
				joueuragagne = (retourjeulu->positionjoueur==62) ? 1 : 0;
			break;
			
			case 2:
				joueuragagne = (retourjeulu->positionjoueur==68) ? 1 : 0;
			break;
			
			case 3:
				joueuragagne = (retourjeulu->positionjoueur==74) ? 1 : 0;
			break;
			
			case 4:
				joueuragagne = (retourjeulu->positionjoueur==80) ? 1 : 0;
			break;
	}
	
	return joueuragagne;
}
