#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

typedef unsigned int uint;

struct game_s {
	int width;
	int height;
	piece* p;
	direction* d;
	direction* d_init;
	bool wrapping;
};
#define DEFAULT_SIZE 5

/**
 * @file game.c
 * @brief Fichier source du jeu 'Net'. Voir game.h pour plus d'informations.
**/

game new_game_ext(int width, int height, piece* pieces, direction* initial_directions, bool wrapping) {
	if(pieces == NULL || initial_directions == NULL) {
		fprintf(stderr, "new_game_ext: NULL pointers\n");
		exit(EXIT_FAILURE);
	}
	if(width < 1 || height < 1) {
		fprintf(stderr, "new_game_ext: invalid param\n");
		exit(EXIT_FAILURE);
	}
	game g = (game)malloc(sizeof(struct game_s));
	if(g == NULL) {
		fprintf(stderr, "new_game_ext: Error malloc g\n");
		exit(EXIT_FAILURE);
	}
	g->p = (piece*)malloc((width * height) * sizeof(piece));
	if(g->p == NULL) {
		fprintf(stderr, "new_game_ext: Error malloc g->p\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d = (direction*)malloc((width * height) * sizeof(direction));
	if(g->d == NULL) {
		fprintf(stderr, "new_game_ext: Error malloc g->d\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d_init = (direction*)malloc((width * height) * sizeof(direction));
	if(g->d_init == NULL) {
		fprintf(stderr, "new_game_ext: Error malloc g->d_init\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < width * height; i++) {
		g->p[i] = pieces[i];
		g->d[i] = initial_directions[i];
		g->d_init[i] = initial_directions[i];
	}
	g->height = height;
	g->width = width;
	g->wrapping = wrapping;
	return g;
}

bool is_wrapping(cgame g) {
	if(g == NULL) {
		fprintf(stderr, "is_wrapping: pointeur NULL\n");
		exit(EXIT_FAILURE);
	}
	return g->wrapping;
}

game new_game_empty_ext(int width, int height, bool wrapping) {
	if(width < 1 || height < 1) {
		fprintf(stderr, "New_game_empty_ext: Invalid param\n");
		exit(EXIT_FAILURE);
	}
	game g = malloc(sizeof(struct game_s));
	if(g == NULL) {
		fprintf(stderr, "new_game_empty_ext: Error malloc g\n");
		exit(EXIT_FAILURE);
	}
	g->p = (piece*)malloc((width * height) * sizeof(piece));
	if(g->p == NULL) {
		fprintf(stderr, "new_game_empty_ext: Error malloc g->p\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d = (direction*)calloc((width * height), sizeof(direction));
	if(g->d == NULL) {
		fprintf(stderr, "new_game_empty_ext: Error malloc g->d\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d_init = (direction*)calloc((width * height), sizeof(direction));
	if(g->d_init == NULL) {
		fprintf(stderr, "new_game_empty_ext: Error malloc g->d_init\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < (width * height); i++) {
		g->p[i] = EMPTY;
	}
	g->height = height;
	g->width = width;
	g->wrapping = wrapping;
	return g;
}

game new_game_empty() {
	game g = malloc(sizeof(struct game_s));
	if(g == NULL) {
		fprintf(stderr, "new_game_empty: Error malloc g\n");
		exit(EXIT_FAILURE);
	}
	g->p = (piece*)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(piece));
	if(g->p == NULL) {
		fprintf(stderr, "new_game_empty: Error malloc g->p\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d = (direction*)calloc(DEFAULT_SIZE * DEFAULT_SIZE, sizeof(direction));
	if(g->d == NULL) {
		fprintf(stderr, "new_game_empty: Error malloc g->d\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d_init = (direction*)calloc(DEFAULT_SIZE * DEFAULT_SIZE, sizeof(direction));
	if(g->d_init == NULL) {
		fprintf(stderr, "new_game_empty: Error malloc g->d_init\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
		g->p[i] = EMPTY;
	}
	g->height = DEFAULT_SIZE;
	g->width = DEFAULT_SIZE;
	return g;
}

game new_game(piece* pieces, direction* initial_directions) {
	if(pieces == NULL || initial_directions == NULL) {
		fprintf(stderr, "new_game: NULL pointers\n");
		exit(EXIT_FAILURE);
	}
	game g = (game)malloc(sizeof(struct game_s));
	if(g == NULL) {
		fprintf(stderr, "new_game: Error malloc g\n");
		exit(EXIT_FAILURE);
	}
	g->p = (piece*)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(piece));
	if(g->p == NULL) {
		fprintf(stderr, "new_game: Error malloc g->p\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d = (direction*)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(direction));
	if(g->d == NULL) {
		fprintf(stderr, "new_game: Error malloc g->d\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	g->d_init = (direction*)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(direction));
	if(g->d_init == NULL) {
		fprintf(stderr, "new_game: Error malloc g->d_init\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
		g->p[i] = pieces[i];
		g->d[i] = initial_directions[i];
		g->d_init[i] = initial_directions[i];
	}
	g->height = DEFAULT_SIZE;
	g->width = DEFAULT_SIZE;
	return g;
}

void set_piece(game g, int x, int y, piece piece, direction orientation) {
	if(g == NULL) {
		fprintf(stderr, "set_piece: pointeur NULL\n");
		exit(EXIT_FAILURE);
	}
	if(piece < -1 || piece > 4 || orientation < 0 || orientation > 3 || x >= g->width || y >= g->height || x < 0 || y < 0) {
		// si la piece ou son orientation n'ont pas de correspondance avec leurs
		// typedef enum (dans game.h) ou que les positions sont hors du tableau
		fprintf(stderr, "set_piece: Incorrect param!\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	int w = g->width;
	// x = position sur la largeur, y = position sur la hauteur donc position dans
	// le tableau = x + (y * largeur du jeux)
	g->p[x + y * w] = piece;
	g->d[x + y * w] = orientation;
	g->d_init[x + y * w] = orientation;
}

void shuffle_dir(game g) {
	if(g == NULL) {
		fprintf(stderr, "set_piece: pointeur NULL\n");
		exit(EXIT_FAILURE);
	}

	int w = g->width;
	int h = g->height;
	for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			g->d[x + (w * y)] = rand() % 4; // géneration d'un chiffre entre 0 et 3
											// qui correspond aux valeur dans
											// type_enum
		}
	}
}

int game_height(cgame game) {
	if(game) {
		return game->height;
	}
	fprintf(stderr, "game_height : Appel avec un pointeur NULL\n");
	exit(EXIT_FAILURE);
}

int game_width(cgame game) {
	if(game) {
		return game->width;
	}
	fprintf(stderr, "game_width: appel avec un pointeur NULL\n");
	exit(EXIT_FAILURE);
}

void rotate_piece_one(game game, int x, int y) {
	if(game) {
		if(x < game->width && y < game->height) {
			game->d[y * game->width + x] = (game->d[y * game->width + x] + 1) % 4;
		}
	}
}

void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn) {
	if(game) {
		if(x < game->width && y < game->height) {
			game->d[y * game->width + x] = (game->d[y * game->width + x] + nb_cw_quarter_turn) % 4;
		}
	}
}

void set_piece_current_dir(game game, int x, int y, direction dir) {
	if(game) {
		if(x < game->width && y < game->height) {
			game->d[y * game->width + x] = dir;
		}
	}
}

bool is_edge_coordinates(cgame g, int x, int y, direction dir) {
	// assert( (x >= 0) && (x < (*g).width) && (y>= 0) && (y<(*g).height) );
	int width = g->width;
	piece p = g->p[y * width + x];	 // récupérer les pieces du jeux
	direction d = g->d[y * width + x]; // récupérer les directions du jeux
	return is_edge(p, d, dir);
}

bool is_edge(piece piece, direction orientation, direction dir) {
	///////////////_SEGMENT_/////////////////
	if(piece == SEGMENT) {
		if(orientation == N || orientation == S) //// SEGMENT= | /////
			return dir == N || dir == S;
		else //// SEGMENT= - /////
			return dir == W || dir == E;
	}
	///////////////_test_LEAF_////////////////////
	if(piece == LEAF) {
		switch(orientation) {
		case N: //// LEAF= ^ /////
			return dir == N;
			break;
		case S: //// LEAF= v /////
			return dir == S;
			break;
		case E: //// LEAF= > /////
			return dir == E;
			break;
		case W: //// LEAF= < /////
			return dir == W;
			break;
		default:
			return false;
		}
	}
	///////////////_test_CORNER_///////////////////
	if(piece == CORNER) {
		switch(orientation) {
		case N: //// CORNER= └ /////
			return dir == N || dir == E;
			break;
		case S: //// CORNER= ┐ /////
			return dir == S || dir == W;
			break;
		case E: //// CORNER= ┌ /////
			return dir == S || dir == E;
			break;
		case W: //// CORNER= ┘ /////
			return dir == W || dir == N;
			break;
		default:
			return false;
		}
	}
	///////////////_test_TEE_///////////////////
	if(piece == TEE) {
		switch(orientation) {
		case N: //// TEE= ┴ /////
			return dir == N || dir == E || dir == W;
			break;
		case S: //// TEE= ┬ /////
			return dir == S || dir == E || dir == W;
			break;
		case W: //// TEE= ┤ /////
			return dir == N || dir == S || dir == W;
			break;
		case E: //// TEE= ├ /////
			return dir == N || dir == E || dir == S;
			break;
		default:
			return false;
		}
	}
	///////////////_test_CROSS_/////////////////
	return piece == CROSS;
}

/**
 * On utilise le fait que la direction est une énumération, avec N=0, E=1, S=2, W=3. On remarque que les directions opposées sont séparées par 2 (S=N+2, W=E+2). La formule est donc (dir + 2) modulo 4.
 */
direction opposite_dir(direction dir) { return (dir + 2) % 4; }

game copy_game(cgame g_src) {
	game g = new_game_empty();
	(*g).width = (*g_src).width;
	(*g).height = (*g_src).height;
	for(int i = 0; i < (*g).width * (*g).height; i++) {
		(*g).p[i] = (*g_src).p[i];
		(*g).d[i] = (*g_src).d[i];
		(*g).d_init[i] = (*g_src).d_init[i];
	}
	(*g).wrapping = (*g_src).wrapping;
	return g;
}

void delete_game(game g) {
	if(g != NULL) {
		free(g->p);
		free(g->d);
		free(g->d_init);
		free(g);
	}
}

piece get_piece(cgame game, int x, int y) {
	if(game == NULL || game->p == NULL) {
		fprintf(stderr, "get_piece: call on NULL pointer\n");
		exit(EXIT_FAILURE);
	}
	int wid = game->width;
	int hei = game->height;
	if(x < 0 || x >= wid || y < 0 || y >= hei) {
		fprintf(stderr, "get_piece: call on unvalid coordinates %d %d\n", x, y);
		exit(EXIT_FAILURE);
	}
	return (*game).p[x + y * wid];
}

direction get_current_dir(cgame g, int x, int y) {
	if(g == NULL || g->d == NULL) {
		fprintf(stderr, "get_current_dir: call on NULL pointer\n");
		exit(EXIT_FAILURE);
	}
	int wid = g->width;
	int hei = g->height;
	if(x < 0 || x >= wid || y < 0 || y >= hei) {
		fprintf(stderr, "get_current_dir: call on unvalid coordinates\n");
		exit(EXIT_FAILURE);
	}
	return *(g->d + x + y * wid);
}

bool is_connected_coordinates(cgame g, int x, int y, direction d);
bool all_pieces_connected(cgame g);
void aux_all_pieces_connected(cgame g, int x, int y, bool* v);
bool is_game_over(cgame g) {
	if(!g && !g->p && !g->d && !g->d_init) {
		fprintf(stderr, "is_game_over : NULL pointer\n");
		exit(EXIT_FAILURE);
	}
	for(uint i = 0; i < g->width * g->height; i++) { // i = index
		for(direction d = 0; d < 4; d++) {			 // d = direction
			// 1-
			if(is_edge_coordinates(g, i % g->width /*x*/, i % g->width /*y*/, d) && !is_connected_coordinates(g, i % g->width /*x*/, i % g->width /*y*/, d)) {
				return false;
			}
		}
	}
	bool r = all_pieces_connected(g);
	return r;
}

void restart_game(game g) {
	if(g == NULL) {
		fprintf(stderr, "restart_game: call on NULL pointer\n");
		delete_game(g);
		exit(EXIT_FAILURE);
	}
	int wid = g->width;
	int hei = g->height;
	for(int y = 0; y < hei; y++) {
		for(int x = 0; x < wid; x++) {
			set_piece_current_dir(g, x, y, g->d_init[x + y * wid]);
		}
	}
}

/*
A partir d'ici : fonctions auxiliaires
*/

/**
 * @brief Renvoie si la pièce est connectée dans la direction donnée. On part du principe que la pièce donnée est connectable dans la direction donnée.
 * @param g : jeu
 * @param x : abscisse
 * @param y : ordonnée
 * @param d : direction où tester
 * @return un booléen.
*/
bool is_connected_coordinates(cgame g, int x, int y, direction d) {
	if(!g) {
		fprintf(stderr, "is_connected_coordinates: NULL pointer error\n");
		exit(EXIT_FAILURE);
	}
	switch(d) {
	case N:
		if(is_wrapping(g))
			return (is_edge_coordinates(g, x, (y + 1) % (game_height(g)), S));
		else
			return (is_edge_coordinates(g, x, y + 1, S));
		break;
	case E:
		if(is_wrapping(g))
			return (is_edge_coordinates(g, (x + 1) % (game_width(g)), y, W));
		else
			return (is_edge_coordinates(g, x + 1, y, W));
		break;
	case S:
		if(is_wrapping(g))
			return (is_edge_coordinates(g, x, (y - 1) % (game_height(g)), N));
		else
			return (is_edge_coordinates(g, x, y - 1, N));
		break;
	case W:
		if(is_wrapping(g))
			return (is_edge_coordinates(g, (x - 1) % (game_width(g)), y, E));
		else
			return (is_edge_coordinates(g, x - 1, y, E));
		break;
	default: // pb d'appel
		return false;
	}
}

/**
 * @brief Renvoie si, en partant de (0,0), on touche toutes les pièces du tableau.
 * On part d'un jeu dont on sait que toutes les pieces sont bien connectees entre elles.
 * @param g : game
*/
bool all_pieces_connected(cgame g) {
	if(!g) {
		// error
	}
	// bool virus[g->width*g->height];
	bool* virus = (bool*)calloc(g->width * g->height, sizeof(bool));
	aux_all_pieces_connected(g, 0, 0, virus);
	for(uint i = 0; i < g->width * g->height; i++) {
		if(virus[i] == false) { // la pièce n'est pas contaminée
			free(virus);
			return false;
		}
	}
	free(virus);
	// virus=NULL;
	return true;
}

/**
 * @brief Utilisé par all_pieces_connected pour la récursion.
 * @param g : game
 * @param x : abscisse
 * @param y : ordonnée
 * @param v : virus (le principe étant qu'à la fin de l'exécution, si toutes les cases sont contaminées par le virus, le jeu est finit)
 */

void aux_all_pieces_connected(cgame g, int x, int y,
	bool* v) { // v : virus ; fonction récursive
	int index = x + y * g->width;
	if(!v[index]) {		 // si la piece n'est pas encore infectée
		v[index] = true; // on l'infecte
		for(direction d = 0; d < 4; d++) {
			if(is_edge_coordinates(g, x, y, d)) {
				switch(d) {
				case N:
					aux_all_pieces_connected(g, x, (y + 1) % (game_height(g)), v);
					break;
				case E:
					aux_all_pieces_connected(g, (x + 1) % (game_width(g)), y, v);
					break;
				case S:
					aux_all_pieces_connected(g, x, (y - 1) % (game_height(g)), v);
					break;
				default: // W
					aux_all_pieces_connected(g, (x - 1) % (game_width(g)), y, v);
				}
			}
		}
	}
}
