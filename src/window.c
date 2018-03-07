/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "window.h"

#include <graph.h>
#include <unistd.h>

/*
 * Création de la fenêtre
 */
void createWindow(void){
	InitialiserGraphique();
	CreerFenetre(200, 100, SCREEN_X, SCREEN_Y);
	ChoisirTitreFenetre("Taquin");
	ChoisirCurseur(3);
}

/*
 * Destruction d'une window
 */
void destroyWindow(void){
	FermerGraphique();
}

/*
 * Commencer l'affichage
 */
void startDraw(void){
	ChoisirEcran(1);
	EffacerEcran(SCREEN_COLOR);
}

/*
 * Terminer l'affichage
 */
void stopDraw(void){
	/*Copie de l'écran virtuel vers l'écran visible pour éviter l'apparition des images*/
	CopierZone(1, 0, 0, 0, SCREEN_X, SCREEN_Y, 0, 0);
}

/*
 * Obtention des coordonnées de la souris
 */
Vector getMousePosition(void){
	Vector mouse_pos;
	
	SourisPosition();
	
	/*Récupération des variables globales*/
	mouse_pos.x = _X;
	mouse_pos.y = _Y;
	
	return mouse_pos;
}

