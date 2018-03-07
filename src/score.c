/*Auteurs:
	Thomas BECHET
	Dorian TERBAH
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "score.h"

/*
 * Charge les scores
 */
Score* loadScore(void){
	Score* score = NULL;
	Score score_buf;
	unsigned int i;
	FILE* input = NULL;
	size_t s;

	/*Allocation de la mémoire*/
	score = (Score*)malloc(MAX_SAVE * sizeof(Score));
	assert(score);

	/*Initialisation des scores à 0 (pour les rendre valides)*/
	for(i = 0; i < MAX_SAVE; i++){
		score[i].count = 0;
		score[i].time = 0;
	}

	/*Ouverture du fichier*/
	input = fopen(SAVE_FILE, "r");
	if(!input){ /*Si le fichier ne charge pas on retourne le score avec des valeurs nulles*/
		return score;
	}

	/*Lecture des scores*/
	for(i = 0; i < MAX_SAVE; i++){
		s = fread(&score_buf, sizeof(Score), 1, input);
		if(s != 1){ /*En cas d'erreur, on rend le score avec ce qui a été chargé*/
			fclose(input); /*On ferme d'abord le fichier*/
			return score;
		}

		score[i] = score_buf;
	}

	/*Fermeture du fichier*/
	fclose(input);

	return score;
}

/*
 * Stocke les scores
 */
void storeScore(Score* score){
	unsigned int i;
	size_t s;
	FILE* output = NULL;

	assert(score);

	/*Ouverture du fichier*/
	output = fopen(SAVE_FILE, "w");
	if(!output){
		fprintf(stderr, "Le jeu n'a pas pu sauvegarder !\n");
		fprintf(stderr, "Erreur d'ouverture.\n");
		
		return;
	}

	/*Sauvegarde des données*/
	for(i = 0; i < MAX_SAVE; i++){
		s = fwrite(&score[i], sizeof(Score), 1, output);
		if(s != 1){
			fprintf(stderr, "Failed to save score in file: %s\n", SAVE_FILE);

			fprintf(stderr, "Le jeu n'a pas pu sauvegarder !\n");
			fprintf(stderr, "Erreur d'écriture.\n");

			return;
		}
	}

	/*Fermeture du fichier et libération de la mémoire*/
	fclose(output);
	free(score);
}

/*
 * Calcul du score
 */
unsigned int computeScore(unsigned int count, unsigned int size_x, unsigned int size_y){
	unsigned int x;
	unsigned int factor;

	/*S'il y a 0 coup de fait (notamment pour un plateau de 1*1), il y a un non-sens
	pour éviter des erreurs de calcul on revoie 0 en score*/
	if(count == 0) return 0;

	/*Calcul du facteur*/
	factor = size_x * size_y;

	/*Vérification de la valeur*/
	assert(factor > 0);

	/*Calcul*/
	x = (factor * factor * factor) - count;
	x += 1;

	return x;
}

/*
 * Insertion d'un score
 */
int insertScore(Score* scores, const Score* input){
	unsigned int i, j;

	assert(input);
	assert(scores);

	for(i = 0; i < MAX_SAVE; i++){
		if(input->score > scores[i].score){
			/*Décalage des scores inférieurs dans le tableau de scores*/
			for(j = MAX_SAVE - 1; j > i; j--){
				scores[j] = scores[j - 1];
			}
			scores[i] = *input;

			/*Si sa place est la première c'est qu'il s'agit d'un nouveau record
			on renvoit d'un vrai*/
			if(i == 0) return 1;
			else return 0;
		}
	}
	return 0;
}



