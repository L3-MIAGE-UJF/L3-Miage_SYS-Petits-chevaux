/**
 * \file	dada.c
 * \author	AOUN Abel et DOUCHET Maximilien
 * \version	1.0
 * \date	14/10/2014
 * \brief       Programme de jeu des petits chevaux utilisant des fork() et des pipes.
 *
 * \details	Fichier Principal du programme dada
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	/**
	 * Tableau de pipes
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
	
	int pipes[9][2];
	
	/**
	 * tableau des PID de chaque fils, pid renvoyé par fork et le status renvoyé par les wait finaux
	 */
	 
	int pidfils[4], pidfork, status;
	
	
	/**
	 * Autres variables
	 */
	int indice;
	
	int num_fils, nb_fils; //le numéro du fils et le nombre de fils à créé.
	nb_fils = 4; // Quatres joueurs
	 
	/**
	 * Création des pipes
	 */
	
	for(indice=0;indice<9;indice++) {
		if (pipe(pipes[indice])==-1) {
		        fprintf(stderr,"Erreur lors de l'ouverture de pipes[%d] \n", indice);
		        exit(EXIT_FAILURE);
    		}
	}

	for(num_fils=0;num_fils<nb_fils;num_fils++) {
		switch(pidfork=fork()) {
			case -1 :
				/**
				 * En cas d'erreur lors de la creation du fork
				 */
				 
				fflush(stdout);
				fprintf(stderr,"Erreur lors de la creation du fork\n");
				exit(-1);
			break;
			
			case 0 :
				/**
				 * Code d'execution du fils num_fils
				 */

				/**
				 * Fermetures des pipes inutilises pour le fils en cours
				 */
				 
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

				/**
				 * Corps du fils num_fils
				 */

				fflush(stdout);
				fprintf(stdout, "Je suis le fils %d avec le pid %d \n", num_fils, getpid());

				/**
				 * Fermetures des pipes restant
				 */

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
			break;
			
			default :
				/**
				 * Code d'execution du programme principal, poursuite de la création de fils
				 */

				pidfils[num_fils]=pidfork;
				fflush(stdout);
				fprintf(stdout, "Fils %d cree avec le pid %d \n", num_fils, pidfils[num_fils]);
			break;
		}
	}
	
	/**
	 * Suite du programme principal
	 */
	
	/**
	 * Fermetures des pipes inutilises
	 */
	 
	if (close(pipes[0][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[0][1] \n"); } //fermeture I entree du main depuis joueurs
	
	for(indice=1;indice<5;indice++) {
		if (close(pipes[indice][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture O sortie du main vers joueurs
	}

	for(indice=5;indice<=8;indice++) {
		if (close(pipes[indice][1])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][1] \n", indice); } //fermeture I de joueur vers joueur
		if (close(pipes[indice][0])==-1) { fprintf(stderr,"Erreur lors de fermeture de pipes[%d][0] \n", indice); } //fermeture O de joueur vers joueur
	}	
	
	/**
	 * Corps du programme
	*/
	
	
	
	/**
	 * Fermetures des pipes restants
	 */
	 
	close(pipes[0][0]); //fermeture O entree du main depuis joueurs

	for(indice=1;indice<5;indice++) {
		close(pipes[indice][1]); //fermeture I sortie du main vers joueurs
	}
	
	while((pidfork = (int) wait(&status) )!=-1) {
		fflush(stdout);
		fprintf(stdout, "Le fils avec le pid %d est mort\n", pidfork);
	}
	
	return 0;
}
