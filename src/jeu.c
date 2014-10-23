#include <stdio.h>
#include <stdlib.h>

int premier_joueur(void) {
	char buff[10]={0};

	printf("Quel sera le premier joueur ?\n");
	
	while (buff[0]>'4'||buff[0]<'1') {
		//fflush(stdout);
		printf("\nEntrez un nombre entre 1 et 4 : ");
		fgets(buff, sizeof(buff), stdin);
	}
	
	printf("Le joueur %d commence ! \n\n", (buff[0]-'0'));
	return (int) (buff[0]-'0');
}


//je_joue(num_fils);

//je_fais_passer_le_message();

 /**
 * \brief      Couleur possible pour un Point.
 * \details   La table de correspondance de couleurs est disponible en modification par les accesseurs.
 */

/**
 * \brief       Creer le plateau et l'initialise a 0
 * \details
 * \return    le pointeur \a sur le tableau cree
 */


/**
 * Structure transitant du programme principal vers les joueurs. Elle informe les joueurs du prochain qui doit jouer.
 */
 


/**
 * Structure transitant des joueurs vers le programme principal. Elle informe le programme principal du résultat du de, de la nouvelle position du joueur.
 */



/**
 * Structure transitant des joueurs vers les joueurs. Elle informe les autres joueurs de la nouvelle position du joueur
 */


//typedef enum
//{
//   COLOR_BLUE,               /*!< Couleur bleu (0,0,255)               */
//   COLOR_DARK_RED,      /*!< Couleur rouge sombre (64,0,0)  */
//   COLOR_OLIVE              /*!< Couleur olive (51,51,0)               */
//}
