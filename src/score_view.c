/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "views.h"
#include "window.h"
#include "ui.h"
#include "score.h"
#include "textures_def.h"

#include <graph.h>
#include <stdio.h>

/*
 * Affichage de la scene
 */
void drawScoreScene(const UI* ui, SharedState* state){
	char buf[50];
	Score* ptr = NULL;
	unsigned int i, y;

	/*Affichage du background et de l'interface*/
	startDraw();
	ChargerImageFond(IMG_BACKGROUND_PATH);
	drawUI(ui);

	/*Affichage des scores*/
	ptr = state->scores; /*Simplification de lecture*/
	ChoisirCouleurDessin(0x290d00);
	y = 100;
	for(i = 0; i < MAX_SAVE; i++){

		/*Si les valeurs ne sont pas nulles c'est qu'il s'agit d'un score valide*/
		if(ptr[i].score != 0 || ptr[i].count != 0 || ptr[i].time != 0){
			snprintf(buf, 50, "%u. %upts %ucoups %us %ux%u", i + 1, ptr[i].score, ptr[i].count, (unsigned int)(ptr[i].time / 1000000), (unsigned int)ptr[i].board_size.x, (unsigned int)ptr[i].board_size.y);
			EcrireTexte(SCREEN_X / 2 - TailleChaineEcran(buf, 2) / 2, y, buf, 2);
		} else{ /*Dans le cas contraire on affiche "rien"*/
			snprintf(buf, 50, "-----");
			EcrireTexte(SCREEN_X / 2 - TailleChaineEcran(buf, 2) / 2, y, buf, 2);
		}
		
		y += 40; /*Avancement dans la verticalité*/
	}

	stopDraw();
}

/*
 * Vue des scores
 */
void goScoreView(SharedState* state){
	int running;
	UI* ui = NULL;
	Event event;
	button back_button;

	/*Création de l'interface*/
	ui = createUI();

	/*Ajout du bouton de retour*/
	back_button = addButton(ui, IMG_BUTTON_BACK_PATH, makeVector(IMG_BUTTON_X, IMG_BUTTON_Y), makeVector((SCREEN_X / 2) - (IMG_BUTTON_X / 2), 550));

	running = 1;
	do
	{
		/*Affichage de la scene*/
		drawScoreScene(ui, state);

		/*Attente d'un événement*/
		event = waitEvent(ui);

		/*Appel du bouton retour*/
		if(event.id == back_button){
			running = 0;
			state->view_state = MainView;
		}
	} while(running);

	/*Destruction de l'interface*/
	destroyUI(ui);
}