/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "game.h"
#include "window.h"
#include "views.h"

/*
 * Lancement du jeu
 */
void startGame(void){
	int running;
	SharedState shared_state; /*Création de la zone de mémoire partagée*/
	
	shared_state.view_state = MainView; /*Initialiser la vue à la vue principale*/
	shared_state.scores = loadScore(); /*Chargement des scores depuis le fichier*/
	
	createWindow(); /*Ouverture de la fenêtre*/
	
	running = 1;	
	while(running){ /*Boucle principale*/
		
		/*Selection de la vue active*/
		if(shared_state.view_state == MainView){
			goMainView(&shared_state);
		} else if(shared_state.view_state == ImageView){
			goImageView(&shared_state);
		} else if(shared_state.view_state == SizeView){
			goSizeView(&shared_state);
		} else if(shared_state.view_state == GameView){
			goGameView(&shared_state);
		} else if(shared_state.view_state == ScoreView){
			goScoreView(&shared_state);
		} else if(shared_state.view_state == NoneView){
			running = 0;
		}
		
	}

	storeScore(shared_state.scores); /*Sauvegarde des scores*/
	
	destroyWindow(); /*Fermeture de la fenêtre*/
}