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
	 
	int num_fils, nb_fils; //le numéro du fils et le nombre de fils à créé.
	nb_fils = 4; // Quatres joueurs
	 
	/**
	 * Création des pipes
	 */

	for(num_fils=0;num_fils<nb_fils;num_fils++) {
		pidfork=fork();
		if (pidfork!=0) {
			/**
			 * Code d'execution du programme principal, poursuite de la création de fils
			 */
		
			pidfils[num_fils]=pidfork;
			fprintf(stdout, "Fils %d cree avec le pid %d\n", num_fils, pidfils[num_fils]);
		}
		else {
			/**
			 * Code d'execution du fils num_fils
			 */

			fprintf(stdout, "Je suis le fils %d avec le pid %d\n", num_fils, getpid());

			return 0;
		}
	}
	
	while((pidfork = (int) wait(&status) )!=-1) {
		fprintf(stdout, "Le fils avec le pid %d est mort\n", pidfork);
	}
	
	return 0;
}
