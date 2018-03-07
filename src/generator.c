/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "generator.h"
#include "board.h"
#include "coordinate.h"

#include <time.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Mélange du plateau
 */
void generateBoard(Board* board){
	unsigned int i;
	unsigned int rand_pos;
	unsigned int bx;
	unsigned int by;

	assert(board);

	srand((unsigned int)time(NULL));

	bx = board->size.x;
	by = board->size.y;

	/*Mélange avec un grand nombre d'itérations afin s'assurer un mélange consistant*/
	for(i=0;i<3000;i++){

		/*Génération d'une direction*/
		rand_pos = (rand() % 4);

		/*Application de la direction à la tuile "blank"*/
		if(rand_pos == Up){
			moveBlank(board, Up);
		} else if(rand_pos == Right){
			moveBlank(board, Right);
		} else if(rand_pos == Down){
			moveBlank(board, Down);
		} else if(rand_pos == Left){
			moveBlank(board, Left);
		}

	}

	/*Translation de la tuile "blank" vers l'origine du plateau
	  afin d'obtenir la situation initiale du jeu*/
	Vector vec = getBlankPosition(board);
	for(i = 0; i <= vec.x; i++){
		moveBlank(board, Left);
	}
	for(i = 0 ; i < vec.y; i++){
		moveBlank(board, Up);
	}
}






