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
 * @def : Initialise le rendu ainsi que la fen�tre.
 *		Cette fonction doit �tre appel� manuellement et
 *		suivit de la fonction destroyWindow lors de la fin
 *		du programme. (abstraction de la biblioth�que graphique)
 *		
 */
void createWindow(void);

/*
 * @def : D�truit la fen�tre de rendu ainsi que le contexte de la
 *		biblioth�que graphique. Cette fonction doit �tre appel�e 
 *		seulement si la fonction createWindow a �t� appel�e.
 *		(abstraction de la biblioth�que graphique)
 */
void destroyWindow(void);

/*
 * @def : Commence le rendu d'une nouvelle image ce qui signifie que 
 *		l'�cran est nettoy� avec la couleur SCREEN_COLOR.
 *		(abstraction de la biblioth�que graphique)
 */
void startDraw(void);

/*
 * @def : Termine le rendu de la nouvelle image a afficher en copiant la fen�tre
 *		virtuelle. Cette fonction doit �tre pr�c�d� de startDraw;
 *		(abstraction de la biblioth�que graphique)
 */
void stopDraw(void);

/*
 * @def : Obtient de la position de la souris sous la forme d'un vecteur
 *
 * @return : Le vecteur de la position de la souris
 */
Vector getMousePosition(void);

#endif