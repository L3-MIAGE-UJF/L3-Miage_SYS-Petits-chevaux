#include <stdlib.h>
#include <time.h>

/**
 * \brief       Calcule la distance entre deux points
 * \details    La distance entre les \a point1 et \a point2 est calculée par l'intermédiaire
 *                  des coordonnées des points. (cf #Point)
 * \param    point1         Point 1 pour le calcul de distance.
 * \param    point2         Point 2 pour le calcul de distance.
 * \return    Un \e float représentant la distance calculée.
 */

 /**
 * \brief      Couleur possible pour un Point.
 * \details   La table de correspondance de couleurs est disponible en modification par les accesseurs.
 */

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
