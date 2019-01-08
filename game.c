#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "game.h"

typedef unsigned int uint;


struct game_s {
	int width;
	int height;
	piece *p;
	direction *d;
	direction *d_init;
	bool wrapping;
};
#define DEFAULT_SIZE 5


game new_game_ext(int width, int height, piece *pieces, direction *initial_directions, bool wrapping){
	if (pieces == NULL || initial_directions == NULL){
		fprintf(stderr,"new_game_ext: NULL pointers");
		exit(EXIT_FAILURE);
	}
	if (width<1 || height <1){
		fprintf(stderr,"new_game_ext: invalid param");
		exit(EXIT_FAILURE);    
	}
	game g = (game)malloc(sizeof(struct game_s));	
	g->p = (piece*)malloc((width*height)*sizeof(piece));
	if  (g->p == NULL){
		fprintf(stderr, "new_game_ext: Error malloc g->p\n");
		exit(EXIT_FAILURE); 
	}
	g->d =(direction*)malloc((width*height)*sizeof(direction));
	if  (g->d == NULL){
		fprintf(stderr, "new_game_ext: Error malloc g->d\n");
		exit(EXIT_FAILURE); 
	}
	g->d_init =(direction*)malloc((width*height)*sizeof(direction));
	if  (g->d_init == NULL){
		fprintf(stderr, "new_game_ext: Error malloc g->d_init\n");
		exit(EXIT_FAILURE); 
	}
	for(int i = 0; i < width*height; i++){
		g->p[i] = pieces[i];
		g->d[i] = initial_directions[i];
		g->d_init[i] = initial_directions[i];
	}	
	g->height = height;
	g->width = width;
	g->wrapping = wrapping;
	return g;
} 

bool is_wrapping(cgame g){
	if (g == NULL){
		fprintf(stderr,"is_wrapping: pointeur NULL");
		exit(EXIT_FAILURE);
	}
	return g->wrapping;
}


/* Walid

game new_game_empty_ext(int width, int height, bool wrapping){
	if(wrapping){
		game g = malloc(sizeof(struct game_s));
		g->p = (piece*)malloc((width*height)*sizeof(piece));
		if  (g->p == NULL)
		{
		fprintf(stderr, "Error: malloc\n");
		exit(EXIT_FAILURE); 
		}
		g->d = (direction*)calloc(width*height, sizeof(direction));
		if  (g->d == NULL)
		{
		fprintf(stderr, "Error: malloc\n");
		exit(EXIT_FAILURE); 
		}
		g->d_init = (direction*)calloc(width*height, sizeof(direction));
			if  (g->d_init == NULL)
		{
		fprintf(stderr, "Error: malloc\n");
		exit(EXIT_FAILURE); 
		}

		for(int i=0; i < width*height; i++){
		g->p[i] = EMPTY;
		}
		g->height = height;
		g->width = width;

		return g;
	}
	fprintf(stderr, "game Not wrapping");
	exit(EXIT_FAILURE); 
}
*/

game new_game_empty_ext(int width, int height, bool wrapping){
	if (width<1 || height <1){
		fprintf(stderr, "New_game_empty_ext: Invalid param\n");
		exit(EXIT_FAILURE);    
	}
	game g = malloc(sizeof(struct game_s));
	g->p = (piece*)malloc((width*height)*sizeof(piece));
	if  (g->p == NULL){
		fprintf(stderr, "new_game_empty_ext: Error malloc g->p\n");
		exit(EXIT_FAILURE); 
	}
	g->d = (direction*)calloc((width*height), sizeof(direction));
	if  (g->d == NULL){
		fprintf(stderr, "new_game_empty_ext: Error malloc g->d\n");
		exit(EXIT_FAILURE); 
	}
	g->d_init = (direction*)calloc((width*height), sizeof(direction));
	if  (g->d_init == NULL){
		fprintf(stderr, "new_game_empty_ext: Error malloc g->d_init\n");
		exit(EXIT_FAILURE); 
	}	
	for(int i=0; i < (width*height); i++){
		g->p[i] = EMPTY;
	}
	g->height = height;
	g->width = width;
	g->wrapping = wrapping;
	return g;
}

