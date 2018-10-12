#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
//#include "game_io.h"

/*
shows the grid of the game
 */

//Future co-author: Mathis Gendron

void num_input(int tab[], unsigned int size){
  if (size == 2){
    scanf("%d%d", &tab[0], &tab[1]);
  }
}

void show_grid(game g){
  printf("\n");
  for(int i = 0; i < game_width(g); i++){
    printf("##");
  }
  printf("###\n");
  /*
    beginning of the loop
   */
  for(int y = game_height(g) - 1; y >= 0; y--){ // vertical
    printf("# ");
    for(int x = 0; x < game_width(g); x++){ // horizontal
      switch(get_piece(g,x,y)){
      case EMPTY: printf(" "); break;
      case LEAF:
	switch(get_current_dir(g, x, y)){
	case N: printf("^"); break;
	case S: printf("v"); break;
	case E: printf(">"); break;
	case W: printf("<"); break;
	} break;
      case SEGMENT:
	if(get_current_dir(g, x, y) == N || get_current_dir(g, x, y) == S){
	  printf("|");
	}
	else{
	  printf("-");
	} break;
      case CORNER:
	switch(get_current_dir(g, x, y)){
	case N: printf("└"); break;
	case S: printf("┐"); break;
	case E: printf("┌"); break;
	case W: printf("┘"); break;
	} break;
      case TEE:
	switch(get_current_dir(g, x, y)){
	case N: printf("┴"); break;
	case S: printf("┬"); break;
	case E: printf("├"); break;
	case W: printf("┤"); break;
	} break;
      }
      printf(" ");
    } // end of x loop
    printf("#\n");
  }
  printf("\n");
}

int main(void){
  /*
    Setting up the parameters of the game
   */
  piece p1[] = {
    LEAF, TEE, LEAF, LEAF, LEAF,
    LEAF, TEE, TEE, CORNER, SEGMENT,
    LEAF, LEAF, TEE, LEAF, SEGMENT,
    TEE, TEE, TEE, TEE, TEE,
    CORNER, LEAF, LEAF, CORNER, LEAF
  };
  direction p2[] = {
    E, W, S, E, S,
    S, S, N, W, N,
    E, N, W, W, E,
    S, W, N, E, E,
    W, N, W, N, S,
  };
  game ex = new_game(p1, p2);

  /*
    Starting the game
   */

  int coords[2]; //coords[0] = x, coords[1] = y
    
  while (!is_game_over(ex)){
    show_grid(ex);
    printf("Entrer des coordonnées (de la forme <x> <y>) :\n$");
    num_input(coords, 2);
    
    if (coords[0] >= 0 && coords[0] < game_width(ex) && coords[1] >= 0 && coords[1] < game_height(ex)){
      rotate_piece_one(ex, coords[0], coords[1]);
    }
  }
  
  /*
  fgets(input, 30, stdin);
  int i;
  for(i = 0; input[i] != ' '; ++i){} // cherche le deuxième nombre
  
  x = strtol(input, &(buffer), 0);
  if(*(buffer)!=' '){
    printf("Veuillez entrer 2 nombres!\n");
  }
  printf("x : %ld\nstring : %s\nbuffer : <%c>\n", x, input, *(buffer));
  */

  show_grid(ex);

  delete_game(ex);
  
  return EXIT_SUCCESS;
}
