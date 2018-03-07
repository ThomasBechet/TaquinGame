/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "coordinate.h"
#include "window.h"
#include "ui.h"
#include "textures_def.h"

#include <graph.h>
#include <string.h>

/*
 * Vue de séléction des images
 */
void goImageView(SharedState* state){
	int running;
	UI* ui = NULL;
	Event event;

	button back_button;
	button snake_image;
	button lune_image;
	button waterfall_image;
	button totoro_image;
	button temple_image;
	button stawa_image;

	/*Création de l'interface utilisateur*/
	ui = createUI();

	/*Création des boutons/images*/
	back_button = addButton(ui, IMG_BUTTON_BACK_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector((SCREEN_X / 2) - (IMG_BUTTON_X / 2), 550));
	snake_image = addButton(ui, IMG_SNAKE_TN_PATH, makeVector(IMG_SNAKE_TN_X, IMG_SNAKE_TN_Y), makeVector(320, 230));
	lune_image = addButton(ui, IMG_LUNE_TN_PATH, makeVector(IMG_LUNE_TN_X, IMG_LUNE_TN_Y), makeVector(640, 20));
	waterfall_image = addButton(ui, IMG_WATERFALL_TN_PATH, makeVector(IMG_WATERFALL_TN_X, IMG_WATERFALL_TN_Y), makeVector(640, 365));
	totoro_image = addButton(ui, IMG_TOTORO_TN_PATH, makeVector(IMG_TOTORO_TN_X, IMG_TOTORO_TN_Y), makeVector(320, 20));
	temple_image = addButton(ui, IMG_TEMPLE_TN_PATH, makeVector(IMG_TEMPLE_TN_X, IMG_TEMPLE_TN_Y), makeVector(20, 50));
	stawa_image = addButton(ui, IMG_STAWA_TN_PATH, makeVector(IMG_STAWA_TN_X, IMG_STAWA_TN_Y), makeVector(50, 430));

	/*Configuration des liens entre les images (pour le clavier)*/
	bindButtonTop(ui, back_button, snake_image);
	bindButtonLeft(ui, back_button, stawa_image);
	bindButtonRight(ui, back_button, waterfall_image);
	bindButtonDown(ui, snake_image, back_button);
	bindButtonRight(ui, snake_image, lune_image);
	bindButtonLeft(ui, snake_image, temple_image);
	bindButtonTop(ui, snake_image, totoro_image);
	bindButtonDown(ui, lune_image, back_button);
	bindButtonLeft(ui, lune_image, totoro_image);
	bindButtonDown(ui, lune_image, waterfall_image);
	bindButtonRight(ui, temple_image, totoro_image);
	bindButtonDown(ui, temple_image, stawa_image);
	bindButtonLeft(ui, totoro_image, temple_image);
	bindButtonRight(ui, totoro_image, lune_image);
	bindButtonDown(ui, totoro_image, snake_image);
	bindButtonLeft(ui, waterfall_image, snake_image);
	bindButtonDown(ui, waterfall_image, back_button);
	bindButtonTop(ui, waterfall_image, lune_image);
	bindButtonRight(ui, stawa_image, back_button);
	bindButtonTop(ui, stawa_image, temple_image);

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

		/*Choix des images*/
		if(event.id == back_button){
			running = 0;
			state->view_state = MainView;
		} else if(event.id == snake_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_SNAKE_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_SNAKE_X, IMG_SNAKE_Y);
		} else if(event.id == lune_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_LUNE_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_LUNE_X, IMG_LUNE_Y);
		} else if(event.id == waterfall_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_WATERFALL_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_WATERFALL_X, IMG_WATERFALL_Y);
		} else if(event.id == totoro_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_TOTORO_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_TOTORO_X, IMG_TOTORO_Y);
		} else if(event.id == temple_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_TEMPLE_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_TEMPLE_X, IMG_TEMPLE_Y);
		} else if(event.id == stawa_image){
			running = 0;
			state->view_state = SizeView;
			strncpy(state->board_image, IMG_STAWA_PATH, IMAGE_NAME_MAX);
			state->image_size = makeVector(IMG_STAWA_X, IMG_STAWA_Y);
		}

	} while(running);

	/*Destruction de l'interface*/
	destroyUI(ui);
}