game new_game_empty(){
	game g = malloc(sizeof(struct game_s));
	g->p = (piece*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(piece));
	if  (g->p == NULL){
		fprintf(stderr, "new_game_empty: Error malloc g->p\n");
		exit(EXIT_FAILURE); 
	}
	g->d = (direction*)calloc(DEFAULT_SIZE*DEFAULT_SIZE, sizeof(direction));
	if  (g->d == NULL){
		fprintf(stderr, "new_game_empty: Error malloc g->d\n");
		exit(EXIT_FAILURE); 
	}
	g->d_init = (direction*)calloc(DEFAULT_SIZE*DEFAULT_SIZE, sizeof(direction));
	if  (g->d_init == NULL){
		fprintf(stderr, "new_game_empty: Error malloc g->d_init\n");
		exit(EXIT_FAILURE); 
	}
	for(int i=0; i < DEFAULT_SIZE*DEFAULT_SIZE; i++){
		g->p[i] = EMPTY;
	}
	g->height = DEFAULT_SIZE;
	g->width = DEFAULT_SIZE;	
	return g;
}   

game new_game(piece *pieces, direction *initial_directions){
	if (pieces == NULL || initial_directions == NULL){
		fprintf(stderr,"new_game: NULL pointers");
		exit(EXIT_FAILURE);
	}
	game g = (game)malloc(sizeof(struct game_s));
	g->p = (piece*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(piece));
	if  (g->p == NULL){
		fprintf(stderr, "new_game: Error malloc g->p\n");
		exit(EXIT_FAILURE); 
	}	
	g->d =(direction*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(direction));
	if  (g->d == NULL){
		fprintf(stderr, "new_game: Error malloc g->d\n");
		exit(EXIT_FAILURE); 
	}
	g->d_init =(direction*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(direction));
	if  (g->d_init == NULL){
		fprintf(stderr, "new_game: Error malloc g->d_init\n");
		exit(EXIT_FAILURE); 
	}
	for(int i = 0; i < DEFAULT_SIZE*DEFAULT_SIZE; i++){
		g->p[i] = pieces[i];
		g->d[i] = initial_directions[i];
		g->d_init[i] = initial_directions[i];
	}
	g->height = DEFAULT_SIZE;
	g->width = DEFAULT_SIZE;
	return g;
}  

void set_piece(game g, int x, int y, piece piece, direction orientation){
	if (g == NULL){
		fprintf(stderr,"set_piece: pointeur NULL");
		delete_game (g);
		exit(EXIT_FAILURE);
	}
	if (piece < -1 || piece > 4 || orientation <0 || orientation > 3 || x >= g->width || y >= g->height || x < 0 || y < 0){
		fprintf(stderr, "set_piece: Incorrect param!\n");
		delete_game(g);
		exit(EXIT_FAILURE); 
	}
	int w = g->width;
	g->p[x+y*w]= piece;
	g->d[x+y*w] = orientation;
	g->d_init[x+y*w] = orientation;
}

void shuffle_dir(game g){
	int w = g->width; 
	int h = g->height; 
	for (int y = 0; y < h; y++){
		 for (int x = 0; x < w; x++){
		g->d[x+(w*y)]= rand()%4;	
		/*
		int alea = rand()%4;
		switch(alea)
		{
		 case 0: g->d[x+(5*y)]= N; break;
		 case 1: g->d[x+(5*y)]= S; break;
		 case 2: g->d[x+(5*y)]= E; break;
		 case 3: g->d[x+(5*y)]= W; break;
		}
		*/
		}
	}
}

int game_height(cgame game){
	if(game){
		return game->height;
	}
	fprintf(stderr,"game_height : Appel de game_width avec un pointeur NULL\n");
	exit(EXIT_FAILURE);
}

int game_width(cgame game){
	if(game){
		return game->width;
	}
	fprintf(stderr,"Appel de game_width avec un pointeur NULL\n");
	exit(EXIT_FAILURE);
}

void rotate_piece_one(game game, int x, int y){
	if(game){
		if(x < game->width&& y < game->height){
			game->d[y*game->width+x] = (game->d[y*game->width+x] + 1) % 4;
		}
	}
}

void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn){
	if(game){
		if(x < game->width&& y < game->height){
			game->d[y*game->width+x] = (game->d[y*game->width+x] + nb_cw_quarter_turn) % 4;
		}
	}
}

void set_piece_current_dir (game game, int x, int y, direction dir){
	if(game){
		if(x < game->width&& y < game->height){
			game->d[y*game->width+x] = dir;
		}	
	}
}

bool is_edge_coordinates(cgame g, int x, int y, direction dir){
	//  assert( (x >= 0) && (x < (*g).width) && (y>= 0) && (y<(*g).height) );
	int width = g->width;
	piece p = g->p[y*width+x];
	direction d = g->d[y*width+x];
	return is_edge(p, d, dir);
}

