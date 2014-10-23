/**
 * \file	pipes.h
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Declaration des fonctions relatives au pipes pour le jeu Petits chevaux.
 * \details    Les pipes sont organisés de cette maniere :
 * 0 -> Entree du main depuis joueurs
 * 1 -> sortie du main vers joueur 1
 * 2 -> sortie du main vers joueur 2
 * 3 -> sortie du main vers joueur 3
 * 4 -> sortie du main vers joueur 4
 * 5 -> sortie du joueur 1 vers joueur 2
 * 6 -> sortie du joueur 2 vers joueur 3
 * 7 -> sortie du joueur 3 vers joueur 4
 * 8 -> sortie du joueur 4 vers joueur 1
 */

#ifndef __PIPES_H__
#define __PIPES_H__
	
int creation_pipes(int ** pipes);
	
int pipes_fils_start_close(int num_fils, int ** pipes);
int pipes_fils_end_close(int num_fils, int ** pipes);

int pipes_pere_start_close(int ** pipes);
int pipes_pere_end_close(int ** pipes);

#endif
