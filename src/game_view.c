/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "board.h"
#include "coordinate.h"
#include "window.h"
#include "generator.h"
#include "ui.h"
#include "score.h"
#include "textures_def.h"

#include <graph.h>
#include <stdio.h>
#include <assert.h>

/*
 * @def : Affichage de la scene principale (plateau + interface)
 *
 * @param board : le plateau à dessiner
 * @param board_image : l'image du plateau associé
 * @param ui : l'interface utilisateur
 * @param count : le nombre de coups courant
 */
void drawGameScene(const Board* board, const Image* board_image, const UI* ui, unsigned int count){
	char buf[10];

	ChargerImageFond(IMG_BACKGROUND_PATH); /*Fond d'écran*/
	drawBoard(board, board_image); /*Affichage du plateau*/
	drawUI(ui); /*Affichage de l'interface*/

	/*Affichage du compteur de score*/
	snprintf(buf, 10,"%u", count);
	EcrireTexte(10 + (IMG_PLATE_X / 2) - (TailleChaineEcran(buf, 2) / 2), 20 + (IMG_PLATE_Y / 2), buf, 2); /*Position centrée par rapport au sprite du compteur*/
}
/*
 * @def : Affichage de l'écran de fin de la partie en cas de victoire ou d'abandon
 *
 * @param won : Est-ce que le joueur à gagné ?
 * @param new_record : Est-ce un nouveau record ?
 * @param score : le score (record ou non) associé
 */
void drawGameEnd(int won, int new_record, const Score* score){
	char buf[30];

	assert(score);

	if(won){
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran("Victoire !", 2) / 2), SCREEN_Y / 2 - 40, "Victoire !", 2);

		snprintf(buf, 30, "Score: %upts", score->score);
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 35, buf, 2);

		if(new_record){
			ChoisirCouleurDessin(CouleurParComposante(230, 0, 0));
			snprintf(buf, 30, "Nouveau record !");
			EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 80, buf, 2);
			ChoisirCouleurDessin(0x290d00);
		}
		
	} else{
		EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran("Abandon !", 2) / 2), SCREEN_Y / 2 - 40, "Abandon !", 2);
	}

	snprintf(buf, 30, "Nombre de coups: %u", score->count);
	EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 - 15, buf, 2);
	snprintf(buf, 30, "Temps: %us", (unsigned int)(score->time / 1000000));
	EcrireTexte(SCREEN_X / 2 - (TailleChaineEcran(buf, 2) / 2), SCREEN_Y / 2 + 10, buf, 2);
}

/*
 * Vue du jeu
 */
void goGameView(SharedState* state){
	int running;
	int win;
	int new_record;
	unsigned long time_start;
	Board* board = NULL;
	Image* board_image = NULL;
	UI* ui = NULL;
	Event event;
	Score score;

	/*éléments de l'interface*/
	button giveup_button;
	button retry_button;
	button quit_button;
	image countplate;
	image endplate;

	/*Création de l'interface*/
	ui = createUI();
	
	/*Création des éléments du jeu*/
	giveup_button = addButton(ui, IMG_BUTTON_GIVEUP_PATH, makeVector(IMG_BUTTON_GIVEUP_X, IMG_BUTTON_GIVEUP_Y), makeVector((SCREEN_X / 2) - (IMG_BUTTON_GIVEUP_X / 2), SCREEN_Y - 40));
	countplate = addImage(ui, IMG_PLATE_PATH, makeVector(10, 10));
	board_image = createImage(state->board_image, state->image_size.x, state->image_size.y, state->board_size.x, state->board_size.y);
	board = createBoard(board_image, state->board_size.x, state->board_size.y, (SCREEN_X / 2) - (state->image_size.x / 2), (SCREEN_Y / 2) - (state->image_size.y / 2), 1, 1);
	
	/*Génération du plateau*/
	generateBoard(board);

	score.count = 0; /*Initialisation du nombre de coup à 0*/
	win = 0;

	/*Récupération du temps initial pour calculer le temps total écoulé durant la partie*/
	time_start = Microsecondes();

	running = 1;
	do
	{
		/*Affichage du jeu*/
		startDraw();
		drawGameScene(board, board_image, ui, score.count);
		stopDraw();

		/*Attente d'un évenement*/
		event = waitEvent(ui);

		/*Gérer les évenements par le plateau*/
		handleInput(board, &event, &score.count);

		/*Vérification du plateau*/
		if(isBoardCorrect(board)){
			running = 0;
			win = 1;
		}

		/*Si le joueur veut arrêter, on coupe la boucle*/
		if(event.type == KeyboardEvent && (event.keyboard == XK_Escape || event.id == giveup_button)){
			running = 0;
			win = 0;
		}

	} while(running);

	/*=END OF THE GAME=*/

	/*Création du nouveau score*/
	score.board_size = state->board_size;
	score.time = Microsecondes() - time_start;
	score.score = computeScore(score.count, (unsigned int)state->board_size.x, (unsigned int)state->board_size.y);

	/*Ajout des nouveaux boutons*/
	retry_button = addButton(ui, IMG_BUTTON_RETRY_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(SCREEN_X / 2 - (IMG_BUTTON_X / 2) + 90, SCREEN_Y - 200));
	quit_button = addButton(ui, IMG_BUTTON_QUIT_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(SCREEN_X / 2 - (IMG_BUTTON_X / 2) - 90, SCREEN_Y - 200));
	endplate = addImage(ui, IMG_ENDPLATE_PATH, makeVector(SCREEN_X / 2 - (IMG_ENDPLATE_X / 2), SCREEN_Y / 2 - (IMG_ENDPLATE_Y / 2)));

	/*Liaison entre les boutons*/
	bindButtonLeft(ui, retry_button, quit_button);
	bindButtonRight(ui, quit_button, retry_button);

	/*Désactiver le bouton d'abandon*/
	setButtonFocus(ui, retry_button);
	setButtonVisible(ui, giveup_button, 0);

	/*Ajouter le score dans le tableau des scores seulement lorsque le joueur a gagné*/
	if(win){
		/*S'il s'agit d'un nouveau record, la valeur 1 est retournée*/
		new_record = insertScore(state->scores, &score);
	}

	running = 1;
	do
	{
		/*Affichage de la scène avec l'écran de fin*/
		startDraw();
		drawGameScene(board, board_image, ui, score.count);
		if(win){
			drawGameEnd(1, new_record, &score);
		} else{
			drawGameEnd(0, 0, &score);
		}
		stopDraw();

		/*Attente d'un évenement*/
		event = waitEvent(ui);

		if(event.id == retry_button){
			state->view_state = GameView;
			running = 0;
		} else if(event.id == quit_button){
			state->view_state = MainView;
			running = 0;
		}

	} while(running);
	
	/*Libération de la mémoire en détruisant tous les éléments*/
	destroyUI(ui);
	destroyBoard(board);
	destroyImage(board_image);
}