bool is_edge(piece piece, direction orientation, direction dir){
	///////////////_SEGMENT_/////////////////
	if(piece==SEGMENT){ 
		switch(orientation){
			case N: //// SEGMENT= | /////
					if(dir == N || dir == S){
						return true;
					}
					break;
			case S: //// SEGMENT= | /////
					if(dir == N || dir == S){
						return true;
					} 
					break;
			case E: //// SEGMENT= - /////
					if ( dir == W || dir == E ){    
						return true;
					}
					break;        
			case W: //// SEGMENT= - /////
					if ( dir == W || dir == E ){    
						return true;
					}        
					break;
			default: return false;
		} 
	}	
	///////////////_test_LEAF_////////////////////        
	if(piece==LEAF){ 
		switch(orientation){
			case N: //// LEAF= ^ /////
					if(dir == N){
						return true;
					}
					break;
			case S: //// LEAF= v /////
					if(dir == S){
						return true;
					} 
					break;
			case E: //// LEAF= > /////
					if (dir == E){    
						return true;
					}
					break;
			case W: //// LEAF= < /////
					if ( dir == W){    
						return true;
					}
					break;        
			default: return false;
		} 
	}	
	///////////////_test_CORNER_///////////////////
	if(piece==CORNER){ 
		switch(orientation){
			case N: //// CORNER= └ /////
					if(dir == N || dir == E){
						return true;
					}
					break;
			case S: //// CORNER= ┐ /////
					if(dir == S|| dir == W ){
						return true;
					} 
					break;
			case E: //// CORNER= ┌ /////
					if ( dir == S || dir == E ){    
						return true;
					}
					break;
			case W: //// CORNER= ┘ ///// 
					if ( dir == W || dir == N){    
						return true;
					}
					break;        
			default: return false;
		} 
	}	
	///////////////_test_TEE_///////////////////
	if(piece==TEE){ 
		switch(orientation){	
			case N:  //// TEE= ┴ /////
					if ( dir == N || dir == E || dir == W ){
						return true;
					}
					break;
			case S: //// TEE= ┬ /////            
					if ( dir == S || dir == E || dir == W ){
						return true;
					}
					break;
			case W://// TEE= ┤ /////   
					if ( dir == N || dir == S || dir == W ){
						return true;
					}
					break;    
			case E: //// TEE= ├ /////
					if ( dir == N || dir == E || dir == S ){
						return true;
					}
					break;  
			default: return false;
		} 
	}
	///////////////_test_CROSS_///////////////////
	if(piece==CROSS){
		return true;
	}	
	///////////////////////////////////////////////
	return false;
}
	
direction opposite_dir(direction dir){
	if(dir==S){
		return N;
	}
	if(dir==N){
		return S;        
	}	
	if(dir==W){     
		return E;       
	}       	
	if(dir==E){
		return W;
	}else{
		fprintf(stderr, "incompatible direction!\n");
		exit (EXIT_FAILURE); 
	}   
} 

game copy_game (cgame g_src){
	game g =new_game_empty();
	(*g).width = (*g_src).width;
	(*g).height = (*g_src).height;
	for(int i=0 ; i<(*g).width*(*g).height; i++){ 	
		(*g).p[i]=(*g_src).p[i];
		(*g).d[i]=(*g_src).d[i];  
		(*g).d_init[i]= (*g_src).d_init[i];	
	}
	///////////////////////////
	return g;
}
	
void delete_game (game g){
	if(g!=NULL){
		free(g->p);
		free(g->d);
		free(g->d_init);
		g->p=NULL;
		g->d=NULL;
		g->d_init=NULL;
		free(g);
	}
}

piece get_piece(cgame game, int x, int y){
	if(game==NULL || game->p==NULL){
		fprintf(stderr, "Call of get_piece on NULL pointer");
		exit(EXIT_FAILURE);
	}
	int wid = game->width;
	int hei = game->height;
	if(x<0 || x>=wid || y<0 || y>=hei){
		fprintf(stderr, "Call of get_piece on unvalid coordinates %d %d\n",x,y);
		exit(EXIT_FAILURE);
	}
	return *(game->p+x+y*wid);
}

