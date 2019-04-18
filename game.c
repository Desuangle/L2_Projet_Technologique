#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "game.h"
#include <unistd.h>

#define GAME_WIDTH 5
#define GAME_HEIGHT 5
#define NB_DIR 4  // la quantité de direction (N S W E), 4 en total
typedef unsigned int uint;

// game_s est la définition de type game. il contient 1- la largeur , 2- l'hauteur, 3-les types des pièces, 4-les directions des pièces ,
//5-les directions de départ(direction* start) et l'état de wrapping de jeu.


struct game_s{
	uint width;
	uint height;
	piece* piece;
	direction* direction;
	direction* start;      // les directions de départ
	bool wrapping;
};

typedef enum c_code_e {NOT_EXPLORED = 0, CONNEXE = 1, ERROR_CASE = 2} c_code;
//***********************************************//


static direction next_dir(direction dir){ //prend la prochaine direction dans le sens des aiguilles d'une montre
	direction tab[NB_DIR]= {E,S,W,N};  //voir opposite_dir pour plus de précision
	return tab[dir];
}

static direction prev_dir(direction dir){ // pareil dans l'autre sens
	direction tab[NB_DIR]={W,N,E,S};
	return tab[dir];
}


//****************************************************//
//Les definitions de chacune des fonctions utilisées se trouvent dans game.h
//le calcul x+(g->width*y) est utilisé plusieur fois, voir le commentaire de set_piece pour l'explication

bool is_wrapping(cgame g){
	assert(g);
	return g->wrapping;
}
static int index (cgame game, int x, int y){ // fonction auxiliaire, trouver l'index de la pièce actuelle
	if(x < 0 || x >= game_width(game) || y < 0 || y >= game_height(game)){
		fprintf(stderr, "Invalid coordinates 0");
		exit(EXIT_FAILURE);
	}
	return (game->width * y) + x;
}


game new_game_empty(){
	game g = new_game_empty_ext(GAME_WIDTH,GAME_HEIGHT, false);
	return g;
}

