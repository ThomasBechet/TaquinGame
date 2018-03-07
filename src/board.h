/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef BOARD_H
#define BOARD_H

#include "coordinate.h"
#include "image.h"
#include "ui.h"

/*une tuile a un identificateur (un int)*/
typedef int tile;

/*Structure du plateau*/
typedef struct {
	tile* tiles;
	Vector size;
	Vector pos;
	Vector tile_size;
	Vector tile_bearing;
} Board;

/*
 * @def : crée un tableau remplit de tuiles (id)
 *		de 0 à (x * y). La fonction destroyBoard doit
 *		être appelé pour désallouer la mémoire
 * 
 * @param x : largeur du tableau
 * @param y : hauteur du tableau
 *
 * @return : retourne le tableau
 */
Board* createBoard(const Image* image, size x, size y, int pos_x, int pos_y, int bearing_x, int bearing_y);

/*
 * @def : déalloue la mémoire du tableau
 *
 * @param board : le tableau
 */
void destroyBoard(Board* board);

/*
 * @def : dessine le tableau à partir de l'image
 *
 * @param board : le tableau à dessiner
 * @param image : l'image à partir de laquelle le tableau va
 *		être dessiné
 */
void drawBoard(const Board* board, const Image* image);

/*
 * @def: permet de savoir si l'état du plateau actuel
 *		est correct ou non
 *
 * @param board: le plateau à vérifier
 *
 * @return: vrai si le tableau est correct, faux s'il
 		ne l'est pas
 */
int isBoardCorrect(const Board* board);

/*
 * @def: échange deux tuiles du tableau indiquées aux positions.
 *
 * @param board: plateau des tuiles à échanger
 * @param pos1: position de la tuile 1 (sur le plateau)
 * @param pos2: position de la tuile 2 (sur la plateau)
 */
int swapTile(Board* board, Vector pos1, Vector pos2);

/*
 * @def: permet d'obtenir la position de la tuile invisible,
 *		celle qui sert d'espace de manoeuvre pour les autres tuiles.
 *
 * @param board: plateau dans lequel chercher
 *
 * @return: la position de la tuile sur le plateau
 */
Vector getBlankPosition(const Board* board);
 
 /*
  * @def: déplace la tuile invisible dans la direction donnée.
  *		Cette fonction permet de simplifier le déplacement d'une 
  *		tuile "visible" en déplaçant la tuile invisible par un simple swap.
  *		la fonction vérifie si le déplacement demandé est possible.
  *		Si le déplacement n'est pas possible, l'état du plateau est laissé
  *		inchangé.
  *
  *	@param board: plateau dans lequel on modifie la position de la tuile
  * @param direction: direction de déplacement de la tuile invisible
  *
  * @return: vrai si la tuile a changé de position sinon non
  */
 int moveBlank(Board* board, Direction direction);
 
 /*
  * @def: permet d'obtenir le rectangle d'une tuile relatif à la fenêtre
  *
  * @param board: plateau dans lequel chercher
  * @param tile_pos: position de la tuile dans le plateau dont on veut obtenir le rectangle
  *
  * @return: le rectangle de la tuile
  */
Rect getTileRect(const Board* board, Vector tile_pos);

/*
 * @def: fonction permettant de gérer les mouvements de tuiles du plateau avec
 *		la souris ou le clavier. Pour cela, un évenement doit être passé à la fonction
 *		afin de connaître les états souris et clavier.
 *
 * @param board: plateau à modifier
 * @param event: évenement préalablement modifié par l'interface utilisateur
 * @param count: le nombre de coup à modifier si il y a eu un mouvement de tuile
 */
void handleInput(Board* board, Event* event, unsigned int* count);

#endif