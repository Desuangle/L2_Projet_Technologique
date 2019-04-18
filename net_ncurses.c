#include <assert.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <ncurses.h>
#include "game.h"
#include "game_io.h"
#define MAXLINE 80

void display_game_nc(cgame g);

chtype piece_char(piece piece, direction dir) {
  assert(dir >= 0 && dir < NB_DIR);
  assert(piece < NB_PIECE_TYPE);
  chtype chars[NB_DIR][NB_PIECE_TYPE] = {
      {'^', ACS_VLINE, ACS_LLCORNER, ACS_BTEE, '+'},
      {'>', ACS_HLINE, ACS_ULCORNER, ACS_LTEE, '+'},
      {'v', ACS_VLINE, ACS_URCORNER, ACS_TTEE, '+'},
      {'<', ACS_HLINE, ACS_LRCORNER, ACS_RTEE, '+'}};
  return chars[dir][piece];
}

void display_game_nc(cgame g) {
  clear();
  for (int y = game_height(g) - 1; y > -1; y--) {
    for (int x = 0; x < game_width(g); x++) {
      addch(piece_char(get_piece(g, x, y), get_current_dir(g, x, y)));
    }
    printw("\n");
  }
  if (is_game_over(g)) printw("game over\n");
}

static bool game_step(game g) {
  int ch = getch();
  if (ch == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_CLICKED)
        if (event.x < game_width(g) && event.y < game_height(g)) {
          fprintf(stderr, "%d %d\n", event.x, game_height(g) - 1 - event.y);
          rotate_piece_one(g, event.x, game_height(g) - 1 - event.y);
        }
    }
  }
  return true;  // continue to play
}

int main(int argc, char *argv[]) {
  game g = NULL;
  
  //----------------------------------------
  /*
    Setting up the parameters of the game
   */
	if(argc > 2){
		fprintf(stderr, "Usage : %s <file>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	if(argc==1){
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
		g = new_game_ext(5, 5, p1, p2, false);
	}
	else {
		g = load_game(argv[1]);
	}
  //----------------------------------------

  if (g == NULL) {
    printf("game non initialisÃ©.\nVous devez Ã©diter le code pour que Ã§a marche.\n");
    return EXIT_FAILURE;
  }

  printf("Display game %d x %d!\n", game_width(g), game_height(g));
  initscr();
  keypad(stdscr, TRUE);
  mousemask(ALL_MOUSE_EVENTS, NULL);

  display_game_nc(g);
  refresh();
  bool win = false;
  bool cont = true;
  while (!win && cont) {
    cont = game_step(g);
    win = is_game_over(g);
    display_game_nc(g);
    refresh();
  }
  if (win)
    printf("Yes, you win!\n");
  else
    printf("You gave up, bye bye!\n");
  delete_game(g);
  endwin();
  return EXIT_SUCCESS;
}