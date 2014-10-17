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
#include <signal.h>
#include <string.h>

#include "des.h"
#include "jeu.h"
//#include "plateau.h"

/* void gestionnaire_sigusr1(int numero) { } */

void checkR(int result) {
	if (result < 0) {
		perror("Read Error");
		printf("error dans pid %d \n", getpid());
		exit(EXIT_FAILURE);
	}
}

void checkW(int result) {
	if (result < 0) {
		perror("Write Error");
		printf("error dans pid %d \n", getpid());
		exit(EXIT_FAILURE);
	}
}

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

	int status;
	pid_t pidfork, pidfils[5];

	/**
	 * Autres variables
	 */
	int indice;

	int num_fils, nb_fils; //le numéro du fils et le nombre de fils à créé.
	nb_fils = 4; // Quatres joueurs

	struct sigaction action; //gestion signal


	/**
	 * Pour chaque fils nous initialison une variable informant sur sa position et les structures d'informations qui vont transiter
	 */
//	int * plateau; // Pointeur sur le plateau de jeu

	int position_j;
	
	struct_retourjeu retourjeu;
	struct_retourjeu * retourjeulu;
	
	struct_pendantjeu pendantjeu;
	struct_pendantjeu * pendantjeulu;

	/*
	 * Le programme principal enverra une information contenant le numero du prochain joueur devant jouer.
	 */
	 
 	struct_debuttour debuttour;
 	struct_debuttour * debuttourlu;

	/**
	 * Allocation mémoire de ces structures.
	 */
	
	/**
	 * Initialisation du generateur de nombre aleatoire pour le lance de des
	 */
	init_alea();

	/**
	 * Initialisation du generateur de nombre aleatoire pour le lance de des
	 */

	//plateau = creation_plateau();

	/**
	 * Création des pipes
	 */
	
	for(indice=0;indice<9;indice++) {
		if (pipe(pipes[indice])==-1) {
		        fprintf(stderr,"Erreur lors de l'ouverture de pipes[%d] \n", indice);
		        exit(EXIT_FAILURE);
    		}
	}

	for(num_fils=1;num_fils<=nb_fils;num_fils++) {
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
				/*
				action.sa_handler=gestionnaire_sigusr1;
				sigemptyset(&action.sa_mask);
				action.sa_flags=SA_RESTART;
				
				
				if (sigaction(SIGUSR1, &action, NULL) != 0) {
					fprintf(stderr, "Erreur dans sigaction \n");
					exit(EXIT_FAILURE);
				}
				
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

				// num_fils correspond au numéro du fils
				// position_j correspond a la position du joueur , ils sont tous dans l'ecurie au départ soit 0

				
				position_j=0;
               
				debuttourlu= (struct_debuttour *) malloc(sizeof(struct_debuttour));
				
				//usleep(10000000); // 10 sec
				
				// Tant que le jeu n'est pas fini on regarde si c'est au fils de jouer
				if (read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)) < 0) {
				    perror("Read Error");
				    exit(EXIT_FAILURE);
				}
				
				int resultatdes;
				while(debuttourlu->partieencours==1){


					fflush(stdout);
					fprintf(stdout, "Je suis le fils %d avec le pid %d j'ai lu : %d  dans le pipe : %d \n", num_fils, getpid(), debuttourlu->numerojoueur, num_fils);
				
					if(debuttourlu->numerojoueur == num_fils){
						pendantjeu.numerojoueur = num_fils;
						pendantjeu.positionjoueur = lancer_des(); 
						printf("fils %d de : %d \n",num_fils, pendantjeu.positionjoueur);
						// on écrit dans le pipe du joueur suivant
						
						checkW(write(pipes[num_fils+4][1], &pendantjeu, sizeof(struct_pendantjeu)));
						
						//passe en mode lecture dans le pipe du precedent puis renvoie au pere quand il relit la valeur qu'il a envoyé
						if(num_fils==1){
							checkR(read(pipes[8][0], pendantjeulu,sizeof(struct_pendantjeu)));
							printf("fils %d lit dans pipe %d\n", num_fils, 8);
						}
						else{
							printf("fils %d lit dans pipe %d\n", num_fils, num_fils+3);
							checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
						}
						
						printf("on a relu %d la val %d \n", pendantjeulu->numerojoueur, pendantjeulu->positionjoueur);
					}
					else{
						printf("fils %d en attente \n", num_fils);
						//lit valeur du joueur precedent et renvoie vers le suivant
						if(num_fils==1){
							checkR(read(pipes[8][0], pendantjeulu,sizeof(struct_pendantjeu *)));
						}
						else{
							checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
						}
						
						//on renvoie au suivant
						checkW(write(pipes[num_fils+4][1], pendantjeulu, sizeof(struct_pendantjeu)));					
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
	 
	 verifier tubes, erreur fils 2
	*/
					
					}
					
												sleep(1);
					if (read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)) < 0) {
				
					    perror("Read Error");
					    exit(EXIT_FAILURE);
					}
					
				
							
				}
				
				fprintf(stdout,"Tour fini\n");	
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
/*
				action.sa_handler=gestionnaire_sigusr1;
				sigemptyset(&action.sa_mask);
				action.sa_flags=SA_RESTART;

				if (sigaction(SIGUSR1, &action, NULL) != 0) {
					fprintf(stderr, "Erreur dans sigaction \n");
					exit(EXIT_FAILURE);
				}

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
	/*
	for(indice=0;indice<5;indice++) {
		printf("alea : %d \n", lancer_des());
	}
	*/
	
	//On initialise le premier joueur, soit le fils 1 ayant pour indentifiant 0;
	//debuttour.numerojoueur=0;

	//On ecrit cette structure dans le tube de chaque fils

	debuttour.numerojoueur=1;
	debuttour.partieencours=1;
	
	for(indice=1;indice<=4;indice++) {
		if (write(pipes[indice][1], &debuttour, sizeof(struct_debuttour))<0) {
			perror("Write Error");
		}
		else {
			printf("ok pr fils %d\n", indice);
			//printf("reveil fils %d avec le pid %d\n", indice, pidfils[indice]);
			//kill(pidfils[indice],SIGUSR1);
		}
	}

	debuttour.partieencours=0;
	sleep(5);
	for(indice=1;indice<=4;indice++) {
		if (write(pipes[indice][1], &debuttour, sizeof(struct_debuttour))<0) {
			perror("Write Error");
		}
		else {
			printf("ok pr fils %d\n", indice);
			//printf("reveil fils %d avec le pid %d\n", indice, pidfils[indice]);
			//kill(pidfils[indice],SIGUSR1);
		}
	}

	//usleep(2000000);
	//kill(pidfils[0],SIGUSR1);
	
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
	

	/**
	 * Fermeture du plateau
	 */
	//suppr_plateau(plateau);

	return 0;
}
