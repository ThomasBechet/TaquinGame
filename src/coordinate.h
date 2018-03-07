/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef COORDINATE_H
#define COORDINATE_H

/*Renommage pour d�signer une taille*/
typedef unsigned int size;

/*Enum�ration des diff�rentes directions possibles*/
typedef enum {
	Up,
	Right,
	Down,
	Left
} Direction;

/*Structure d'un vecteur*/
typedef struct {
	int x;
	int y;
} Vector;

/*Structure d'un rectangle*/
typedef struct {
	Vector corner;
	Vector size;
} Rect;

/*
 * @def : constructeur de vecteur
 *
 * @param x : composante x du vecteur
 * @param y : composante y du vecteur
 *
 * @return : retourne le nouveau vecteur
 */
Vector makeVector(int x, int y);

/*
 * @def : constructeur d'un rectangle
 *
 * @param corner : position/origine du rectangle (en haut � gauche)
 * @param size : dimensions du rectangle
 *
 * @return : retourne le nouveau rectangle
 */
Rect makeRect(Vector corner, Vector size);

/*
 * @def : convertis un syst�me de coordonn� 2D 
 *		en un syst�me lin�aire
 *
 * @param position : position � convertir
 * @param rect_x : largeur du syst�me 2D
 *
 * @return : position dans un espace lin�aire
 */
int coordToLinear(Vector position, size rect_x);

/*
 * @def : convertis une position lin�aire en un syst�me 2D
 *
 * @param position : la position lin�aire � convertir
 * @pram rect_x : largeur du syst�me 2D
 *
 * @param return : retourne la position dans un plan 2D
 */
Vector linearToCoord(int position, size rect_x);

/*
 * @def : permet de savoir si un position se trouve dans un rectangle
 *
 * @param position : coordonn�es du point
 * @pram rect : rectangle de teste
 *
 * @return : retourne un bool�en (0 ou 1) si le point se trouve dans le rectangle
 *		ou non.
 */
int intersect(Vector position, Rect rect);

#endif