game new_game_empty_ext(int width, int height, bool wrapping){
	if(width <= 0 || height <= 0){
		fprintf(stderr, "Invalid width and/or height");
		exit(EXIT_FAILURE);
	}
	game g;
	g = (game) malloc(sizeof(struct game_s));
	if(g == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->width =  width;
	g->height = height;
	g->wrapping = wrapping;
	g->piece = (piece *) malloc((g->width * g->height) * sizeof(piece));
	if(g->piece == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->direction = (direction *) malloc((g->width * g->height) * sizeof(direction));
	if(g->direction == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->start = (direction *) malloc((g->width * g->height) * sizeof(direction));
	if(g->start == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	piece piece_game[] = {EMPTY};
	direction dir_game[] = {N};
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			set_piece(g, x, y, piece_game[0], dir_game[0]);
		}
	}
	return g;
}

game new_game(piece *pieces, direction *initial_directions){
	if(pieces == NULL || initial_directions == NULL){
		fprintf(stderr, "Invalid pieces or initial_directions tab");
		exit(EXIT_FAILURE);
	}
	game g = new_game_ext(GAME_WIDTH,GAME_HEIGHT,pieces,initial_directions,false);
	return g;
}

game new_game_ext(int width, int height, piece *pieces, direction *initial_directions, bool wrapping){
	if(pieces == NULL || initial_directions == NULL){
		fprintf(stderr, "Invalid pieces or initial_directions tab");
		exit(EXIT_FAILURE);
	}
	if(width <= 0 || height <= 0){
		fprintf(stderr, "Invalid width and/or height");
		exit(EXIT_FAILURE);
	}
	game g;
	g = (game) malloc(sizeof(struct game_s));
	if(g == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->width = width;
	g->height = height;
	g->wrapping = wrapping;
	g->piece = (piece *) malloc((g->width * g->height) * sizeof(piece));
	if(g->piece == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->direction = (direction *) malloc((g->width * g->height) * sizeof(direction));
	if(g->direction == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	g->start = (direction *) malloc((g->width * g->height) * sizeof(direction));
	if(g->start == NULL){
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	for(uint i = 0; i < g->width * g->height; i++){
			g->piece[i] = pieces[i];
			g->direction[i] = initial_directions[i];
			g->start[i] = initial_directions[i];
	}
	return g;
}

void set_piece(game g, int x, int y, piece piece, direction orientation){ // x+(g->width*y) qui est utilisé ici et dans d'autre code permet de convertir les valeurs x et y en un indice pour
	assert(g);                                                        // le tableau de piece ou de direction
	g->piece[x+(g->width*y)] = piece;
	g->direction[x+(g->width*y)] = orientation;
	g->start[x+(g->width*y)] = orientation;
}

void shuffle_dir(game g){
	assert(g);
	direction all_dir[] = {N,E,S,W};
	uint x = ((uint)RAND_MAX+1)/NB_DIR;  //on met à l'echelle rand_max pour qu'il soit proportionel à 4, car en le divisant (divison entiere) puis en le multipliant on elimine le reste de la division par 4
	uint limite = x * NB_DIR;
	for(uint i = 0; i < g->width * g->height; i++){
		uint j = rand();
		while(j >= limite) //on relance tous les rand() qui donnent sur un nombre entre rand_max et rand_max - (rand_max%4) on garde comme cela qu'un nombre de possibilités divisibles par 4
			j = rand();
		g->direction[i] = all_dir[(j/x)];
	}
}

int game_height(cgame game){
	assert(game);
	return game->height;
}

int game_width(cgame game){
	assert(game);
	return game->width;
}

void rotate_piece_one(game game, int x, int y){
	if( x < 0 || x >= game_width(game) || y < 0 || y >= game_height(game) ){
		fprintf(stderr,"Les cordonnees entrees ne sont pas correctes, veuillez-reessayer");
		exit(EXIT_FAILURE);
	}
	rotate_piece(game,x,y,1); //il s'agis juste d'utilisé rotate_piece une pour avancé d'un cran
}



void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn){
	if( x < 0 || x >= game_width(game)|| y <0 || y >= game_height(game)){
		fprintf(stderr,"Les cordonnees entrees ne sont pas correctes, veuillez-reessayer");
		exit(EXIT_FAILURE);
	}
	if(nb_cw_quarter_turn >= 0){
		direction current = get_current_dir(game,x,y);
		int next = (current + nb_cw_quarter_turn)%NB_DIR; //on additione l'indice de la direction actuelel + le nombre de tour, le reste de la division par 4 donne l'indice de la nouvelle direction
		current = (direction) next;
		set_piece_current_dir(game,x,y,current);
	}else{                                                           //cas ou nb_cw_quarter_turn est negatif (dans ce cas la on tourne le nombre de fois necessaire dans l'autre sens)
		for(int i = 0; i > nb_cw_quarter_turn; i--)
			set_piece_current_dir(game,x,y,prev_dir(get_current_dir(game,x,y)));
	}

}

void set_piece_current_dir (game game, int x, int y, direction dir){
	assert(game);
	game->direction[index(game,x,y)] = dir;
}

bool is_edge_coordinates(cgame g, int x, int y, direction dir){
	return is_edge(get_piece(g,x,y),get_current_dir(g,x,y),dir); //il s'agis juste de faire is_edge à une position donné
}



bool is_edge(piece piece, direction orientation, direction dir){
	if(piece == EMPTY){            //case vide ne connecte jamais
		return false;
	}else if(piece == CROSS){   //Cross connecte dans les 4 sens c'est-à-dire toujours
		return true;
	}else if(piece == LEAF){       //Leaf connecte seulement dans le sens vers lequel il oriente
		return orientation == dir;
	}else if(piece == SEGMENT){       //Segment connecte vers son orientation + l'inverse
		return orientation == dir || orientation == opposite_dir(dir);
	}else if(piece == CORNER){       //Corner connecte vers son orientation + la prochaine clockwise
		return orientation == dir || next_dir(orientation) == dir;
	}else{                      //il ne reste plus que Tee qui connecte partout sauf derriere lui
		return !(orientation == opposite_dir(dir));
	}
}

direction opposite_dir(direction dir){
	direction tab[NB_DIR] = {S,W,N,E}; //Avec la propriété des enum N vaut 0 puis E vaut 1 ect donc on peut s'en servir comme indice
	return tab[dir];
}

game copy_game (cgame g_src){
	game copy = (game)malloc(sizeof(struct game_s));
	if(!copy){
		fprintf(stderr,"not enough memory !\n");
		exit(EXIT_FAILURE);
	}
	copy->direction = (direction*)malloc((g_src->width)*(g_src->height)*sizeof(direction));
	copy->start = (direction*)malloc((g_src->width)*(g_src->height)*sizeof(direction));
	copy->piece = (piece*)malloc((g_src->width)*(g_src->height)*sizeof(piece));
	if(!copy->direction || !copy->start || !copy->piece){
		fprintf(stderr,"not enough memory !\n");
		exit(EXIT_FAILURE);
	}
	copy->height = g_src->height;
	copy->width = g_src->width;
	copy->wrapping = g_src->wrapping;
	for(uint i = 0; i < g_src->width * g_src->height; i++){            //on ne copie pas les tableaux directement car ce sont des pointeurs, on copie leur elements
		copy->piece[i] = g_src->piece[i];
		copy->direction[i] = g_src->direction[i];
		copy->start[i] = g_src->start[i];
	}
	return copy;
}

void delete_game (game g){ //on free d'abord les pointeurs pointés par g pour ne pas les perdre
   	free(g->start);
   	free(g->direction);
  	free(g->piece);
   	free(g);
}



piece get_piece(cgame game, int x, int y){
	assert(game);
	if(x < 0 || x >= game_width(game) || y < 0 || y >= game_height(game)){
		fprintf(stderr, "Invalid coordinates 1");
		exit(EXIT_FAILURE);	}

	return game->piece[index(game,y,x)];
}

direction get_current_dir(cgame game, int x, int y){
	assert(game);
	if(x < 0 || x >= game_width(game) || y < 0 || y >= game_height(game)){
		fprintf(stderr, "Invalid coordinates 2");
		exit(EXIT_FAILURE);
	}

	return game->direction[index(game,x,y)];
}

//fonction qui test si le game est connexe sans aucun loop et renvoie un tableau de 0,1 ou 2 qui est ensuite decodé pour voir si le game est valide (tableau remplie de 1)

int** connexe_without_loop(cgame g,int** tab,int x,int y,int previous,int* error){
	if(get_piece(g,x,y)==EMPTY){  //cas où la case est juste empty on met la case en erreur
		tab[x][y] = ERROR_CASE;        // ici 2 est utilisé pour coder une erreur et sera detecté dans game_over, 1 code les cases ou on est déja passé et 0 les cases qu'on n'a jamais emprunté
		*error = 1;
		return tab;
	}
	if(tab[x][y]==CONNEXE){             //cas où on est deja passé par cette case, (detection de boucle) on met la case en erreur
		tab[x][y] = ERROR_CASE;
		*error = 1;
		return tab;
	}
	direction set_dir[] = {N,E,S,W};
	tab[x][y] = CONNEXE;
	for(int i = 0; i < NB_DIR;i++){
		if(is_edge_coordinates(g,x,y,set_dir[i]) && previous != set_dir[i] && (tab[x][y] == CONNEXE) && *error == 0){ //on ne teste pas la direction d'ou on vient pour na pas faire une boucle
			int fy[] = {y+1,y,y-1,y};
			int fx[] = {x,x+1,x,x-1};
			int next_x = fx[i];
			int next_y = fy[i];
			if(fy[i] >= g->height || fx[i]>= g->width || fx[i] < 0 || fy[i] <0){   //on traite les cas ou on sort des bords du game
				if(!is_wrapping(g)){      // cas sans wrapping
					tab[x][y] = ERROR_CASE;
					*error = 1;
					return tab;
				}else{
					next_x = i == E ? 0 : i == W ? game_width(g)-1 : next_x;
					next_y = i == N ? 0 : i == S ? game_height(g)-1 : next_y;
				}
			}                                 //cas où on ne déborde pas
			if(is_edge_coordinates(g,next_x,next_y,opposite_dir(set_dir[i])))
					tab = connexe_without_loop(g,tab,next_x,next_y,opposite_dir(i),error);
			else{
				tab[x][y] = ERROR_CASE;
				*error = 1;
				return tab;
			}
		}
	}
	return tab;
}

void free_connexe(cgame g,int** c){
	if(!(c == NULL)){
		int i;
		for(i=0;i<game_width(g);i++){
			free(c[i]);
		}
		free(c);
	}
}


bool is_game_over (cgame g){
	assert(g);
	int** connexe = (int**) malloc(game_width(g)*sizeof(int*));
	int error = 0;
	if(connexe==NULL){
		fprintf(stderr,"Not enough Memory !!");
		exit(EXIT_FAILURE);
	}
	for(int i = 0 ; i < g->width;i++){
		connexe[i] = (int*)calloc(game_height(g),sizeof(int));
		if(connexe[i]==NULL){
			fprintf(stderr,"Not enough Memory !!");
			exit(EXIT_FAILURE);
		}
	}
	connexe = connexe_without_loop(g,connexe,0,0,NB_DIR,&error); //ici 4 sert a représenter qu'il n'y a pas de direction précédente (l'argument previous detecte à l'aide d'un int entre 0 et 3 la direction precedente)
	for(int x = 0; x < g->width;x++){
		for(int y = 0 ; y < g->height;y++){
			if(!(connexe[x][y]==1)){ //verifcation que toute les cases on été traversées (code 1) et sans erreurs (les erreur sont code 2), code 0 sont des cases en dehors de la composante connexe
				free_connexe(g,connexe);
				return false;
			}
		}
	}
	free_connexe(g,connexe);
	return true;
}


void restart_game(game g){
	for(int i = 0; i < (g->width)*(g->height);i++ ){
		g->direction[i] = g->start[i];             //on remet les direction initiales sauvegardées dans le tableau start
	}
}
