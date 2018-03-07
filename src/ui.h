/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef UI_H
#define UI_H

#include "coordinate.h"

/*id de la touche du clavier*/
typedef int key;
/*id d'un bouton*/
typedef unsigned int button;
/*id d'une image*/
typedef unsigned int image;

/*Structure d'un sprite (abstraction de la bibliothèque graphique)*/
typedef struct {
	Vector pos;
	int id;
} Sprite;

/*Structure d'un bouton (normalement non accessible par l'utilisateur).
  Cette structure est uniquement gérée par l'interface*/
typedef struct {
	Sprite sprite;
	Rect box;
	button top;
	button down;
	button left;
	button right;
	char visible; 
} ButtonStorage;

/*Structure d'une image, uniquement gérée par l'interface*/
typedef struct {
	Sprite sprite;
	char visible;
} ImageStorage;

/*Structure de l'interface utilisateur*/
typedef struct {
	ButtonStorage* buttons;
	ImageStorage* images;
	unsigned int nbr_buttons;
	unsigned int nbr_images;
	button focus_button;
} UI;

/*Enumération des types d'événements*/
typedef enum {
	KeyboardEvent,
	MouseEvent
} EventType;

/*Structure d'événement*/
typedef struct {
	unsigned int id; /*Id de l'élément de l'interface en lien avec l'événement*/
	EventType type;
	Vector mouse;
	key keyboard;
} Event;

/*
 * @def : création d'un interface et initialise ses variables
 *		(début du cycle de vie)
 */
UI* createUI(void);
/*
 * @def : détruit l'interface et désalloue sa mémoire (fin de cycle de vie)
 *
 * @param ui : l'interface à détruire
 */
void destroyUI(UI* ui);

/*
 * @def : affiche le contenu d'un interface à l'écran
 *		(l'appel de la fonction doit se trouver entre un startdraw et un stopdraw
 *		pour être visible)
 *
 * @param ui : l'interface à dessiner
 */
void drawUI(const UI* ui);

/*
 * @def : attend l'arrivée d'un événement et renvoie les informations
 *		nécéssaires à cet événement. La fonction est bloquante.
 *
 * @param ui : l'interface auquel on veut récupérer un événement
 *
 * @return : retourne la structure d'un événement constitué d'un type d'événement,
 *		de l'élément lié à l'événement et des sortis souris et clavier
 */
Event waitEvent(UI* ui);

/*
 * @def : ajoute un bouton, le bouton sera détruit à la fin de la vie de l'interface
 *
 * @param ui : l'interface auquel on veut ajouter un bouton
 * @param texture : chemin d'accès de la texture du bouton
 * @param size : dimensions de la boîte de collision du bouton
 * @param position : position du bouton sur l'écran (coordonnées)
 *
 * @return : retourne l'id du bouton créé. (l'id 0 est réservé pour signifier l'abscence de bouton)
 */
button addButton(UI* ui, const char* texture, Vector size, Vector position);

/*
 * @def : ajoute une image, l'image sera détruite à la destruction de l'interface
 *
 * @param ui : l'interface auquel on veut ajouter l'image
 * @param texture : chemin d'accès de la texture de l'image
 * @param position : position de l'image sur l'écran
 *
 * @return : retourne l'id de l'image créée. (l'id 0 est réservé pour signifier l'abscence d'image)
 */
image addImage(UI* ui, const char* texture, Vector position);

/*
 * @def : contrôle l'affichage d'un bouton
 *
 * @param ui : l'interface dans lequel on va chercher le bouton
 * @param id : l'id du bouton
 * @param visible : contrôle de l'affichage (booléen)
 */
void setButtonVisible(UI* ui, button id, int visible);
/*
 * @def : contrôle l'affichage d'une image
 * 
 * @param ui : l'interface dans lequel on va chercher l'image
 * @param id : l'id de l'image
 * @param visible : contrôle de l'affichage
 */
void setImageVisible(UI* ui, image id, int visible);

/*
 * @def : contrôle le focus d'un bouton. Cette option permet
 *		le bouton ayant le focus obtient un rectangle (en mode clavier)
 *
 * @param ui : l'interface dans lequel chercher le bouton
 * @param id : l'id du bouton
 */
void setButtonFocus(UI* ui, button id);

/*
 * @def : permet de lier deux boutons. Cela permet de se déplacer entre les différents
 *		boutons quand on utilise le clavier.
 *		Lien vers le haut
 *
 * @param ui : l'interface dans lequel chercher
 * @param id : id du bouton à lier
 * @param link : id du bouton avec lequel on veut lier
 */
void bindButtonTop(UI* ui, button id, button link);
/*
 * @def : permet de lier deux boutons. Cela permet de se déplacer entre les différents
 *		boutons quand on utilise le clavier.
 *		Lien vers le bas
 *
 * @param ui : l'interface dans lequel chercher
 * @param id : id du bouton à lier
 * @param link : id du bouton avec lequel on veut lier
 */
void bindButtonDown(UI* ui, button id, button link);
/*
 * @def : permet de lier deux boutons. Cela permet de se déplacer entre les différents
 *		boutons quand on utilise le clavier.
 *		Lien vers la droite
 *
 * @param ui : l'interface dans lequel chercher
 * @param id : id du bouton à lier
 * @param link : id du bouton avec lequel on veut lier
 */
void bindButtonRight(UI* ui, button id, button link);
/*
 * @def : permet de lier deux boutons. Cela permet de se déplacer entre les différents
 *		boutons quand on utilise le clavier.
 *		Lien vers la gauche
 *
 * @param ui : l'interface dans lequel chercher
 * @param id : id du bouton à lier
 * @param link : id du bouton avec lequel on veut lier
 */
void bindButtonLeft(UI* ui, button id, button link);

#endif