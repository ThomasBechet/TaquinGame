/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef GENERATOR_H
#define GENERATOR_H

#include "board.h"

/*
 * @def : Mélange les tuiles du plateau en assurant
 *		la résolvabilité du puzzle
 *
 * @param board : le plateau à mélanger
 */
void generateBoard(Board* board);

#endif