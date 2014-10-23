/**
 * \file	jeu.c
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Fonctions relatives au jeu pour le programme Petits Chevaux.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/jeu.h"
#include "headers/dada.h"
#include "headers/des.h"
#include "headers/regles.h"

/**
 * \brief       Selection par l'utilisateur du premier joueur.
 * \details    Demande a l'utilisateur de saisir le numero du premier joueur.
 * \return    Int - Retourne le numero du joueur saisi.
 */

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

/**
 * \brief       Recupere les informations pour le prochain tour.
 * \details    Récupère dans le pipe venant du main vers le joueur concerné la structure contenant les informations pour le prochain tour.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    pipes	Tableau des pipes.
 * \param    debuttourlu	Pointeur sur la structure.
 * \return    Void
 */

void cest_a_qui_de_jouer(int num_fils, int ** pipes, struct_debuttour * debuttourlu) {
	checkR(read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)));
}

/**
 * \brief       Verifie si la partie n'a pas été interrompue.
 * \details    Dans le cas ou un joueur a gagné, nous considérons que la partie est finie. 
 * Dans le cas ou l'utilisateur choisi d'interrompre le programme cette fonction sera très utile pour permettre aux joueurs de se tuer même si ils n'ont pas fini de jouer.
 * \param    debuttourlu	Pointeur sur la structure lue au debut du tour.
 * \return    Int - Renvoie 1 si la partie est termine ou interrompue, 0 sinon.
 */

int la_partie_est_interrompue(struct_debuttour * debuttourlu) {
	return (debuttourlu->partieencours) ? 0 : 1;
}

/**
 * \brief       Action effectuées par le joueur lorsque que vient son tour.
 * \details    Le joueur lance un dé, demande aux reglès quelle est sa nouvelle position et enregistre ces informations.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    positionjoueur	Pointeur sur la position du joueur appelant la fonction.
 * \param    pendantjeu		Pointeur sur la structure qui va être transmise aux autres joueurs.
 * \return    Int - Retourne le resultat du lancé de dé, la position est déjà modifiée.
 */

int je_joue(int num_fils, int * positionjoueur, struct_pendantjeu * pendantjeu) {
	int resultatde = lancer_des();

	*positionjoueur = nouvelle_position(num_fils, *positionjoueur, resultatde);
	
	pendantjeu->numerojoueur = num_fils;
	pendantjeu->positionjoueur = *positionjoueur; 

	return resultatde;
}

/**
 * \brief       Transmission des informations du jeu d'un joueurs aux autres joueurs.
 * \details    La structure contenant les informations du jeu qui vient d'être effectué est déjà crée.
 * Il ne reste qu'a l'écrire dans le pipe du voisin.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    pipes	Tableau des pipes.
 * \param    pendantjeu 	Pointeur sur la structure contenant les informations du jeu qui vient d'être fait.
 * \return    Void - Termine en cas d'erreur
 */

void je_transmet_mon_resultat_au_voisin(int num_fils, int ** pipes, struct_pendantjeu * pendantjeu) {
	// on écrit dans le pipe du joueur suivant
	checkW(write(pipes[num_fils+4][1], pendantjeu, sizeof(struct_pendantjeu)));
}

/**
 * \brief       Attente après envoie des informations du retour de ces informations.
 * \details    Permet la récupération des informations envoyés par le biais du joueur précédent. Ce en lisant dans le pipe du joueur précédent le num_fils.
 * Quand l'information sera revenue, elle aura fait le tour.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    pipes	Tableau des pipes.
 * \param    pendantjeulu 	Pointeur sur la structure contenant les informations du jeu qui vient d'être fait et transmis par le voisin précédent.
 * \return    Void - Termine en cas d'erreur
 */

