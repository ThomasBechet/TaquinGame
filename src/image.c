/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "image.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 * Génération de l'image
 */
Image* createImage(const char* file_name, size x, size y, size cut_x, size cut_y){
	Image* image = NULL;
	unsigned int i, j;
	unsigned int tile_x, tile_y;
	
	/*Assurance de travailler avec des valeurs possibles et utilisables*/
	assert(x > 0U && y > 0U && cut_x > 0U && cut_y > 0U);
	
	/*Création de l'image*/
	image = (Image*)malloc(sizeof(Image));
	assert(image);
	
	/*Création des uvs des tuiles*/
	image->uvs = (Rect*)malloc(cut_x * cut_y * sizeof(Rect));
	assert(image->uvs);
	
	/*Copie du nom de l'image*/
	strncpy(image->texture_name, file_name, IMAGE_NAME_MAX);
	
	/*Découpe de l'image*/
	tile_x = x / cut_x; /*Déduction de la hauteur et de la largeur d'une tuile*/
	tile_y = y / cut_y;
	for(j = 0U; j < cut_y; j++){
		for(i = 0U; i < cut_x; i++){
			image->uvs[j * cut_x + i] = makeRect(makeVector(i * tile_x, j * tile_y), makeVector(tile_x, tile_y));
		}
	}
	
	return image;
}

/*
 * Destruction de l'image
 */
void destroyImage(Image* image){
	free(image->uvs);
	free(image);
}

/*
 * Dimensions d'une tuile
 */
Vector getTileSize(const Image* image){	
	assert(image);

	/*Les tuiles ayant toutes les mêmes dimensions, on peut prendre la taille de la première tuile*/
	return image->uvs[0].size;
}

