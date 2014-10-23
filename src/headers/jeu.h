/**
 * \file	jeu.h
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Declaration des fonctions relatives au jeu pour le jeu Petits chevaux.
 */
 
#ifndef __JEU_H__
#define __JEU_H__

/**
 * \struct struct_debuttour
 * \brief Informations transmises par le pere pour les joueurs en debut de tour.
 *
 * partieencours vaut 1 tant que la partie est en cours. Sinon 0.
 * numerojoueur correspond au numero du joueur devant jouer au prochain tour
 *
 */
 
typedef struct struct_debuttour {
	int partieencours; /*!< Indique si la partie est encors en cours 1. Sinon 0 */
	int numerojoueur; /*!< Numero du joueur devant jouer au prochain tour */
} struct_debuttour;

/**
 * \struct struct_retourjeu
 * \brief Informations transmises par les joueurs pour le pere en fin de tour.
 */

typedef struct struct_retourjeu {
	int numerojoueur; /*!< Indique le numero du joueur venant de jouer. */
	int resultatde; /*!< Indique le resultat de son lance de de. Utile pour savoir si le joueur peut rejouer. */
	int positionjoueur; /*!< Indique la nouvelle position du joueur */
} struct_retourjeu;

/**
 * \struct struct_pendantjeu
 * \brief Informations transmises par les joueurs pour les autres joueurs pendant le tour.
 */

typedef struct struct_pendantjeu {
	int numerojoueur; /*!< Indique le joueur venant de jouer. */
	int positionjoueur; /*!< Indique la nouvelle position de ce joueur. Utile pour faire revenir les chevaux a la case depart si deux se trouvent simultanement sur la meme case. */
	/**
	 * Amélioration : Ajouter une information si le joueur a termine.
	 */
} struct_pendantjeu;


int premier_joueur(void);

void cest_a_qui_de_jouer(int num_fils, int ** pipes, struct_debuttour * debuttourlu);
int la_partie_est_interrompue(struct_debuttour * debuttourlu);

int je_joue(int num_fils, int * position_joueur, struct_pendantjeu * pendantjeu);
void je_transmet_mon_resultat_au_voisin(int num_fils, int ** pipes, struct_pendantjeu * pendantjeu);
void jattend_que_linfo_fasse_le_tour (int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);
void je_fais_passer_le_message(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);

void je_transmet_mon_resultat_au_pere(int num_fils, int ** pipes, struct_retourjeu * retourjeu, int resultatde, int positionjoueur);


void pere_envoyer_message_aux_fils(int ** pipes, struct_debuttour * debuttour, int numerojoueur, int partieencours);
void pere_lit_retour_tour(int ** pipes, struct_retourjeu * retourjeulu);

int joueur_suivant(struct_retourjeu * retourjeulu);

#endif
