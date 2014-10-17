#ifndef __JEU_H__
#define __JEU_H__

typedef struct {
	int partieencours; //=1 si la partie est toujours en cours
	int numerojoueur;
} struct_debuttour;

typedef struct {
	int numerojoueur;
	int resultatde;
	int positionjoueur;
} struct_retourjeu;

typedef struct {
	int numerojoueur;
	int positionjoueur;
} struct_pendantjeu;

#endif
