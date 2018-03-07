/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "window.h"
#include "ui.h"
#include "textures_def.h"

#include <graph.h>

/*
 * Vue du menu principal
 */
void goMainView(SharedState* state){
	int running;
	UI* ui = NULL;
	Event event;
	button play_button;
	button quit_button;
	button score_button;
	
	/*Création de l'interface*/
	ui = createUI();

	/*Ajout des boutons*/
	play_button = addButton(ui, IMG_BUTTON_PLAY_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 200));
	score_button = addButton(ui, IMG_BUTTON_SCORE_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 320));
	quit_button = addButton(ui, IMG_BUTTON_QUIT_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(500 - (IMG_BUTTON_X / 2), 420));
	
	/*Configuration des boutons*/
	bindButtonDown(ui, play_button, score_button);
	bindButtonTop(ui, score_button, play_button);
	bindButtonDown(ui, score_button, quit_button);
	bindButtonTop(ui, quit_button, score_button);

	running = 1;
	do
	{
		/*Affichage de la scene*/
		startDraw();
		ChargerImageFond(IMG_BACKGROUND_PATH);
		drawUI(ui);
		stopDraw();

		/*Attente d'un évenement*/
		event = waitEvent(ui);

		/*Gestion des boutons*/
		if(event.id == play_button){
			running = 0;
			state->view_state = ImageView;
		} else if(event.id == score_button){
			running = 0;
			state->view_state = ScoreView;
		} else if(event.id == quit_button){
			running = 0;
			state->view_state = NoneView;
		}
	} while(running);
	
	destroyUI(ui);
}