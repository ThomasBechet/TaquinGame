/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#ifndef SCORE_H
#define SCORE_H

#include "coordinate.h"

/*Fichier de sauvegarde*/
#define SAVE_FILE "save.dat"
/*Nombre de sauvegarde*/
#define MAX_SAVE 10

/*Structure d'un score*/
typedef struct{
	Vector board_size;
	unsigned int count;
	unsigned int score;
	unsigned long time; /*Microseconds*/
} Score;

/*
 * @def : charge un tableau de score à partir du fichier de sauvegarde
 *		la fonction génére également les scores
 *
 * @return : le tableau de score
 */
Score* loadScore(void);

/*
 * @def : stocke le tableau de score dans le fichier de sauvegarde.
 *		la fonction se charge également de désallouer la mémoire terminant
 *		alors le cycle de vie du tableau des scores.
 *
 * @param score : le tableau de score à stocker
 */
void storeScore(Score* score);

/*
 * @def : calcul le score à partir des paramètres suivants : le nombre de coup, la
 *		dimension du plateau
 *
 * @param count : le nombre de coup
 * @param size_x : largeur du plateau
 * @param size_y : hauteur du plateau
 *
 * @return : le score calculé
 */
unsigned int computeScore(unsigned int count, unsigned int size_x, unsigned int size_y);

/*
 * @def : insert un score dans un tableau de score.
 *
 * @param scores : le tableau de score
 * @param input : le score à insérer
 *
 * @return : retourne vrai si le nouveau score est également le meilleur score
 *		dans le cas contraire, la fonction renvoie faux
 */
int insertScore(Score* scores, const Score* input);

#endif