/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "ui.h"
#include "window.h"

#include <assert.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>

/*
 * Création de l'interface
 */
UI* createUI(void){
	UI* ui = NULL;

	/*Allocation de la mémoire de l'interface*/
	ui = (UI*)malloc(sizeof(UI));
	assert(ui);

	/*Allocation de la première image (emplacement symbolique)*/
	ui->images = (ImageStorage*)malloc(sizeof(ImageStorage));
	assert(ui->images);
	/*Allocation du premier bouton (emplacement symbolique)*/
	ui->buttons = (ButtonStorage*)malloc(sizeof(ButtonStorage));
	assert(ui->buttons);

	/*Initialisation du nombre des éléments à 0 (pas d'éléments)*/
	ui->nbr_buttons = 0;
	ui->nbr_images = 0;

	/*Initialiser le lien du bouton focus à NULL (aucun bouton focus)*/
	ui->focus_button = 0;

	return ui;
}

/*
 * Destruction de l'interface
 */
void destroyUI(UI* ui){
	unsigned int i;

	assert(ui);

	/*Libération des images*/
	for(i = 0; i < ui->nbr_buttons; i++){
		LibererSprite(ui->buttons[i].sprite.id);
	}
	for(i = 0; i < ui->nbr_images; i++){
		LibererSprite(ui->images[i].sprite.id);
	}

	/*Désallocation de la mémoire*/
	free(ui->images);
	free(ui->buttons);
	free(ui);
}

/*
 * Affichage de l'interface
 */
void drawUI(const UI* ui){
	unsigned int i;
	ButtonStorage* button = NULL; /*Simplification d'écriture*/

	assert(ui);

	/*Affichage des boutons*/
	for(i = 0; i < ui->nbr_buttons; i++){
		button = &ui->buttons[i];

		if(button->visible){ /*Si le bouton est visible, on le dessine*/
			AfficherSprite(button->sprite.id, button->sprite.pos.x, button->sprite.pos.y);

			/*Ajouter le rectangle noir s'il s'agit du bouton ayant le focus*/
			if(ui->focus_button == (i + 1)){
				ChoisirCouleurDessin(0x000000); /*Couleur noir*/
				DessinerRectangle(button->box.corner.x, button->box.corner.y, button->box.size.x, button->box.size.y);
			}
		}
	}

	/*Affichage des images*/
	for(i = 0; i < ui->nbr_images; i++){
		if(ui->images[i].visible)
			AfficherSprite(ui->images[i].sprite.id, ui->images[i].sprite.pos.x, ui->images[i].sprite.pos.y);
	}
}

/*
 * Attente des événements
 */
Event waitEvent(UI* ui){
	Event event;
	unsigned int i;

	assert(ui);

	event.id = 0; /*Initialisation de l'élément focus à NULL*/
	while(1){
		/*Cas de la souris*/
		if(SourisCliquee()){
			event.type = MouseEvent;
			event.mouse = getMousePosition();

			/*Detection de collision entre les boutons et le clique de la souris*/
			for(i = 0; i < ui->nbr_buttons; i++){
				if(intersect(event.mouse, ui->buttons[i].box)){
					event.id = i + 1; /*ID = pos + 1*/
				}
			}

			return event;

		/*Cas du clavier*/
		} else if(ToucheEnAttente()){
			event.type = KeyboardEvent;
			event.keyboard = Touche();

			/*Changement du bouton qui a le focus en fonction des flèches directionnelles*/
			if(event.keyboard == XK_Up){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].top) ui->focus_button = ui->buttons[ui->focus_button - 1].top;
				}
			} else if(event.keyboard == XK_Down){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].down) ui->focus_button = ui->buttons[ui->focus_button - 1].down;
				}
			} else if(event.keyboard == XK_Right){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].right) ui->focus_button = ui->buttons[ui->focus_button - 1].right;
				}
			} else if(event.keyboard == XK_Left){
				if(!ui->focus_button){
					if(ui->nbr_buttons > 0) ui->focus_button = 1;
				} else{
					if(ui->buttons[ui->focus_button - 1].left) ui->focus_button = ui->buttons[ui->focus_button - 1].left;
				}
			} else if(event.keyboard == XK_Return){
				if(ui->focus_button){
					event.id = ui->focus_button;
				}
			}

			return event;
		}

		/*Mise en pause le processus pour éviter une utilisation du CPU trop importante*/
		usleep(200);
	}
}

/*
 * Ajouter un bouton
 */
button addButton(UI* ui, const char* texture, Vector size, Vector position){
	assert(ui);

	/*Ajout d'un bouton*/
	ui->buttons = (ButtonStorage*)realloc(ui->buttons, (ui->nbr_buttons + 1) * sizeof(ButtonStorage));
	assert(ui->buttons);

	/*Configuration du nouveau bouton en fonction des paramètres*/
	ui->buttons[ui->nbr_buttons].box.corner = position;
	ui->buttons[ui->nbr_buttons].box.size = size;
	ui->buttons[ui->nbr_buttons].sprite.pos = position;
	ui->buttons[ui->nbr_buttons].sprite.id = ChargerSprite((char*)texture);
	ui->buttons[ui->nbr_buttons].visible = 1;
	ui->buttons[ui->nbr_buttons].top = 0;
	ui->buttons[ui->nbr_buttons].down = 0;
	ui->buttons[ui->nbr_buttons].left = 0;
	ui->buttons[ui->nbr_buttons].right = 0;

	/*Augmentation du nombre de bouton*/
	ui->nbr_buttons++;

	/*ID = pos + 1*/
	return (ui->nbr_buttons);
}

/* 
 * Ajout d'une image
 */
image addImage(UI* ui, const char* texture, Vector position){
	assert(ui);

	/*Allocation d'une nouvelle image*/
	ui->images = (ImageStorage*)realloc(ui->images, (ui->nbr_images + 1) * sizeof(ImageStorage));
	assert(ui->images);

	/*Configuration de la nouvelle image*/
	ui->images[ui->nbr_images].sprite.pos = position;
	ui->images[ui->nbr_images].sprite.id = ChargerSprite((char*)texture);
	ui->images[ui->nbr_images].visible = 1;

	/*Ajout d'une image*/
	ui->nbr_images++;

	return (ui->nbr_images);
}

/*
 * Contrôle du focus du bouton
 */
void setButtonFocus(UI* ui, button id){
	assert(ui);
	/*id 0 pour signifier qu'aucun bouton n'est focus*/
	ui->focus_button = id;
}

/*
 * Contrôle la visibilité d'un bouton
 */
void setButtonVisible(UI* ui, button id, int visible){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].visible = visible;
}
/*
 * Contrôle la visibilité d'une image
 */
void setImageVisible(UI* ui, image id, int visible){
	assert(ui);
	assert(id);
	ui->images[id - 1].visible = visible;
}

/*
 * Lien du bouton haut
 */
void bindButtonTop(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].top = link;
}
/*
 * Lien du bouton vers le bas
 */
void bindButtonDown(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].down = link;
}
/*
 * Lien du bouton vers la droite
 */
void bindButtonRight(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].right = link;
}
/*
 * Lien du bouton vers la gauche
 */
void bindButtonLeft(UI* ui, button id, button link){
	assert(ui);
	assert(id);
	ui->buttons[id - 1].left = link;
}