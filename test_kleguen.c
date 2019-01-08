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
        CROSS, TEE, CROSS, TEE, TEE,
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
  set_piece(g_copy,1,0,TEE,W);
  set_piece(g_copy,2,0,LEAF,S);
  set_piece(g_copy,3,0,LEAF,E);
  set_piece(g_copy,4,0,LEAF,S);
  set_piece(g_copy,0,1,LEAF,S);
  set_piece(g_copy,1,1,TEE,S);
  set_piece(g_copy,2,1,TEE,N);
  set_piece(g_copy,3,1,CORNER,W);
  set_piece(g_copy,4,1,SEGMENT,N);
  set_piece(g_copy,0,2,LEAF,E);
  set_piece(g_copy,1,2,LEAF,N);
  set_piece(g_copy,2,2,TEE,W);
  set_piece(g_copy,3,2,LEAF,W);
  set_piece(g_copy,4,2,SEGMENT,E);
  set_piece(g_copy,0,3,CROSS,S);
  set_piece(g_copy,1,3,TEE,W);
  set_piece(g_copy,2,3,CROSS,N);
  set_piece(g_copy,3,3,TEE,E);
  set_piece(g_copy,4,3,TEE,E);
  set_piece(g_copy,0,4,CORNER,W);
  set_piece(g_copy,1,4,LEAF,N);
  set_piece(g_copy,2,4,LEAF,W);
  set_piece(g_copy,3,4,CORNER,N);
  set_piece(g_copy,4,4,LEAF,S);


  int w = game_width(g); // ou int w = game_width(g_copy);
  int h = game_height(g); // ou int h = game_height(g_copy);
  for (int y = 0; y < h; y++){
     for (int x = 0; x < w; x++)
     {
        direction d = get_current_dir(g, x, y);
        direction d_copy = get_current_dir(g_copy, x, y);
        if(  (get_piece(g, x, y) != get_piece(g_copy, x, y) )  || ( d != d_copy )  )
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

restart_game(g_copy);
for (int y = 0; y < h; y++){
     for (int x = 0; x < w; x++)
     {
        direction d = get_current_dir(g, x, y);
        direction d_copy = get_current_dir(g_copy, x, y);
        if(  (get_piece(g, x, y) != get_piece(g_copy, x, y) )  || ( d != d_copy )  )
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
{ //le bug pas trouvé était que shuffle ne shuffle que une partie de la grill et il aurait fallut que shuffle un grand nombre de fois et compter les directions pour chaque pièces
  piece p1[] ={
  LEAF, TEE, LEAF, LEAF, LEAF,
  LEAF, TEE, TEE, CORNER, SEGMENT,
  LEAF, CROSS, TEE, LEAF, SEGMENT,
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
  if(compare == game_width(g)*game_height(g)) //si les shuffles donne le même jeux alors erreur
  {
    delete_game(g);
      g = NULL;
    delete_game(g1);
      g1 = NULL;
    fprintf(stderr, "La fonction shuffle n'est pas aléatoire\n");

    return EXIT_FAILURE;
  }

  for (int y = 0; y < h; y++) //compte le nombre de piece dans chaque direction verifier les %
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
  printf("No :%d \n",No);
  printf("So :%d \n",So);
  printf("Ea :%d \n",Ea);
  printf("We :%d \n",We);
    int moit = (w * h)/2;
    if (No>moit || So>moit || Ea>moit|| We>moit || No==0||So==0||Ea==0||We==0 ||(No == 8 && So == 7 && Ea== 6 && We == 4) ) // si une direction à plus de 50% ou n'est pas présente ou que les dir n'ont pas changé
    {
      delete_game(g);
      g = NULL;
      fprintf(stderr, "La fonction shuffle ne semble pas être aléatoire, une des directions est présente sur plus de la moitié des pièces ou une direction est absente\n");
      return EXIT_FAILURE;
    }
    if (No == 0 || So==0 || We == 0 || Ea ==0 || (No+So+We+Ea != (w*h) )) //on verif que le shuffle place tous les directions et que la somme = 25
    {
      delete_game(g);
      g = NULL;
      fprintf(stderr, "La fonction shuffle ne place pas toute les directions\n");
      return EXIT_FAILURE;
    }

 for(int y=0; y<game_height(g);y+=1) //Verifie que shuffle ne touche pas aux directions
 {
   for(int x=0; x<game_width(g);x+=1)
   {
      if(get_piece(g,x,y)!=p1[y*w+x])
      {
        delete_game(g);
        g = NULL;
        delete_game(g1);
        g1 = NULL;
        return EXIT_FAILURE;
      }
   }
 }

  bool *check = (bool*)calloc(game_width(g)*game_height(g), sizeof(bool));
  for (int i = 0; i <= 10; i++)
  { 
    shuffle_dir(g);
    for(int y=0; y<game_height(g);y+=1) //Verifie que shuffle ne touche pas aux directions
    {
      for(int x=0; x<game_width(g);x+=1)
      {    
        if (get_current_dir(g,x,y) != p2[y*w+x])
        {
        check[x + y*w]=true;
        }
      }
    }
  }

for (int a = 0; a< game_width(g)*game_height(g); a++)
{
  if (check[a] != true)
  {
    printf( "%d", a );
    delete_game(g);
    g = NULL;
    delete_game(g1);
    g1 = NULL;
    return EXIT_FAILURE;
  }
}
    delete_game(g);
    g = NULL;
    delete_game(g1);
    g1 = NULL;
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

  direction p2[] = {E,N,W,N,N, //1er ligne du bas
                    E,S,N,S,S,
                    N,N,E,W,N,
                    E,S,S,N,W,
                    E,W,E,S,S  //dernier ligne du haut
                    };

  game g = new_game(p1, p2);
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
      	fprintf(stderr, "Error: Le jeu créé ne correspond pas à ses paramètres %d %d \n", x ,y);
        return EXIT_FAILURE;
      }

    }
  }
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}
/* ********** TEST game_new_game_ext ********** */
int test_game_new_game_ext(int argc, char *argv[])
{
  piece p1[] = {
  LEAF, TEE, LEAF, LEAF, LEAF, LEAF, TEE,
  TEE, CORNER, SEGMENT,LEAF, LEAF, TEE, LEAF,
  SEGMENT,TEE, TEE, TEE, TEE, TEE, CORNER, 
  LEAF, LEAF, CORNER, LEAF, CROSS, CROSS, LEAF,
  SEGMENT,TEE, TEE, TEE, TEE, TEE, CORNER, 
  TEE, CORNER, SEGMENT,LEAF, LEAF, TEE, LEAF,
  LEAF, LEAF, CORNER, LEAF, CROSS, CROSS, LEAF,
  SEGMENT,TEE, TEE, TEE, TEE, TEE, CORNER, 
  };

  direction p2[] = 
  {
   E,N,W,N,N,E,S, //1er ligne du bas
   E,S,N,S,S,N,W,
   N,N,E,W,N,S,E,
   E,S,S,N,W,W,N,
   E,W,E,S,S,N,S,
   E,S,S,N,W,W,N,
   E,W,E,S,S,N,S,
   E,S,S,N,W,W,N //dernier ligne du haut
  };

 game g = new_game_ext(7, 8, p1, p2, false);

 
 int h = game_height(g);
 int w = game_width(g);


 if (w != 7 || h!=8 || is_wrapping(g) != false)
 {
	  delete_game(g);
    g = NULL;
    printf("h = %d, w = %d",h,w);
    fprintf(stderr, "Error: Le jeu créé ne correspond pas à ses paramètres (wrapping, height ou width \n");
    return EXIT_FAILURE;
  }

for (int x = 0; x < h; x++)
{
  for (int y = 0; x < w; x++)
  {
    if (get_piece(g,x,y) != p1[x+w*y] || get_current_dir(g,x,y)!=p2[x+w*y])
    {
	    delete_game(g);
      g = NULL;
      fprintf(stderr, "Error: Le jeu créé ne correspond pas à ses paramètres (piece ou diretion) \n");
      return EXIT_FAILURE;
    }
  }
}
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;

 
}
/* ********** TEST game_new_game_empty_ext ********** */ //int width, int height, bool wrapping)
int test_game_new_game_empty_ext(int argc, char *argv[])
{
    game g = new_game_empty_ext(6, 7, true);
    assert(g);
    int w = game_width(g);
    int h = game_height(g);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
        {
            if (get_piece(g, x, y) != EMPTY)
            {
                fprintf(stderr, "Error: piece (%d,%d) is not empty!\n", x, y);
                delete_game(g);
                return EXIT_FAILURE;
            }
        }

    if (is_wrapping(g) != true)
    {
      g = NULL;
      fprintf(stderr, "Error: Le jeux ne wrap pas");
      delete_game(g);
      return EXIT_FAILURE;
    }

    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}

/* ********** TEST game_bool_is_wrapping ********** */
int test_game_is_wrapping(int argc, char *argv[])
{
  game g = new_game_empty_ext(6, 7, true);
  if (is_wrapping(g)!=true)
  {
    return EXIT_FAILURE;
    g = NULL;
    delete_game(g);
  }
  g = NULL;
  delete_game(g);

 game g1 = new_game_empty_ext(6, 7, false);
  if (is_wrapping(g1)!= false)
  {
   return EXIT_FAILURE;
   g1 = NULL;
    delete_game(g1);
  }
 delete_game(g1);
 g1 = NULL;
 return EXIT_SUCCESS;

}
/* ********** TEST game_height ********** */
int test_game_height (int argc, char *argv[])
{
  game g1 = new_game_empty();
  piece p1[] = {};
  direction p2[] = {};
  game g2 = new_game(p1, p2);
  int w1 = game_height(g1), w2 = game_height(g2);
  if(w1 == 5 && w2 == 5){ // /!\ DEFAULT_SIZE = 5
    delete_game(g1);
    delete_game(g2);
    return EXIT_SUCCESS;
  }
  fprintf(stderr, "Error : wrong size.\n");
  return EXIT_FAILURE;
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

    else if (strcmp("is_wrapping", argv[1]) == 0)
        status = test_game_is_wrapping(argc, argv);

    else if (strcmp("new_game_ext", argv[1]) == 0)
        status = test_game_new_game_ext(argc, argv);

    else if (strcmp("new_game_empty_ext", argv[1]) == 0)
        status = test_game_new_game_empty_ext(argc, argv);

    /*else if (strcmp("empty", argv[1]) == 0)
      status = test_empty(argc, argv);*/
    else
    {
        fprintf(stderr, "Error: test G%s not found!\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (status != EXIT_SUCCESS)
        printf("FAILURE (status %d)\n", status);
    else
        printf("SUCCESS (status %d)\n", status);

    return status;
}

#endif