direction get_current_dir(cgame g, int x, int y){
	if(g==NULL || g->d==NULL){
		fprintf(stderr, "Call of get_current_dir on NULL pointer");
		exit(EXIT_FAILURE);
	}
	int wid = g->width;
	int hei = g->height;
	if(x<0 || x>=wid || y<0 || y>=hei){
		fprintf(stderr, "Call of get_current_dir on unvalid coordinates");
		exit(EXIT_FAILURE);
	}
	return *(g->d+x+y*wid);
}

bool is_connected_coordinates(cgame g, int x, int y, direction d);
bool all_pieces_connected(cgame g);
void aux_all_pieces_connected(cgame g, int x, int y, bool *v);
bool is_game_over (cgame g){
	if(!g && !g->p && !g->d && !g->d_init){
		fprintf(stderr,"error is_game_over : NULL pointer\n");
		exit(EXIT_FAILURE);
	}
	for (uint i = 0; i < g->width*g->height; i++){ // i = index
		for (direction d = 0; d < 4; d++){ // d = direction
			// 1-
			if(
			is_edge_coordinates(g, i%g->width /*x*/, i%g->width /*y*/, d) && 
			!is_connected_coordinates(g, i%g->width /*x*/, i%g->width /*y*/, d)
			){
				return false;
			}
		}
	}
	bool r = all_pieces_connected(g);
	return r;
}



void restart_game(game g){
	if(g==NULL){
		fprintf(stderr, "Call of restart_game on NULL pointer");
		delete_game (g);
		exit(EXIT_FAILURE);
	}
	int wid = g->width;
	int hei = g->height;
	for(int y=0;y<hei;y++){
		for(int x=0;x<wid;x++){
			set_piece_current_dir(g,x,y,g->d_init[x+y*wid]);
		}
	}
}

/*
A partir d'ici : fonctions auxiliaires
*/

/*
Présupposé :
La pièce donnée est connectable dans la direction donnée
Entrées :
g : jeu
x : abscisse
y : ordonnée
d : direction où tester
Sortie :
Renvoie si la pièce est connectée dans la direction donnée
*/
bool is_connected_coordinates(cgame g, int x, int y, direction d){
	if (!g){
		fprintf(stderr, "NULL pointer error\n");
		exit(EXIT_FAILURE);
	}
	switch (d){
		case N:
			if(is_wrapping(g))
				return (is_edge_coordinates(g, x, (y+1)%(game_height(g)), S));
			else
				return (is_edge_coordinates(g, x, y+1, S));
		break;
		case E:
			if(is_wrapping(g))
				return (is_edge_coordinates(g, (x+1)%(game_width(g)), y, W));
			else
				return (is_edge_coordinates(g, x+1, y, W));
		break;
		case S:
			if(is_wrapping(g))
				return (is_edge_coordinates(g, x, (y-1)%(game_height(g)), N));
			else
				return (is_edge_coordinates(g, x, y-1, N));
		break;
		default: // W
			if(is_wrapping(g))
				return (is_edge_coordinates(g, (x-1)%(game_width(g)), y, E));
			else
				return (is_edge_coordinates(g, x-1, y, E));
	}
}

/*
Entrée :
g : jeu
Sortie :
Renvoie si en partant de (soit du milieu, soit de (0,0) ; à débattre, là on teste avec (0,0)), on touche toutes les pièces du tableau
*/
bool all_pieces_connected(cgame g){
	if (!g){
	//error
	}
	// bool virus[g->width*g->height];
	bool *virus = (bool*) calloc(g->width*g->height, sizeof(bool));
	aux_all_pieces_connected(g, 0, 0, virus);
	for(uint i = 0; i < g->width*g->height; i++){
		if (virus[i] == false){ // la pièce n'est pas contaminée
			return false;
		}
	}	
	//free(virus);
	//virus=NULL;
	return true;
}
void aux_all_pieces_connected(cgame g, int x, int y, bool *v){ // v : virus ; fonction récursive
	int index = x + y * g->width;
	if(!v[index]){ // si la piece n'est pas encore infectée
		v[index] = true; // on l'infecte
		for(direction d = 0; d < 4; d++){
			if(is_edge_coordinates(g, x, y, d)){
				switch (d){
					case N:
						aux_all_pieces_connected(g, x, (y+1)%(game_height(g)), v);
					break;
					case E:
						aux_all_pieces_connected(g, (x+1)%(game_width(g)), y, v);
					break;
					case S:
						aux_all_pieces_connected(g, x, (y-1)%(game_height(g)), v);
					break;
					default: // W
						aux_all_pieces_connected(g, (x-1)%(game_width(g)), y, v);
				}
			}
		}
	}
}


