#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"

/* ********** TEST SUCCESS ********** */
/*
  |  ┘ ^ < └ v  |  ┌ < > ┐ v  |
  |  ┬ ┤ ┴ ├ ├  |  ├ ┬ ┬ ┴ ┤  |
  |  > ^ ┤ < -  |  ^ ^ ├ < |  |
  |  v ┬ ┴ ┘ |  |  > ┬ ┴ ┐ |  |
  |  > ┤ v > v  |  > ┴ < ^ ^  |
  |             |             |
  |    start    |   solution  |

*/
    //on remplit de gauche a droite de bas vers le haut


/* ********** TEST SET_PIECE********** */

int test_set_piece(int argc, char *argv[])
{
  game g = new_game_empty();

  int h = 5;
  int w = 5;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
          set_piece(g,x,y,LEAF,N);

          if (get_piece(g, x, y) != LEAF || get_current_dir(g, x, y)!= N)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un Leaf en direction N\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,LEAF,S);
          if (get_piece(g, x, y) != LEAF || get_current_dir(g, x, y)!= S)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un Leaf en direction S \n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,LEAF,E);
          if (get_piece(g, x, y) != LEAF || get_current_dir(g, x, y)!= E)
          {
          delete_game(g);
	  fprintf(stderr, "Error: La pièce inséré n'est pas un Leaf en direction E \n");
          g = NULL;
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,LEAF,W);
          if (get_piece(g, x, y) != LEAF || get_current_dir(g, x, y)!= W)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un Leaf en direction W \n");
          return EXIT_FAILURE;
          }

          set_piece(g,x,y,TEE,N);
          if (get_piece(g, x, y) != TEE || get_current_dir(g, x, y)!= N)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un TEE en direction N\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,TEE,S);
          if (get_piece(g, x, y) != TEE || get_current_dir(g, x, y)!= S)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un TEE en direction S\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,TEE,E);
          if (get_piece(g, x, y) != TEE || get_current_dir(g, x, y)!= E)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un TEE en direction E\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,TEE,W);
          if (get_piece(g, x, y) != TEE || get_current_dir(g, x, y)!= W)
          {
          delete_game(g);
          g = NULL;
 	  fprintf(stderr, "Error: La pièce inséré n'est pas un TEE en direction W\n");
          return EXIT_FAILURE;
          }


          set_piece(g,x,y,CORNER,N);
          if (get_piece(g, x, y) != CORNER|| get_current_dir(g, x, y)!= N)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un CORNER en direction N\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,CORNER,S);
           if (get_piece(g, x, y) != CORNER|| get_current_dir(g, x, y)!= S)
           {
           delete_game(g);
           g = NULL;
	   fprintf(stderr, "Error: La pièce inséré n'est pas un CORNER en direction S\n");
           return EXIT_FAILURE;
           }
          set_piece(g,x,y,CORNER,E);
          if (get_piece(g, x, y) != CORNER|| get_current_dir(g, x, y)!= E)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un CORNER en direction E\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,CORNER,W);
          if (get_piece(g, x, y) != CORNER|| get_current_dir(g, x, y)!= W)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un CORNER en direction W\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,SEGMENT,N);
          if (get_piece(g, x, y) != SEGMENT|| get_current_dir(g, x, y)!= N)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un SEGMENT en direction N\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,SEGMENT,S);
          if (get_piece(g, x, y) != SEGMENT|| get_current_dir(g, x, y)!= S)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un SEGMENT en direction S\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,SEGMENT,E);
          if (get_piece(g, x, y) != SEGMENT|| get_current_dir(g, x, y)!= E)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un SEGMENT en direction E\n");
          return EXIT_FAILURE;
          }
          set_piece(g,x,y,SEGMENT,W);
          if (get_piece(g, x, y) != SEGMENT|| get_current_dir(g, x, y)!= W)
          {
          delete_game(g);
          g = NULL;
	  fprintf(stderr, "Error: La pièce inséré n'est pas un SEGMENT en direction W\n");
          return EXIT_FAILURE;
          }
        }
      }

  delete_game(g);
  g = NULL;
  return EXIT_SUCCESS;

}

