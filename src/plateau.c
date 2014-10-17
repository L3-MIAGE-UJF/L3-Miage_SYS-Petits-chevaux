#include <stdlib.h>
#include <time.h>

 /**
 * \brief      Couleur possible pour un Point.
 * \details   La table de correspondance de couleurs est disponible en modification par les accesseurs.
 */

/**
 * \brief       Creer le plateau et l'initialise a 0
 * \details
 * \return    le pointeur \a sur le tableau cree
 */

// Pas forcement indispensable ?
int * creation_plateau() {
	int * plateau;
	int indice;

	plateau = (int *) malloc(sizeof(int)*80);
	for (indice=0;indice<80;indice++) {
		plateau[indice]=0;
	}
	return plateau;
}

void suppr_plateau(int * plateau) {
	free(plateau);
}

//typedef enum
//{
//   COLOR_BLUE,               /*!< Couleur bleu (0,0,255)               */
//   COLOR_DARK_RED,      /*!< Couleur rouge sombre (64,0,0)  */
//   COLOR_OLIVE              /*!< Couleur olive (51,51,0)               */
//}
