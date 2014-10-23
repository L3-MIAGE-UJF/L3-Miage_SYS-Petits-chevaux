/**
 * \file	pipes.c
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Fonctions relatives au pipes pour le jeu Petits chevaux.
 * \details    Les pipes sont organisés de cette maniere :
 * 0 -> Entree du main depuis joueurs
 * 1 -> sortie du main vers joueur 1
 * 2 -> sortie du main vers joueur 2
 * 3 -> sortie du main vers joueur 3
 * 4 -> sortie du main vers joueur 4
 * 5 -> sortie du joueur 1 vers joueur 2
 * 6 -> sortie du joueur 2 vers joueur 3
 * 7 -> sortie du joueur 3 vers joueur 4
 * 8 -> sortie du joueur 4 vers joueur 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * \brief       Creation des pipes
 * \details    Fonction de creation des pipes
 * \param    pipes	Tableau des pipes
 * \return    Retourne 0 si tout s'est bien passé
 */
 
int creation_pipes(int ** pipes) {
	int indice;
	for(indice=0;indice<9;indice++) {
		if (pipe(pipes[indice])==-1) {
			fprintf(stderr,"Erreur lors de l'ouverture de pipes[%d] \n", indice);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}

/**
 * \brief       Fermeture des pipes non utilises pour chaque fils.
 * \details    Ferme les pipes de chaque fils non utilisés.
 * \param    num_fils         Le numéro du fils souhaitant fermer ses pipes
 * \param    pipes	Le Tableau des pipes
 * \return    Retourne 0 si tout s'est bien passé
 */

int pipes_fils_start_close(int num_fils, int ** pipes) {
	int indice;
	
	if (close(pipes[0][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[0][0] \n"); } //fermeture O entree du main depuis joueurs

	for(indice=1;indice<5;indice++) {
		if (close(pipes[indice][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture I sortie du main vers joueurs
		if (num_fils!=indice) {
			if (close(pipes[indice][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][0] \n", indice); } //fermeture 0 sortie du main vers joueurs quand indice !=num_fils
		}
	}

	for(indice=5;indice<9;indice++) {
		if (num_fils!=(indice-4)) {
			if (indice==5) {
				if (close(pipes[8][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[8][0] \n"); } //fermeture O de joueur vers joueur
			}
			else {
				if (close(pipes[(indice-1)][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][0] \n", indice); } //fermeture O de joueur vers joueur
			}
			if (close(pipes[indice][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture I de joueur vers joueur
		}
	}
	
	return 0;
}

/**
 * \brief       Fermeture des pipes utilisés pour chaque fils.
 * \details    Ferme les pipes de chaque fils utilisés lorsque qu'il n'en a plus besoin.
 * \param    num_fils         Le numéro du fils souhaitant fermer ses pipes
 * \param    pipes	Le Tableau des pipes
 * \return    Retourne 0 si tout s'est bien passé
 */

int pipes_fils_end_close(int num_fils, int ** pipes) {
	int indice;
	
	for(indice=5;indice<9;indice++) {
		if (num_fils==(indice-4)) {
			if (indice==5) {
				if (close(pipes[8][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[8][0] \n"); } //fermeture O de joueur vers joueur						
			}
			else {
				if (close(pipes[(indice-1)][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][0] \n", indice); } //fermeture O de joueur vers joueur
			}
			if (close(pipes[indice][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture I de joueur vers joueur
		}
	}
	
	return 0;
}

/**
 * \brief       Fermeture des pipes non utilises pour le pere.
 * \details    Ferme les pipes non utilisés du père.
 * \param    pipes	Le Tableau des pipes
 * \return    Retourne 0 si tout s'est bien passé
 */

int pipes_pere_start_close(int ** pipes) {
	int indice;
	
	if (close(pipes[0][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[0][1] \n"); } //fermeture I entree du main depuis joueurs
	
	for(indice=1;indice<5;indice++) {
		if (close(pipes[indice][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture O sortie du main vers joueurs
	}

	for(indice=5;indice<=8;indice++) {
		if (close(pipes[indice][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture I de joueur vers joueur
		if (close(pipes[indice][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][0] \n", indice); } //fermeture O de joueur vers joueur
	}
	
	return 0;
}

/**
 * \brief       Fermeture des pipes utilisés pour le père.
 * \details    Ferme les pipes du père utilisés lorsque qu'il n'en a plus besoin.
 * \param    pipes	Le Tableau des pipes
 * \return    Retourne 0 si tout s'est bien passé
 */

int pipes_pere_end_close(int ** pipes) {
	int indice;
	close(pipes[0][0]); //fermeture O entree du main depuis joueurs

	for(indice=1;indice<5;indice++) {
		close(pipes[indice][1]); //fermeture I sortie du main vers joueurs
	}
	
	return 0;
}
