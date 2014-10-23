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
 * \brief      Donne une nouvelle position pour un joueur.
 * \details    Donne une nouvelle position selon la position et le numero de joueur transmis.
 * \param    num_fils	Correspond au numéro du fils appelant la fonction.
 * \param    positionjoueur	Correspond a la position du fils appelant la fonction.
 * \param    resultatde		Correspond a la valeur du lance de des du joueur.
 * \return    Int Renvoie 0 si ce n'est pas au fils de jouer et 1 si c'est son tour.
 */

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
