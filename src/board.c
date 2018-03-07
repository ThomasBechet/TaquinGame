/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include "board.h"
#include "window.h"

#include <stdlib.h>
#include <assert.h>
#include <graph.h>
#include <string.h>

/*
 * Création du tableau
 */
Board* createBoard(const Image* image, size x, size y, int pos_x, int pos_y, int bearing_x, int bearing_y){
	Board* board = NULL;
	unsigned int i;
	
	assert(image);
	assert(x > 0 && y > 0);
	
	/*Allocation du plateau sur le tas*/
	board = (Board*)malloc(sizeof(Board));
	assert(board);
	
	/*Attribution des paramètres du plateau*/
	board->size.x = x;
	board->size.y = y;
	board->pos.x = pos_x;
	board->pos.y = pos_y;
	board->tile_size = getTileSize(image);
	board->tile_bearing.x = bearing_x;
	board->tile_bearing.y = bearing_y;
	
	/*Allocation des tuiles*/
	board->tiles = (tile*)malloc(board->size.x * board->size.y * sizeof(tile));
	
	assert(board->tiles);
	
	/*Initialisation des id des tuiles dans l'ordre croissant: image de base*/
	for(i = 0; i < board->size.x * board->size.y; i++){
		board->tiles[i] = i;
	}
	
	return board;
}

/*
 * Libération de la mémoire du plateau
 */
void destroyBoard(Board* board){
	assert(board);
	
	free(board->tiles);
	free(board);
}

/*
 * Affichage du plateau en fonction de l'image
 */
void drawBoard(const Board* board, const Image* image){
	
	unsigned int i, j;
	size size_x, size_y;
	size tile_x, tile_y;
	int id;
	char buf[IMAGE_NAME_MAX];
	
	Vector bearing;
	Vector position;
	
	
	assert(board);
	assert(image);
	
	size_x = board->size.x;
	size_y = board->size.y;
	
	tile_x = getTileSize(image).x;
	tile_y = getTileSize(image).y;
	
	bearing = board->tile_bearing;
	position = board->pos;
	
	/*Affichage de chaque tuile (en utilisant leur rectangle) avec les uvs de la tuile de l'image associée (id)*/
	for(j = 0U; j < size_y; j++){
		for(i = 0U; i < size_x; i++){
			id = board->tiles[(unsigned int)coordToLinear(makeVector((int)i, (int)j), size_x)];
			
			/*Si l'id est 0 c'est qu'il s'agit de la tuile "blank", il ne faut pas l'afficher !*/
			if(id != 0){
				Rect uv = image->uvs[id];
				strncpy(buf, image->texture_name, IMAGE_NAME_MAX);
				ChargerImage(buf, position.x + i * (tile_x + bearing.x), position.y + j * (tile_y + bearing.y), uv.corner.x, uv.corner.y, uv.size.x, uv.size.y);
			}
		}
	}
	
}

/*
 * Le plateau est-il correct ?
 */
int isBoardCorrect(const Board* board){
	unsigned int i;
	size x, y;
	
	assert(board);
	x = board->size.x;
	y = board->size.y;
	
	/*Si les id des tuiles du plateau ne sont pas dans l'ordre croissant c'est que le plateau n'est pas correct*/
	for(i = 0U; i < x * y; i++){
		if(board->tiles[i] != i) return 0;
	}
	
	return 1;
}

/*
 * Echanger deux tuiles aux positions données
 */
int swapTiles(Board* board, Vector pos1, Vector pos2){
	size x, y;
	Rect rect;
	int id_temp;
	
	assert(board);
	
	x = board->size.x;
	y = board->size.y;
	
	/*Création d'un rectangle de la taille des dimensions du plateau*/
	rect = makeRect(makeVector(0, 0), makeVector(x - 1, y - 1));
	
	/*Vérifier si les positions sont bien comprises dans le plateau. Si oui, on peut échanger les poisitions (les id des tuiles images)*/
	if(intersect(pos1, rect), intersect(pos2, rect)){
		id_temp = board->tiles[coordToLinear(pos1, x)]; /*valeur temporaire pour le swap*/
		board->tiles[coordToLinear(pos1, x)] = board->tiles[coordToLinear(pos2, x)];
		board->tiles[coordToLinear(pos2, x)] = id_temp;

		return 1;
	}

	/*Un des points n'est pas dans le plateau*/
	return 0;
}