void jattend_que_linfo_fasse_le_tour(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu) {
	//passe en mode lecture dans le pipe du precedent puis renvoie au pere quand il relit la valeur qu'il a envoyé
	if(num_fils==1){
		checkR(read(pipes[8][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}
	else{
		checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}
}

/**
 * \brief       Fait passer les informations au suivant.
 * \details    Permet la transmission des informations envoyés par le biais du joueur précédent. Ce en lisant dans le pipe du joueur précédent le num_fils.
 * On l'envoie au suivant immédiatement. Cela nous permet d'appliquer la regle pour que le joueur revienne au point de départ si un autre joueur est arrivé sur la même case.
 * Cette fonction est appellée lorsque ce n'est pas à num_fils de jouer.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    pipes	Tableau des pipes.
 * \param    pendantjeulu 	Pointeur sur la structure contenant les informations du jeu qui vient d'être transmis par le voisin précédent.
 * \return    Void - Termine en cas d'erreur
 */
 
void je_fais_passer_le_message(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu) {
	
	//printf("fils %d en attente \n", num_fils);
	//lit valeur du joueur precedent et renvoie vers le suivant
	
	if(num_fils==1){
		checkR(read(pipes[8][0], pendantjeulu,sizeof(struct_pendantjeu)));
	}
	else{
		checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
	}
	//printf("fils %d fait transiter info %d\n", num_fils, pendantjeulu->positionjoueur);
	
	//on renvoie au suivant
	checkW(write(pipes[num_fils+4][1], pendantjeulu, sizeof(struct_pendantjeu)));
}

/**
 * \brief       Transmet les informations au père.
 * \details    Quand les informations transmises ont fait le tour, on génère une structure contenant les informations dont le père aura besoin pour modérer.
 * On lui envoie alors dans le pipe des fils vers le père.
 * \param    num_fils	Int - Correspond au numéro du fils souhaitant récupérer les informations.
 * \param    pipes	Tableau des pipes.
 * \param    retourjeu 		Pointeur sur la structure contenant les informations du jeu qui vient d'être fait et ayant fait le tour.
 * \param    resultatde 	Valeur du dé lancé. Utile pour le père afin de savoir si le fils doit rejouer ou non. En cas de double 6.
 * \param    positionjoueur 	Nouvelle position du joueur. Utile pour savoir si un joueur est arrivé au bout de sa course. 
 * \return    Void - Termine en cas d'erreur
 */
 
void je_transmet_mon_resultat_au_pere(int num_fils, int ** pipes, struct_retourjeu * retourjeu, int resultatde, int positionjoueur) {

	retourjeu->numerojoueur=num_fils;
	retourjeu->resultatde=resultatde;
	retourjeu->positionjoueur=positionjoueur;
	
	checkW(write(pipes[0][1], retourjeu, sizeof(struct_retourjeu)));
}

/**
 * \brief       Transmet les informations du père vers les fils.
 * \details    Quand les informations transmises au père ont été analysé, ou lors du premier tour le père doit envoyer des informations au fils.
 * \param    pipes	Tableau des pipes.
 * \param    debuttour	 	Pointeur sur la structure devant contenir les informations qui vont être transmises au joueur.
 * \param    numerojoueur 	Numéro du prochain joueur devant jouer.
 * \param    partieencours 	Indique si la partie est toujours en cours. (1 oui | 0 - non)
 * \return    Void - Termine en cas d'erreur
 */

void pere_envoyer_message_aux_fils(int ** pipes, struct_debuttour * debuttour, int numerojoueur, int partieencours) {
	int indice;
	debuttour->numerojoueur=numerojoueur;
	debuttour->partieencours=partieencours;
	
	for(indice=1;indice<=4;indice++) {
		checkW(write(pipes[indice][1], debuttour, sizeof(struct_debuttour)));
	}
}

/**
 * \brief       Lecture des informations transmises par les fils.
 * \details    Le joueur qui vient de jouer fait remonter des informations au père une fois qu'il vient de terminer de faire circuler des informations aux autres joueurs.
 * \param    pipes	Tableau des pipes.
 * \param    retourjeulu	 Pointeur sur la structure devant contenir les informations destinées au père par le joueurs.
 * \return    Void - Termine en cas d'erreur
 */
	
void pere_lit_retour_tour(int ** pipes, struct_retourjeu * retourjeulu) {
	checkR(read(pipes[0][0], retourjeulu, sizeof(struct_retourjeu)));
	
	printf("\nretour tour lu : num fils %d, de : %d, newpositionjoueur : %d\n", retourjeulu->numerojoueur, retourjeulu->resultatde, retourjeulu->positionjoueur);
}

/**
 * \brief       Indique le prochain joueur devant jouer.
 * \details    Selon le retour des informations renvoyées au père après un tour de jeu. Le père décide si il fait rejouer un joueur (en cas de double 6), ou si il donne la main au suivant.
 * \param    retourjeulu	 Pointeur sur la structure devant contenir les informations destinées au père par le joueurs.
 * \return    result	Int - Le numéro du prochain joueur devant s'executer.
 */

int joueur_suivant(struct_retourjeu * retourjeulu) {
	if (retourjeulu->resultatde==6) {
		return retourjeulu->numerojoueur;
	}
	else {
		return (retourjeulu->numerojoueur==4) ? 1 : retourjeulu->numerojoueur+1;
	}
}