/* ********** TEST shuffle_dir********** */

int test_shuffle_dir(int argc, char *argv[])
{
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

  int w = game_width(g);
  int h = game_height(g);

  int No = 0; int So = 0; int We = 0; int Ea =0;

  shuffle_dir(g);

  for (int y = 0; y < h; y++)
  {
      for (int x = 0; x < w; x++)
      {
        char dir = get_current_dir(g, x, y);
        if (dir == N)
        {
          No+=1;
        }
        if (dir == S)
        {
          So+=1;
        }
        if (dir == E)
        {
          Ea+=1;
        }
        if (dir == W)
        {
          We+=1;
        }
      }
  }
    int moit = (w * h)/2;
    if (No>moit || So>moit || Ea>moit|| We>moit)
    {
      delete_game(g);
      g = NULL;
      fprintf(stderr, "La fonction shuffle ne semble pas être aléatoire, une des directions est présente sur plus de la moitié des pièces\n");
      return EXIT_FAILURE;
    }
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;



}

/* ********** TEST EMPTY ********** */
/*
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
*/
/* ********** TEST game_new_game ********** */
int test_game_new_game (int argc, char *argv[])
{

  piece p1[] = {
  LEAF, TEE, LEAF, LEAF, LEAF,
  LEAF, TEE, TEE, CORNER, SEGMENT,
  LEAF, LEAF, TEE, LEAF, SEGMENT,
  TEE, TEE, TEE, TEE, TEE,
  CORNER, LEAF, LEAF, CORNER, LEAF
  };

  direction p2[] = {E,N,W,N,N, //1er ligne du bass
                    E,S,N,S,S,
                    N,N,E,W,N,
                    E,S,S,N,W,
                    E,W,E,S,S  //dernier ligne du haut
                    };

  game(g) = new_game(p1, p2);
  int w = 5;
  int h = 5;
  if (g == NULL)
  {
    delete_game(g);
    return EXIT_FAILURE;
  }

  for (int x = 0; x < h; x++)
  {
    for (int y = 0; x < w; x++)
    {
      if (get_piece(g,x,y) != p1[x+5*y] || get_current_dir(g,x,y)!=p2[x+5*y])
      {
	delete_game(g);
        g = NULL;
	fprintf(stderr, "Error: Le jeu créé ne correspond pas à ses paramètres\n");
        return EXIT_FAILURE;
      }

    }
  }
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}

/* ********** TEST game_height ********** */
int test_game_height (int argc, char *argv[])
{
  piece p1[] = {
  LEAF, TEE, LEAF, LEAF, LEAF,
  LEAF, TEE, TEE, CORNER, SEGMENT,
  LEAF, LEAF, TEE, LEAF, SEGMENT,
  TEE, TEE, TEE, TEE, TEE,
  CORNER, LEAF, LEAF, CORNER, LEAF
  };

  direction p2[] = {E,N,W,N,N, //1er ligne du bass
                    E,S,N,S,S,
                    N,N,E,W,N,
                    E,S,S,N,W,
                    E,W,E,S,S  //dernier ligne du haut
                    };

  game(g) = new_game(p1, p2);

  if (game_height(g) != 5)
  {
    delete_game(g);
    g = NULL;
    return EXIT_FAILURE;
    fprintf(stderr, "Error: La hauteur ne correspond pas à celle attendu\n");
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
    if (strcmp("set_piece", argv[1]) == 0)
        status = test_set_piece(argc, argv);

    else if (strcmp("game_new_game", argv[1]) == 0)
        status = test_game_new_game(argc, argv);

    else if (strcmp("shuffle_dir", argv[1]) == 0)
        status = test_shuffle_dir(argc, argv);

    else if (strcmp("game_height", argv[1]) == 0)
        status = test_game_height(argc, argv);

    /*else if (strcmp("empty", argv[1]) == 0)
      status = test_empty(argc, argv);*/
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
