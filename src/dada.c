/**
 * \file	dada.c
 * \author	AOUN Abel et DOUCHET Maximilien
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
#include "headers/regles.h"
#include "headers/pipes.h"


/**
 * Fonctions de vérification pour les opérations read et write
 */
 
 
/**
 * \brief       Fonction de verification du bon deroulement de read.
 * \details    Verifie que l'operation de lecture dans un pipe s'est bien deroulée.
 * \param    result	Int - Correspond au resultat de la fonction read appellée en parametre.
 * \return    Void - Termine le programme en cas d'erreur
 */
 
void checkR(int result) {
	if (result < 0) {
		perror("Read Error");
		printf("error dans pid %d \n", getpid());
		exit(EXIT_FAILURE);
	}
}

/**
 * \brief       Fonction de verification du bon deroulement de write.
 * \details    Verifie que l'operation d'ecriture dans un pipe s'est bien deroulée.
 * \param    result	Int - Correspond au resultat de la fonction read appellée en parametre.
 * \return    Void - Termine le programme en cas d'erreur
 */

void checkW(int result) {
	if (result < 0) {
		perror("Write Error");
		printf("error dans pid %d \n", getpid());
		exit(EXIT_FAILURE);
	}
}


/**
 * \fn int main (int argc, char *argv[])
 * \brief Corps du programme Petit Chevaux
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
 
int main(int argc, char *argv[]) {


	/**
	 * Déclaration et instanciation du tableau de pipes.
	 * Se référer à pipes.h pour plus d'information.
	 */
	 
	int indice;
	int **pipes;

	// faire schema ?
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


	int positionjoueur;
	
	int resultatde;
	
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

				// positionjoueur correspond a la position du joueur , ils sont tous dans l'ecurie au départ soit 0
				positionjoueur=0;
				
				/* Allocation d'une zone memoire pour les structures allant être lu pendant le jeu et a chaque debut de tour */               
				debuttourlu=(struct_debuttour *) malloc(sizeof(struct_debuttour));
				pendantjeulu=(struct_pendantjeu *) malloc(sizeof(struct_pendantjeu));

				/**
				 * Corps du fils num_fils
				 */
							
				// Tant que le jeu n'est pas fini on regarde si c'est au fils de jouer
				cest_a_qui_de_jouer(num_fils, pipes, debuttourlu);

				
				while(!la_partie_est_interrompue(debuttourlu)){

// essayer de supprimer ce code en gardant l'alea
					usleep(100000);
					lancer_des(); // ? sinon alea donne memes valeurs
//

					if (cest_mon_tour(num_fils, debuttourlu)) {

						resultatde=je_joue(num_fils, &positionjoueur, &pendantjeu);

						je_transmet_mon_resultat_au_voisin(num_fils, pipes, &pendantjeu);

						jattend_que_linfo_fasse_le_tour (num_fils, pipes, pendantjeulu);
						
						je_transmet_mon_resultat_au_pere(num_fils, pipes, &retourjeu, resultatde, positionjoueur);
					}
					else {
						je_fais_passer_le_message(num_fils, pipes, pendantjeulu);
						//mode je lit et regarde si je doit reculer
					}
					
					cest_a_qui_de_jouer(num_fils, pipes, debuttourlu);						
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

	retourjeulu=(struct_retourjeu *) malloc(sizeof(struct_retourjeu));

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

	pere_envoyer_message_aux_fils(pipes, &debuttour, premier_joueur(), 1);

	do {
		pere_lit_retour_tour(pipes, retourjeulu);
		pere_envoyer_message_aux_fils(pipes, &debuttour, joueur_suivant(retourjeulu), 1);
	} while (!le_joueur_a_gagne(retourjeulu));

	pere_envoyer_message_aux_fils(pipes, &debuttour, 0, 0);
	
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
