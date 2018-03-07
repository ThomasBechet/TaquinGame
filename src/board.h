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
 * @def : cr�e un tableau remplit de tuiles (id)
 *		de 0 � (x * y). La fonction destroyBoard doit
 *		�tre appel� pour d�sallouer la m�moire
 * 
 * @param x : largeur du tableau
 * @param y : hauteur du tableau
 *
 * @return : retourne le tableau
 */
Board* createBoard(const Image* image, size x, size y, int pos_x, int pos_y, int bearing_x, int bearing_y);

/*
 * @def : d�alloue la m�moire du tableau
 *
 * @param board : le tableau
 */
void destroyBoard(Board* board);

/*
 * @def : dessine le tableau � partir de l'image
 *
 * @param board : le tableau � dessiner
 * @param image : l'image � partir de laquelle le tableau va
 *		�tre dessin�
 */
void drawBoard(const Board* board, const Image* image);

/*
 * @def: permet de savoir si l'�tat du plateau actuel
 *		est correct ou non
 *
 * @param board: le plateau � v�rifier
 *
 * @return: vrai si le tableau est correct, faux s'il
 		ne l'est pas
 */
int isBoardCorrect(const Board* board);

/*
 * @def: �change deux tuiles du tableau indiqu�es aux positions.
 *
 * @param board: plateau des tuiles � �changer
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
  * @def: d�place la tuile invisible dans la direction donn�e.
  *		Cette fonction permet de simplifier le d�placement d'une 
  *		tuile "visible" en d�pla�ant la tuile invisible par un simple swap.
  *		la fonction v�rifie si le d�placement demand� est possible.
  *		Si le d�placement n'est pas possible, l'�tat du plateau est laiss�
  *		inchang�.
  *
  *	@param board: plateau dans lequel on modifie la position de la tuile
  * @param direction: direction de d�placement de la tuile invisible
  *
  * @return: vrai si la tuile a chang� de position sinon non
  */
 int moveBlank(Board* board, Direction direction);
 
 /*
  * @def: permet d'obtenir le rectangle d'une tuile relatif � la fen�tre
  *
  * @param board: plateau dans lequel chercher
  * @param tile_pos: position de la tuile dans le plateau dont on veut obtenir le rectangle
  *
  * @return: le rectangle de la tuile
  */
Rect getTileRect(const Board* board, Vector tile_pos);

/*
 * @def: fonction permettant de g�rer les mouvements de tuiles du plateau avec
 *		la souris ou le clavier. Pour cela, un �venement doit �tre pass� � la fonction
 *		afin de conna�tre les �tats souris et clavier.
 *
 * @param board: plateau � modifier
 * @param event: �venement pr�alablement modifi� par l'interface utilisateur
 * @param count: le nombre de coup � modifier si il y a eu un mouvement de tuile
 */
void handleInput(Board* board, Event* event, unsigned int* count);

#endif