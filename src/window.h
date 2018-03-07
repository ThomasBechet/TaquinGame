/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "coordinate.h"

#define SCREEN_X 1000
#define SCREEN_Y 700
#define SCREEN_COLOR 0xFFFFFF

/*
 * @def : Initialise le rendu ainsi que la fenêtre.
 *		Cette fonction doit être appelé manuellement et
 *		suivit de la fonction destroyWindow lors de la fin
 *		du programme. (abstraction de la bibliothèque graphique)
 *		
 */
void createWindow(void);

/*
 * @def : Détruit la fenêtre de rendu ainsi que le contexte de la
 *		bibliothèque graphique. Cette fonction doit être appelée 
 *		seulement si la fonction createWindow a été appelée.
 *		(abstraction de la bibliothèque graphique)
 */
void destroyWindow(void);

/*
 * @def : Commence le rendu d'une nouvelle image ce qui signifie que 
 *		l'écran est nettoyé avec la couleur SCREEN_COLOR.
 *		(abstraction de la bibliothçque graphique)
 */
void startDraw(void);

/*
 * @def : Termine le rendu de la nouvelle image a afficher en copiant la fenêtre
 *		virtuelle. Cette fonction doit être précédé de startDraw;
 *		(abstraction de la bibliothèque graphique)
 */
void stopDraw(void);

/*
 * @def : Obtient de la position de la souris sous la forme d'un vecteur
 *
 * @return : Le vecteur de la position de la souris
 */
Vector getMousePosition(void);

#endif