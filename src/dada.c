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

#include <string.h>

#include "headers/des.h"
#include "headers/jeu.h"
#include "headers/pipes.h"


/**
 * Fonctions de vérification pour les opérations read et write
 */
 
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


/**
 * Corps du programme.
 */
 
int main(int argc, char *argv[]) {


	/**
	 * Déclaration et instanciation du tableau de pipes.
	 * Se référer à pipes.h pour plus d'information.
	 */
	 
	int indice;
	int **pipes;

	pipes=(int **) malloc(sizeof(int * ) * 9);	
	
	for (indice=0;indice<9;indice++) {
		pipes[indice]= (int *) malloc(sizeof(int) * 2);
	}

	/**
	 * tableau des PID de chaque fils, pid renvoyé par fork et le status renvoyé par les wait finaux
	 */

	int status;
	pid_t pidfork, pidfils[5];

	/**
	 * Autres variables
	 */

	int num_fils, nb_fils; //le numéro du fils et le nombre de fils à créé.
	nb_fils = 4; // Quatres joueurs



	/**
	 * Pour chaque fils nous initialison une variable informant sur sa position et les structures d'informations qui vont transiter
	 */


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
	 * Création des pipes
	 */
	
	creation_pipes(pipes);

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
				 * La variable num_fils correspond au numéro du fils en cours
				 */

				/**
				 * Fermetures des pipes inutilises pour le fils en cours
				 */
				 
				pipes_fils_start_close(num_fils, pipes);

				/**
				 * Instanciation et initialisation de variables propres au fils num_fils.
				 */

				// position_j correspond a la position du joueur , ils sont tous dans l'ecurie au départ soit 0
				position_j=0;

				/* Allocation d'une zone memoire pour les structures allant être lu pendant le jeu et a chaque debut de tour */               
				debuttourlu=(struct_debuttour *) malloc(sizeof(struct_debuttour));
				pendantjeulu=(struct_pendantjeu *) malloc(sizeof(struct_pendantjeu));

				/**
				 * Corps du fils num_fils
				 */
							
				// Tant que le jeu n'est pas fini on regarde si c'est au fils de jouer
				checkR(read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)));
				
				int resultatdes;
				while(debuttourlu->partieencours==1){

					sleep(1);
					lancer_des(); // ? sinon alea donne memes valeurs

					if (cest_mon_tour(num_fils, debuttourlu)) {
//						je_joue(num_fils);
						pendantjeu.numerojoueur = num_fils;
						pendantjeu.positionjoueur = lancer_des(); 
						printf("fils %d a lance les des : %d \n",num_fils, pendantjeu.positionjoueur);
						// on écrit dans le pipe du joueur suivant
						
						checkW(write(pipes[num_fils+4][1], &pendantjeu, sizeof(struct_pendantjeu)));
						
						//passe en mode lecture dans le pipe du precedent puis renvoie au pere quand il relit la valeur qu'il a envoyé
						if(num_fils==1){
							checkR(read(pipes[8][0], pendantjeulu,sizeof(struct_pendantjeu)));
							//printf("fils %d lit dans pipe %d\n", num_fils, 8);
						}
						else{
							//printf("fils %d lit dans pipe %d\n", num_fils, num_fils+3);
							checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
						}
						
						printf("Tour d'info fini , fils %d a relu %d la val %d\n", num_fils, pendantjeulu->numerojoueur, pendantjeulu->positionjoueur);
					}
					else {
//						je_fais_passer_le_message();
						//printf("fils %d en attente \n", num_fils);
						//lit valeur du joueur precedent et renvoie vers le suivant
						if(num_fils==1){
							checkR(read(pipes[8][0], pendantjeulu,sizeof(struct_pendantjeu)));
						}
						else{
							checkR(read(pipes[num_fils+3][0], pendantjeulu, sizeof(struct_pendantjeu)));
						}
						printf("fils %d fait transiter info %d\n", num_fils, pendantjeulu->positionjoueur);
						//on renvoie au suivant
						checkW(write(pipes[num_fils+4][1], pendantjeulu, sizeof(struct_pendantjeu)));		
					}

					
					checkR(read(pipes[num_fils][0], debuttourlu, sizeof(struct_debuttour)));				
							
				}

				/**
				 * Fermetures des pipes restant
				 */
			
				pipes_fils_end_close(num_fils, pipes);

				return 0;
			break;
			
			default :
				/**
				 * Code d'execution du programme principal, poursuite de la création de fils
				 */

				pidfils[num_fils]=pidfork;
/*
				fflush(stdout);
				fprintf(stdout, "Fils %d cree avec le pid %d \n", num_fils, pidfils[num_fils]);
*/
			break;
		}
	}
	
	/**
	 * Suite du programme principal
	 */

	fflush(stdout);
	fprintf(stdout, "\nTous les fils sont créés. Début du programme.\n\n");

	/**
	 * Fermetures des pipes inutilises
	 */
	 
	pipes_pere_start_close(pipes);
	
	/**
	 * Corps du programme
	*/
	
	//On initialise le premier joueur, soit le fils 1 ayant pour indentifiant 0;
	//debuttour.numerojoueur=0;

	//On ecrit cette structure dans le tube de chaque fils

	debuttour.numerojoueur=premier_joueur();
	
	debuttour.partieencours=1;
	
	for(indice=1;indice<=4;indice++) {
		checkW(write(pipes[indice][1], &debuttour, sizeof(struct_debuttour)));
	}

	debuttour.partieencours=0;
	for(indice=1;indice<=4;indice++) {
		checkW(write(pipes[indice][1], &debuttour, sizeof(struct_debuttour)));
	}
	
	/**
	 * Fermetures des pipes restants
	 */
	 
	pipes_pere_end_close(pipes);

	while((pidfork = (int) wait(&status) )!=-1);

	fflush(stdout);
	fprintf(stdout, "\nTous les fils sont morts. Fin du programme.\n\n");
		
	free(pipes);

	return 0;
}
