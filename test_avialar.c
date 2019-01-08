#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h> // INT_MAX, INT_MIN (used in rotate_piece)

#include "game.h"
/* mes fonctions à tester
int game_width(cgame game);
void rotate_piece_one(game game, int x, int y);
void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn);
void set_piece_current_dir (game game, int x, int y, direction dir);
*/

/* ********** TEST GAME WIDTH ********** */

int test_game_width(int argc, char *argv[])
{
  game g1 = new_game_empty_ext(5, 5, false);
  piece p1[] = {};
  direction p2[] = {};
  game g2 = new_game(p1, p2);
  int w1 = game_width(g1), w2 = game_width(g2);
  if(w1 == 5 && w2 == 5){ // /!\ DEFAULT_SIZE = 5
    delete_game(g1);
    delete_game(g2);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "Error : wrong size.\n");
  return EXIT_FAILURE;
}

/* ********** TEST ONE ROTATION ********** */

int test_rotate_piece_one(int argc, char *argv[])
{
  game g = new_game_empty_ext(5, 5, false);
  direction d = get_current_dir(g, 0, 0);
  rotate_piece_one(g, 0, 0);
  if((d+1)%4 == get_current_dir(g,0,0)){ // directions go N, E, S, W, N, E, ... in numbers it's 0, 1, 2, 3, 0, 1, ...
    delete_game(g);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "Error : pieces don't rotate by 1 quarter clockwise.\n");
  return EXIT_FAILURE;
}

/* ********** TEST X ROTATIONS ********** */

int test_rotate_piece(int argc, char *argv[])
{
  game g = new_game_empty_ext(5, 5, false);
  direction d = get_current_dir(g,0,0);
  for(int i = 0; i < 8; i++){
    d = (d+i) % 4;
    rotate_piece(g, 0, 0, i);
    if (d != get_current_dir(g, 0, 0)){
      fprintf(stderr, "Error : rotate_piece by %d rotations gives a wrong direction.\nExpected : %d\nGot %d\n", i, d, get_current_dir(g, 0, 0));
      delete_game(g);
      return EXIT_FAILURE;
    }
  }
  d = (d + INT_MAX) % 4; // test with the highest number
  rotate_piece(g, 0, 0, INT_MAX);
  if (d != get_current_dir(g, 0, 0)){
    fprintf(stderr, "Error : rotate_piece by %d rotations gives a wrong direction.\n", INT_MAX);
    delete_game(g);
    return EXIT_FAILURE;
  }
  d = (d - 1) %4;
  rotate_piece(g, 0, 0, -1);
  if (d != get_current_dir(g, 0, 0)){
    fprintf(stderr, "Error : rotate_piece by -1 rotation gives a wrong direction.\n");
    delete_game(g);
    return EXIT_FAILURE;
  }
  d = (d + INT_MIN) % 4;
  rotate_piece(g, 0, 0, INT_MIN);
  if (d != get_current_dir(g, 0, 0)){
    fprintf(stderr, "Error : rotate_piece by %d rotation gives a wrong direction.\n", INT_MIN);
    delete_game(g);
    return EXIT_FAILURE;
  }
  delete_game(g);
  return EXIT_SUCCESS;
}

/* ********** TEST SET DIRECTION ********** */

int test_set_piece_current_dir(int argc, char *argv[])
{
  game g = new_game_empty_ext(5, 5, false);
  set_piece_current_dir (g, 0, 0, N);
  if(get_current_dir(g, 0, 0) != N){
    delete_game(g);
    fprintf(stderr, "Error : set_piece_current_dir did not set the right direction.\n");
    return EXIT_FAILURE;
  }
  set_piece_current_dir (g, 0, 0, S);
  if(get_current_dir(g, 0, 0) != S){
    delete_game(g);
    fprintf(stderr, "Error : set_piece_current_dir did not set the right direction.\n");
    return EXIT_FAILURE;
  }
  set_piece_current_dir (g, 0, 0, E);
  if(get_current_dir(g, 0, 0) != E){
    delete_game(g);
    fprintf(stderr, "Error : set_piece_current_dir did not set the right direction.\n");
    return EXIT_FAILURE;
  }
  set_piece_current_dir (g, 0, 0, W);
  if(get_current_dir(g, 0, 0) != W){
    delete_game(g);
    fprintf(stderr, "Error : set_piece_current_dir did not set the right direction.\n");
    return EXIT_FAILURE;
  }
  delete_game(g);
  return EXIT_SUCCESS;
}

/* ********** TEST IS GAME OVER ********** */

int test_game_over(int argc, char *argv[])
{
  // solution given by game.h
  piece p1[] = {
    LEAF, TEE, LEAF, LEAF, LEAF,
    LEAF, TEE, TEE, CORNER, SEGMENT,
    LEAF, LEAF, TEE, LEAF, SEGMENT,
    TEE, TEE, TEE, TEE, TEE,
    CORNER, LEAF, LEAF, CORNER, LEAF
  };
  direction p2[] = {
    E, N, W, N, N,
    E, S, N, S, S,
    N, N, E, W, S,
    E, S, S, N, W,
    E, W, E, S, S
  };
  game g = new_game_ext(5, 5, p1, p2, false);
  if(is_game_over(g)){
    delete_game(g);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "Error: game is not completed though it should be.\n");
  delete_game(g);
  return EXIT_FAILURE;
}

/* ********** TEST EMPTY ********** */

int test_empty(int argc, char *argv[])
{
    game g = new_game_empty();
    assert(g);
    int w = game_width(g);
    int h = game_height(g);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            if (get_piece(g, x, y) != EMPTY)
            {
                fprintf(stderr, "Error: piece (%d,%d) is not empty!\n", x, y);
                return EXIT_FAILURE;
            }
        }
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}

/* ********** USAGE ********** */

#ifndef TESTFW

void usage(int argc, char *argv[])
{
    fprintf(stderr, "Usage: %s <testname>\n", argv[0]);
    exit(EXIT_FAILURE);
}

#endif

/* ********** MAIN ROUTINE ********** */

#ifndef TESTFW

int main(int argc, char *argv[])
{
    if (argc == 1)
        usage(argc, argv);

    printf("=> RUN TEST \"%s\"\n", argv[1]);

    int status;
    if (strcmp("is_game_over", argv[1]) == 0)
        status = test_game_over(argc, argv);
    else if (strcmp("empty", argv[1]) == 0)
        status = test_empty(argc, argv);
    else if (strcmp("game_width", argv[1]) == 0)
        status = test_game_width(argc, argv);
    else if (strcmp("rotate_piece_one", argv[1]) == 0)
        status = test_rotate_piece_one(argc, argv);
    else if (strcmp("rotate_piece", argv[1]) == 0)
        status = test_rotate_piece(argc, argv);
    else if (strcmp("set_piece_current_dir", argv[1]) == 0)
        status = test_set_piece_current_dir(argc, argv);
    else
    {
        fprintf(stderr, "Error: test %s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (status != EXIT_SUCCESS)
        printf("FAILURE (status %d)\n", status);
    else
        printf("SUCCESS (status %d)\n", status);

    return status;
}

#endif
