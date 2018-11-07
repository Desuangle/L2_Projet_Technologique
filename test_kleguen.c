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
  game g = new_game(p1, p2);
  assert(g);

/*
  |  ┘ ^ < └ v  |  
  |  ┬ ┤ ┴ ├ ├  | 
  |  > ^ ┤ < -  |  
  |  v ┬ ┴ ┘ |  | 
  |  > ┤ v > v  |  
  |             |             
  |    start    |     

*/
  game g_copy = new_game_empty();
  assert(g_copy);
  set_piece(g_copy,0,0,LEAF,E);
  set_piece(g_copy,0,1,TEE,W);
  set_piece(g_copy,0,2,LEAF,S);
  set_piece(g_copy,0,3,LEAF,E);
  set_piece(g_copy,0,4,LEAF,S);
  set_piece(g_copy,1,0,LEAF,S);
  set_piece(g_copy,1,1,TEE,S);
  set_piece(g_copy,1,2,TEE,N);
  set_piece(g_copy,1,3,CORNER,W);
  set_piece(g_copy,1,4,SEGMENT,N);
  set_piece(g_copy,2,0,LEAF,E);
  set_piece(g_copy,2,1,LEAF,N);
  set_piece(g_copy,2,2,TEE,W);
  set_piece(g_copy,2,3,LEAF,W);
  set_piece(g_copy,2,4,SEGMENT,E);
  set_piece(g_copy,3,0,TEE,S);
  set_piece(g_copy,3,1,TEE,W);
  set_piece(g_copy,3,2,TEE,N);
  set_piece(g_copy,3,3,TEE,E);
  set_piece(g_copy,3,4,TEE,E);
  set_piece(g_copy,4,0,CORNER,W);
  set_piece(g_copy,4,1,LEAF,N);
  set_piece(g_copy,4,2,LEAF,W);
  set_piece(g_copy,4,3,CORNER,N);
  set_piece(g_copy,4,4,LEAF,S);
          
  int w = game_width(g); // ou int w = game_width(g_copy);
  int h = game_height(g); // ou int h = game_height(g_copy);
  for (int y = 0; y < h; y++){
     for (int x = 0; x < w; x++)            
     {
        direction d = get_current_dir(g, x, y);
        direction d_copy = get_current_dir(g_copy, x, y);
        if(  (get_piece(g, x, y) != get_piece(g_copy, x, y) )  && ( d != d_copy )  )  
        {
           delete_game(g);
           g = NULL;
           delete_game(g_copy);
           g_copy = NULL;
           fprintf(stderr, "Error: set piece (%d,%d)!\n", x, y);
           return EXIT_FAILURE;
        }
      }
  }

  delete_game(g);
  g = NULL;
  delete_game(g_copy);
  g_copy = NULL;
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
  game(g1)= new_game(p1, p2);
  int compare = 0;
  shuffle_dir(g);
  shuffle_dir(g1);

  int w = game_width(g);
  int h = game_height(g);

  int No = 0; int So = 0; int We = 0; int Ea =0;

  for (int y = 0; y < h; y++)
  {
      for (int x = 0; x < w; x++)
      {
        char dir1 = get_current_dir(g, x, y);
        char dir2 = get_current_dir(g1, x, y);
        if (dir1 == dir2)
        {
          compare +=1;
        }
      }
  }
  if(compare == 25) //si les shuffles donne le même jeux
  {
    fprintf(stderr, "La fonction shuffle n'est pas aléatoire\n");
    return EXIT_FAILURE;
  }

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
    if (No>moit || So>moit || Ea>moit|| We>moit || No==0||So==0||Ea==0||We==0 ||(No == 8 && So == 7 && Ea== 6 && We == 4) ) // si une direction à plus de 50% ou n'est pas présente ou que les dir n'ont pas changé
    {
      delete_game(g);
      g = NULL;
      fprintf(stderr, "La fonction shuffle ne semble pas être aléatoire, une des directions est présente sur plus de la moitié des pièces ou une direction est absente\n");
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