/*
 * Obtenir la position de la tuile "blank"
 */
Vector getBlankPosition(const Board* board){
	unsigned int i;
	unsigned int size;
	
	assert(board);
	
	size = board->size.x * board->size.y;
	
	for(i = 0U; i < size; i++){
		if(board->tiles[i] == 0) return linearToCoord(i, board->size.x); /*Espace linéaire vers espace 2D*/
	}
	
	/*Retourner 0 0 sinon (cas peu probable)*/
	return makeVector(0, 0);
}

/*
 * Déplace la tuile "blank"
 */
int moveBlank(Board* board, Direction direction){
	Vector blank_pos;
	Vector swap_tile;
	
	assert(board);
	
	blank_pos = getBlankPosition(board);
	
	/*Obtenir la position de la tuile avec laquelle il faut échanger les positions*/
	if(direction == Up){
		swap_tile = makeVector(blank_pos.x, blank_pos.y - 1);
	} else if(direction == Right){
		swap_tile = makeVector(blank_pos.x + 1, blank_pos.y);
	} else if(direction == Down){
		swap_tile = makeVector(blank_pos.x, blank_pos.y + 1);
	} else if(direction == Left){
		swap_tile = makeVector(blank_pos.x - 1, blank_pos.y);
	}
	
	/*Echanger les positions*/
	return swapTiles(board, blank_pos, swap_tile);
}

/*
 * Obtention du rectangle relatif à l'écran d'une des tuiles
 */
Rect getTileRect(const Board* board, Vector tile_pos){
	Rect rect;
	
	assert(board != NULL);
	
	rect.corner.x = board->pos.x + tile_pos.x * (board->tile_size.x + board->tile_bearing.x);
	rect.corner.y = board->pos.y + tile_pos.y * (board->tile_size.y + board->tile_bearing.y);
	rect.size.x = board->tile_size.x;
	rect.size.y = board->tile_size.y;
	
	return rect;
}

/*
 * Gérer les entrées claviers et souris
 */
void handleInput(Board* board, Event* event, unsigned int* count){
	Vector blank_pos;
	Vector mouse_pos;
	int touche;
	
	assert(board);
	assert(event);
	
	if(event->type == MouseEvent){ /*Cas d'un évenement type souris*/
		mouse_pos = event->mouse;
		blank_pos = getBlankPosition(board);
				
		/*Déplacer la tuile correspondante (s'il y a collision) et augmenter le nombre de coup*/
		if(intersect(mouse_pos, getTileRect(board, makeVector(blank_pos.x, blank_pos.y - 1)))){
			if(moveBlank(board, Up)) (*count)++;
		} else if(intersect(mouse_pos, getTileRect(board, makeVector(blank_pos.x, blank_pos.y + 1)))){
			if(moveBlank(board, Down)) (*count)++;
		} else if(intersect(mouse_pos, getTileRect(board, makeVector(blank_pos.x + 1, blank_pos.y)))){
			if(moveBlank(board, Right)) (*count)++;
		} else if(intersect(mouse_pos, getTileRect(board, makeVector(blank_pos.x - 1, blank_pos.y)))){
			if(moveBlank(board, Left)) (*count)++;
		}
		
	} else if(event->type == KeyboardEvent){ /*Cas d'un évenement type clavier*/
		
		touche = event->keyboard;
		
		/*Déplacer la tuile correspondante (s'il y a collision) et augmenter le nombre de coup*/
		if(touche == XK_Up){
			if(moveBlank(board, Down)) (*count)++;
		} else if(touche == XK_Right){
			if(moveBlank(board, Left)) (*count)++;
		} else if(touche == XK_Down){
			if(moveBlank(board, Up)) (*count)++;
		} else if(touche == XK_Left){
			if(moveBlank(board, Right)) (*count)++;
		} else if(touche == XK_Escape){
			return;
		}
	}
}