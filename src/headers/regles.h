/**
 * \file	regles.h
 * \author	AOUN Abel et DOUCHET Maximilien
 * \brief       Declaration des fonctions relatives aux regles pour le jeu Petits chevaux.
 */

#ifndef __REGLES_H__
#define __REGLES_H__

int cest_mon_tour(int num_fils, struct_debuttour * debuttourlu);

int nouvelle_position(int num_fils, int positionjoueur, int resultatde, int *danslescalier);

int le_joueur_a_gagne(struct_retourjeu * retourjeulu);

void conflit_entre_deux_joueur(struct_pendantjeu * pendantjeulu, int * positionjoueur);

void position_escalier(int num_fils, int positionjoueur, int resultatde);

#endif
