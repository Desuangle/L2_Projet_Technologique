#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"



struct game_s {

    int width;
    int height;
    piece *p;
    direction *d;
    direction *d_init;

};



game new_game_empty(){
	game g=NULL;
	return g;
}
    // TO DO
   

game new_game(piece *pieces, direction *initial_directions){
	game g=NULL;
	return g;
}
    // TO DO
 

void set_piece(game g, int x, int y, piece piece, direction orientation){
}
    // TO DO


void shuffle_dir(game g){
}
    // TO DO


int game_height(cgame game){
	return EXIT_SUCCESS;
}
    // TO DO
  

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
      game->p[y*game->width+x] = (game->p[y*game->width+x] + 1) % 4;
    }
  }
}


void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn){
 if(game){
   if(x < game->width&& y < game->height){
     game->p[y*game->width+x] = (game->p[y*game->width+x] + nb_cw_quarter_turn) % 4;
   }
 }
}


void set_piece_current_dir (game game, int x, int y, direction dir){
  if(game){
   if(x < game->width&& y < game->height){
     game->p[y*game->width+x] = dir;
   }
 }
}


bool is_edge_coordinates(cgame g, int x, int y, direction dir){
	return true;
}
     // TO DO



bool is_edge(piece piece, direction orientation, direction dir){
	return true;
}
     // TO DO


direction opposite_dir(direction dir){
	return 0;
} 
     // TO DO


game copy_game (cgame g_src){
	game g=NULL;
	return g;
}
     // TO DO


void delete_game (game g){
}
     // TO DO


piece get_piece(cgame game, int x, int y){
	return 0;
}
     // TO DO


direction get_current_dir(cgame g, int x, int y){
	return 0;
}
     // TO DO


bool is_game_over (cgame g){
	return true;
}
     // TO DO


void restart_game(game g){
}
     // TO DO

