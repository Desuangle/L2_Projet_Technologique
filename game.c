#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"



struct game_s {

    int width;
    int height;
    int **matrice;
    piece *p1;
    direction *p2;

};


game new_game_empty();
    // TO DO
   

game new_game(piece *pieces, direction *initial_directions);
    // TO DO
 

void set_piece(game g, int x, int y, piece piece, direction orientation);
    // TO DO


void shuffle_dir(game g);
    // TO DO


int game_height(cgame game);
    // TO DO
  

 int game_width(cgame game);
     // TO DO


void rotate_piece_one(game game, int x, int y);
    // TO DO


void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn);
     // TO DO


void set_piece_current_dir (game game, int x, int y, direction dir);
     // TO DO


bool is_edge_coordinates(cgame g, int x, int y, direction dir);
     // TO DO



bool is_edge(piece piece, direction orientation, direction dir);
     // TO DO


direction opposite_dir(direction dir);
     // TO DO


game copy_game (cgame g_src);
     // TO DO


void delete_game (game g);
     // TO DO


piece get_piece(cgame game, int x, int y);
     // TO DO


direction get_current_dir(cgame g, int x, int y);
     // TO DO


bool is_game_over (cgame g);
     // TO DO


void restart_game(game g);
     // TO DO

