/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef VIEWS_H
#define VIEWS_H

#include "game.h"

/*
 * @def : Accès à la vue du jeu (celle du plateau)
 *
 * @param state : états partagés
 */
void goGameView(SharedState* state);

/*
 * @def : Accès au menu principale
 *
 * @param state : états partagés
 */
void goMainView(SharedState* state);

/*
 * @def : Accès au menu de la selection de la taille du plateau
 *
 * @param state : états partagés
 */
void goSizeView(SharedState* state);

/*
 * @def : Accès au menu de selection des images
 *
 * @param state : états partagés
 */
void goImageView(SharedState* state);

/*
 * @def : Accès au menu des scores
 *
 * @param state : états partagés
 */
void goScoreView(SharedState* state);

#endif