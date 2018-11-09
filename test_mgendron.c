#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"

int test_delete_game (int argc, char *argv[]){
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
    delete_game(g);

   //la mémoire est libérée aprés l'appel de la fonction delete_game  
   //On ne peut donc ni accéder au jeu, ni vérifier que le pointeur pointe sur le jeu
   //chaque tentative d'accès au jeu renvoit un seg fault
   //y a pas de solution pour cette fonction 
   
    return EXIT_SUCCESS;    
}

int test_get_piece(int argc, char *argv[]){
    piece p1[] = {
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    LEAF, LEAF, LEAF, LEAF, LEAF,
    SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT,
    CORNER, CORNER, CORNER, CORNER, CORNER,
    TEE, TEE, TEE, TEE, TEE
    };
    direction p2[] = {
    N, E, S, W, N,
    N, E, S, W, E,
    N, E, S, W, S,
    N, E, S, W, W,
    N, E, S, W, N,
    };
    game g = new_game(p1, p2);
    for(int y=0; y<game_height(g);y+=1){
        for(int x=0; x<game_width(g);x+=1){
            if(get_piece(g,x,y)!=p1[y*5+x]){
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

int test_get_current_dir(int argc, char *argv[]){
    piece p1[] = {
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    LEAF, LEAF, LEAF, LEAF, LEAF,
    SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT,
    CORNER, CORNER, CORNER, CORNER, CORNER,
    TEE, TEE, TEE, TEE, TEE
    };
    direction p2[] = {
    N, E, S, W, N,
    N, E, S, W, E,
    N, E, S, W, S,
    N, E, S, W, W,
    N, E, S, W, N,
    };
    game g = new_game(p1, p2);
    for(int y=0; y<game_height(g);y+=1){
        for(int x=0; x<game_width(g);x+=1){
            if(get_current_dir(g,x,y)!=p2[y*5+x]){
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

int test_restart_game(int argc, char *argv[]){
    piece p1[] = {
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
    LEAF, LEAF, LEAF, LEAF, LEAF,
    SEGMENT, SEGMENT, SEGMENT, SEGMENT, SEGMENT,
    CORNER, CORNER, CORNER, CORNER, CORNER,
    TEE, TEE, TEE, TEE, TEE
    };
    direction p2[] = {
    N, E, S, W, N,
    N, E, S, W, E,
    N, E, S, W, S,
    N, E, S, W, W,
    N, E, S, W, N,
    };
    game ex = new_game(p1, p2);
    for(int y=0; y<game_height(ex);y+=1){
        for(int x=0; x<game_width(ex);x+=1){
            rotate_piece(ex,x,y,x);
        }
    }
    restart_game(ex);
    for(int y=0; y<game_height(ex);y+=1){
        for(int x=0; x<game_width(ex);x+=1){
            if(get_piece(ex,x,y)!=p1[y*5+x]){
                return EXIT_FAILURE;
            }
            if(get_current_dir(ex,x,y)!=p2[y*5+x]){
                return EXIT_FAILURE;
            }
        }
    }
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
    if (strcmp("delete", argv[1]) == 0)
        status = test_delete_game(argc, argv);
    else if (strcmp("get_piece", argv[1]) == 0)
        status = test_get_piece(argc, argv);
    else if (strcmp("current_dir", argv[1]) == 0)
        status = test_get_current_dir(argc, argv);
    else if (strcmp("restart", argv[1]) == 0)
        status = test_restart_game(argc, argv);
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
