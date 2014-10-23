#ifndef __JEU_H__
#define __JEU_H__

typedef struct struct_debuttour {
	int partieencours; //=1 si la partie est toujours en cours
	int numerojoueur;
} struct_debuttour;

typedef struct struct_retourjeu {
	int numerojoueur;
	int resultatde;
	int positionjoueur;
} struct_retourjeu;

typedef struct struct_pendantjeu {
	int numerojoueur;
	int positionjoueur;
	// joueur a termine
} struct_pendantjeu;


int premier_joueur(void);

void cest_a_qui_de_jouer(int num_fils, int ** pipes, struct_debuttour * debuttourlu);
int la_partie_est_interrompue(struct_debuttour * debuttourlu);

int je_joue(int num_fils, int * position_joueur, struct_pendantjeu * pendantjeu, int *danslescalier);
void je_transmet_mon_resultat_au_voisin(int num_fils, int ** pipes, struct_pendantjeu * pendantjeu);
void jattend_que_linfo_fasse_le_tour (int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);
void je_fais_passer_le_message(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);

void je_transmet_mon_resultat_au_pere(int num_fils, int ** pipes, struct_retourjeu * retourjeu, int resultatde, int positionjoueur);


void pere_envoyer_message_aux_fils(int ** pipes, struct_debuttour * debuttour, int numerojoueur, int partieencours);
void pere_lit_retour_tour(int ** pipes, struct_retourjeu * retourjeulu);

int joueur_suivant(struct_retourjeu * retourjeulu);

#endif
