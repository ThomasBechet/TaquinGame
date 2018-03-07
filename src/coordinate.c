/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "coordinate.h"

#include <assert.h>

/*
 * Création d'un vecteur
 */
Vector makeVector(int x, int y){
	Vector vec;
	
	vec.x = x;
	vec.y = y;
	
	/*Passage par valeur car il s'agit d'une petite structure
	  et allouer de la mémoire rend le code moins lisible*/
	return vec;
}

/*
 * Création d'un rectangle
 */
Rect makeRect(Vector corner, Vector size){
	Rect rect;
	
	rect.corner = corner;
	rect.size = size;
	
	return rect;
}

/*
 * Conversion de coordonnées
 */
int coordToLinear(Vector position, size rect_x){
	assert(rect_x > 0U); /*Espace à 0 de largeur n'existe pas*/
	
	return position.y * (int)rect_x + position.x;
}

/*
 * Conversion de coordonnées
 */
Vector linearToCoord(int linear, size rect_x){
	Vector coord;
	
	assert(rect_x > 0U);
	
	coord.y = linear / rect_x;
	coord.x = linear % rect_x;
	
	return coord;
}

/*
 * Intersection entre un rectangle et un point
 */
int intersect(Vector position, Rect rect){
	int x, y;
	int xx, yy;
	
	x = rect.corner.x;
	y = rect.corner.y;
	xx = x + rect.size.x;
	yy = y + rect.size.y;
	
	if(position.x >= x && position.y >= y && position.x <= xx && position.y <= yy)
		return 1;
	else
		return 0;
}

