/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef GAME_H
#define GAME_H

#include "coordinate.h"
#include "image.h"
#include "score.h"

/*Différents états de vue*/
typedef enum {
	MainView,
	ImageView,
	SizeView,
	ScoreView,
	GameView,
	NoneView
} ViewState;

/*Zone mémoire partagée entre les vues*/
typedef struct {
	ViewState view_state;
	Vector board_size;
	char board_image[IMAGE_NAME_MAX];
	Vector image_size;
	Score* scores;
} SharedState;

/*
 * @def : Fonction de point d'encrage du jeu. Cette fonction doit
 *		être appelée dans le main
 */
void startGame(void);

#endif