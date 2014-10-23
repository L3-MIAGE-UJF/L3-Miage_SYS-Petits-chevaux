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
} struct_pendantjeu;


int premier_joueur(void);

void cest_a_qui_de_jouer(int num_fils, int ** pipes, struct_debuttour * debuttourlu);
int la_partie_est_interrompue(struct_debuttour * debuttourlu);

void je_joue(int num_fils, struct_pendantjeu * pendantjeu);
void je_transmet_mon_resultat_au_voisin(int num_fils, int ** pipes, struct_pendantjeu * pendantjeu);
void jattend_que_linfo_fasse_le_tour (int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);
void je_fais_passer_le_message(int num_fils, int ** pipes, struct_pendantjeu * pendantjeulu);

#endif
