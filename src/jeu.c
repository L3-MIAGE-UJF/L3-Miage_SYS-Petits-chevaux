#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/jeu.h"
#include "headers/dada.h"
#include "headers/des.h"
#include "headers/regles.h"

int premier_joueur(void) {
	char buff[10]={0};

	printf("Quel sera le premier joueur ?\n");
	
	while (buff[0]>'4'||buff[0]<'1') {
		//fflush(stdout);
		printf("\nEntrez un nombre entre 1 et 4 : ");
		fgets(buff, sizeof(buff), stdin);
	}
	
	printf("Le joueur %d commence ! \n\n", (buff[0]-'0'));
	return (int) (buff[0]-'0');
}

void cest_a_qui_de_jouer(int num_fils, int ** pipes, struct_debuttour * debuttourlu) {
	checkR(read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)));
}

int la_partie_est_interrompue(struct_debuttour * debuttourlu) {
	return (debuttourlu->partieencours) ? 0 : 1;
}

int je_joue(int num_fils, int * positionjoueur, struct_pendantjeu * pendantjeu, int *danslescalier) {
	int resultatde = lancer_des();
	printf("\n je joue numfils: %d posiion:%d \n",num_fils, *positionjoueur);
	*positionjoueur = nouvelle_position(num_fils, *positionjoueur, resultatde, danslescalier);
	
	pendantjeu->numerojoueur = num_fils;
	pendantjeu->positionjoueur = *positionjoueur; 
//	printf("fils %d a lance les des : %d, il a np : %d \n",num_fils, resultatde, pendantjeu->positionjoueur);
	return resultatde;
}
	
void je_transmet_mon_resultat_au_voisin(int num_fils, int ** pipes, struct_pendantjeu * pendantjeu) {
	// on écrit dans le pipe du joueur suivant
	checkW(write(pipes[num_fils+4][1], pendantjeu, sizeof(struct_pendantjeu)));
}

void jattend_que_linfo_fasse_le_tour(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu) {
	//passe en mode lecture dans le pipe du precedent puis renvoie au pere quand il relit la valeur qu'il a envoyé
	if(num_fils==1){
		checkR(read(pipes[8][0], pendantjeulu, sizeof(struct_pendantjeu)));
		//printf("fils %d lit dans pipe %d\n", num_fils, 8);
	}
	else{
		//printf("fils %d lit dans pipe %d\n", num_fils, num_fils+3);
		checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}

//	printf("Tour d'info fini , fils %d a relu %d la val %d\n", num_fils, pendantjeulu->numerojoueur, pendantjeulu->positionjoueur);
}

void je_fais_passer_le_message(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu) {
	
	//printf("fils %d en attente \n", num_fils);
	//lit valeur du joueur precedent et renvoie vers le suivant
	
	if(num_fils==1){
		checkR(read(pipes[8][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}
	else{
		checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}
	//printf("fils %d fait transiter info %d\n", num_fils, pendantjeulu->positionjoueur);
	
	//on renvoie au suivant
	checkW(write(pipes[num_fils+4][1], pendantjeulu, sizeof(struct_pendantjeu)));
}

void je_transmet_mon_resultat_au_pere(int num_fils, int ** pipes, struct_retourjeu * retourjeu, int resultatde, int positionjoueur) {

	retourjeu->numerojoueur=num_fils;
	retourjeu->resultatde=resultatde;
	retourjeu->positionjoueur=positionjoueur;
	
	checkW(write(pipes[0][1], retourjeu, sizeof(struct_retourjeu)));
}

void pere_envoyer_message_aux_fils(int ** pipes, struct_debuttour * debuttour, int numerojoueur, int partieencours) {
	int indice;
	debuttour->numerojoueur=numerojoueur;
	debuttour->partieencours=partieencours;
	
	for(indice=1;indice<=4;indice++) {
		checkW(write(pipes[indice][1], debuttour, sizeof(struct_debuttour)));
	}
}
	
void pere_lit_retour_tour(int ** pipes, struct_retourjeu * retourjeulu) {
	checkR(read(pipes[0][0], retourjeulu, sizeof(struct_retourjeu)));
	
	printf("\nretour tour lu : num fils %d, de : %d, newpositionjoueur : %d\n", retourjeulu->numerojoueur, retourjeulu->resultatde, retourjeulu->positionjoueur);
}

int joueur_suivant(struct_retourjeu * retourjeulu) {
	if (retourjeulu->resultatde==6) {
		return retourjeulu->numerojoueur;
	}
	else {
		return (retourjeulu->numerojoueur==4) ? 1 : retourjeulu->numerojoueur+1;
	}
}
				
 /**
 * \brief      Couleur possible pour un Point.
 * \details   La table de correspondance de couleurs est disponible en modification par les accesseurs.
 */

/**
 * \brief       Creer le plateau et l'initialise a 0
 * \details
 * \return    le pointeur \a sur le tableau cree
 */


/**
 * Structure transitant du programme principal vers les joueurs. Elle informe les joueurs du prochain qui doit jouer.
 */
 


/**
 * Structure transitant des joueurs vers le programme principal. Elle informe le programme principal du résultat du de, de la nouvelle position du joueur.
 */



/**
 * Structure transitant des joueurs vers les joueurs. Elle informe les autres joueurs de la nouvelle position du joueur
 */


//typedef enum
//{
//   COLOR_BLUE,               /*!< Couleur bleu (0,0,255)               */
//   COLOR_DARK_RED,      /*!< Couleur rouge sombre (64,0,0)  */
//   COLOR_OLIVE              /*!< Couleur olive (51,51,0)               */
//}
