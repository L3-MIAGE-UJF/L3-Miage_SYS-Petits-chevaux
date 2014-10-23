/**
 * \file	des.c
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Fonctions de simulation d'un tirage de des.
 */

#include <stdlib.h>
#include <time.h>

/**
 * \brief       Initialise le generateur de nombres aleatoires
 * \details	Initialise la graine allant servir pour la génération de nombres aléatoire.
 * \return    Void
 */

void init_alea() {
	srand(time(NULL)); // initialisation de rand
}

/**
 * \brief       Simule un lancé de dé à 6 cotés.
 * \return    Int - Compris entre 1 et 6.
 */

int lancer_des() {
	return rand()%6+1;
}
