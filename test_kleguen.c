#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"

/* ********** TEST SUCCESS ********** */

  int test_success(int argc, char *argv[])
{
/**
  |  ┘ ^ < └ v  |  ┌ < > ┐ v  |
  |  ┬ ┤ ┴ ├ ├  |  ├ ┬ ┬ ┴ ┤  |
  |  > ^ ┤ < -  |  ^ ^ ├ < |  |
  |  v ┬ ┴ ┘ |  |  > ┬ ┴ ┐ |  |
  |  > ┤ v > v  |  > ┴ < ^ ^  |
  |             |             |
  |    start    |   solution  |

**/
    //on remplit de gauche a droite de bas vers le haut
    piece p1[] = {
    LEAF, TEE, LEAF, LEAF, LEAF,
    LEAF, TEE, TEE, CORNER, SEGMENT,
    LEAF, LEAF, TEE, LEAF, SEGMENT,
    TEE, TEE, TEE, TEE, TEE,
    CORNER, LEAF, LEAF, CORNER, LEAF
  };

    direction p2[] = {E,N,W,N,N,
                      E,S,N,S,S,
                      N,N,E,W,N,
                      E,S,S,N,W,
                      E,W,E,S,S
                      };
    //   ┐
    //  └
    //taille de 5*5 obli
    game(g) = new_game(p1, p2);

    if(is_game_over(g))
    {
      return EXIT_SUCCESS;
    }
    else
    {
    return EXIT_FAILURE;
    }

}

/* ********** TEST SET_PIECE********** */

int test_set_piece(int argc, char *argv[])
{
  game g = new_game_empty();
  set_piece(g,1,1,LEAF,N);

  if (get_piece(g, 1, 1)== LEAF && get_current_dir(g, 1, 1)== N)
  {
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;;
  }
  else
{
    delete_game(g);
    g = NULL;
    return EXIT_FAILURE;
  }

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
   if (strcmp("success", argv[1]) == 0)
        status = test_success(argc, argv);
    else if (strcmp("set_piece", argv[1]) == 0)
        status = test_set_piece(argc, argv);
    else if (strcmp("empty", argv[1]) == 0)
        status = test_empty(argc, argv);
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
