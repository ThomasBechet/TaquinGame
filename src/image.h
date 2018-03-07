/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "coordinate.h"

/*Taille maximum du nom d'une image*/
#define IMAGE_NAME_MAX 30

/*Structure d'une image*/
typedef struct {
	Rect* uvs;
	char texture_name[IMAGE_NAME_MAX];
} Image;

/*
 * @def : fonction générant l'image en fonction de sa taille, du nombre de découpe
 *
 * @param file_name : nom de l'image
 * @param x : largeur de l'image (en pixels)
 * @param y : hauteur de l'image (en pixels)
 * @param cut_x : nombre de découpes horizontales
 * @param cut_y : nombre de découpes verticales
 *
 * @return : la nouvelle image générée
 */
Image* createImage(const char* file_name, size x, size y, size cut_x, size cut_y);

/*
 * @def : désalloue la mémoire d'une image
 *
 * @param image : l'image à désallouer
 */
void destroyImage(Image* image);

/*
 * @def : permet de connaître les dimensions d'une tuile découpée
 *		selon le nombre de découpe
 *
 * @param image : l'image des tuiles
 *
 * @return : vecteur représentant les dimensions de la tuile 
 */
Vector getTileSize(const Image* image);



#endif