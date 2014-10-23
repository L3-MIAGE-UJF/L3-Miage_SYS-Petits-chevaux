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

#endif
