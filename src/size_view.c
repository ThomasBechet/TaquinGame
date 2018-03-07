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
#include <stdio.h>

#define MAX_SIZE 8
#define MIN_SIZE 3

/*
 * Vue de selection de la taille du plateau
 */
void goSizeView(SharedState* state){
	int running;
	unsigned int middle_x, middle_y;
	Vector board_size;
	char buf[2];

	UI* ui = NULL;
	Event event;
	button back_button;
	button upx_button;
	button downx_button;
	button upy_button;
	button downy_button;
	button launch_button;
	image scoreplate_sprite;

	/*Taille initiale du plateau*/
	board_size = makeVector(3, 3);

	/*Simplification d'écriture*/
	middle_x = SCREEN_X / 2;
	middle_y = SCREEN_Y / 2;

	/*Création de l'interface*/
	ui = createUI();

	/*Ajout des éléments de l'interface*/
	back_button = addButton(ui, IMG_BUTTON_BACK_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(middle_x - (IMG_BUTTON_X / 2), 550));
	upx_button = addButton(ui, IMG_ARROW_UP_PATH, makeVector(IMG_ARROW_X, IMG_ARROW_Y), makeVector(middle_x - 70 - IMG_ARROW_X, middle_y - 130));
	upy_button = addButton(ui, IMG_ARROW_UP_PATH, makeVector(IMG_ARROW_X, IMG_ARROW_Y), makeVector(middle_x + 70, middle_y - 130));
	downx_button = addButton(ui, IMG_ARROW_DOWN_PATH, makeVector(IMG_ARROW_X, IMG_ARROW_Y), makeVector(middle_x - 70 - IMG_ARROW_X, middle_y + 70));
	downy_button = addButton(ui, IMG_ARROW_DOWN_PATH, makeVector(IMG_ARROW_X, IMG_ARROW_Y), makeVector(middle_x + 70, middle_y + 70));
	launch_button = addButton(ui, IMG_BUTTON_LAUNCH_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector(middle_x - (IMG_BUTTON_X / 2), 70));
	scoreplate_sprite = addImage(ui, IMG_SCOREPLATE_PATH, makeVector(middle_x - (IMG_SCOREPLATE_X / 2), middle_y - (IMG_SCOREPLATE_Y / 2)));
	
	/*Configuration des boutons pour le clavier*/
	bindButtonDown(ui, launch_button, upx_button);
	bindButtonTop(ui, upx_button, launch_button);
	bindButtonRight(ui, upx_button, upy_button);
	bindButtonDown(ui, upx_button, downx_button);
	bindButtonTop(ui, upy_button, launch_button);
	bindButtonLeft(ui, upy_button, upx_button);
	bindButtonDown(ui, upy_button, downy_button);
	bindButtonTop(ui, downx_button, upx_button);
	bindButtonRight(ui, downx_button, downy_button);
	bindButtonDown(ui, downx_button, back_button);
	bindButtonTop(ui, downy_button, upy_button);
	bindButtonLeft(ui, downy_button, downx_button);
	bindButtonDown(ui, downy_button, back_button);
	bindButtonTop(ui, back_button, downx_button);

	running = 1;
	do
	{
		/*Affichage de la scene*/
		startDraw();
		ChargerImageFond(IMG_BACKGROUND_PATH);
		drawUI(ui);
		TailleSupPolice(50);
		ChoisirCouleurDessin(0x290d00);
		snprintf(buf,2,"%d", board_size.x);
		EcrireTexte(middle_x - 125, middle_y, buf, 2);
		snprintf(buf,2,"%d", board_size.y);
		EcrireTexte(middle_x + 125, middle_y, buf, 2);
		stopDraw();

		/*Attente d'un événement*/
		event = waitEvent(ui);

		/*Gestion de l'événement*/
		if(event.id == back_button){
			running = 0;
			state->view_state = ImageView;
		} else if(event.id == upx_button){
			board_size.x++;
			board_size.x = (board_size.x > MAX_SIZE) ? MAX_SIZE : board_size.x; /*Taille x++*/
			board_size.x = (board_size.x < MIN_SIZE) ? MIN_SIZE : board_size.x;
		} else if(event.id == upy_button){
			board_size.y++;
			board_size.y = (board_size.y > MAX_SIZE) ? MAX_SIZE : board_size.y; /*Taille y++*/
			board_size.y = (board_size.y < MIN_SIZE) ? MIN_SIZE : board_size.y;
		} else if(event.id == downx_button){
			board_size.x--;
			board_size.x = (board_size.x > MAX_SIZE) ? MAX_SIZE : board_size.x; /*Taille x--*/
			board_size.x = (board_size.x < MIN_SIZE) ? MIN_SIZE : board_size.x;
		} else if(event.id == downy_button){
			board_size.y--;
			board_size.y = (board_size.y > MAX_SIZE) ? MAX_SIZE : board_size.y; /*Taille y--*/
			board_size.y = (board_size.y < MIN_SIZE) ? MIN_SIZE : board_size.y;
		} else if(event.id == launch_button){
			running = 0;
			state->board_size = board_size;
			state->view_state = GameView;
		}

	} while(running);

	/*Destruction de l'interface*/
	destroyUI(ui);
}