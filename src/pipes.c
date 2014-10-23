#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int pipes_pere_end_close(int ** pipes) {
	int indice;
	close(pipes[0][0]); //fermeture O entree du main depuis joueurs

	for(indice=1;indice<5;indice++) {
		close(pipes[indice][1]); //fermeture I sortie du main vers joueurs
	}
	
	return 0;
}
