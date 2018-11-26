#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "game.h"


/* ********** TEST is_edge *********** */
int test_is_edge(int argc, char *argv[])
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
    int w = game_width(g);
    int h = game_height(g);
   for (int y = 0; y < h; y++){
         for (int x = 0; x < w; x++)            
         {
            piece p = get_piece(g, x, y);  ///piece { LEAF=0= ^ , SEGMENT=1= | , CORNER=2= └ , TEE=3= ┴ }===> direction (North)
            direction d = get_current_dir(g, x, y);
             ///////////////_test_SEGMENT_///////////////// 
            if( (p == SEGMENT) && ( (d == N) || (d == S) ) )  //// SEGMENT= | /////
             {
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }   
            if( (p == SEGMENT) && ( (d == W) || (d == E) ) )  //// SEGMENT= - /////
             {
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }  
             ///////////////_test_LEAF_//////////////////// 
            if( (p == LEAF) && (d == N) )  //// LEAF= ^ /////
             {
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 
             }   
            if( (p == LEAF) && (d == S) )  //// LEAF= v /////
             {
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }   
            if( (p == LEAF) && (d == W) )  //// LEAF= < /////
             {
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }     
            if( (p == LEAF) && (d == E) )  //// LEAF= > /////
             {
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }       
             ///////////////_test_CORNER_/////////////////// 
            if( (p == CORNER) && (d == N) )  //// CORNER= └ /////
             {
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 
             }   
            if( (p == CORNER) && (d == S) ) //// CORNER= ┐ /////
             {
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }   
            if( (p == CORNER) && (d == W) )//// CORNER= ┘ /////   
             {
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }     
            if( (p == CORNER) && (d == E) )//// CORNER= ┌ /////
             {
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }       
             ///////////////_test_TEE_///////////////////
            if( (p == TEE) && (d == N) )  //// TEE= ┴ /////
             {
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 
             }   
            if( (p == TEE) && (d == S) ) //// TEE= ┬ /////
             {
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }   
            if( (p == TEE) && (d == W) )//// TEE= ┤ /////   
             {
                 if ( ! is_edge(p , d , W) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
 
             }     
            if( (p == TEE) && (d == E) )//// TEE= ├ /////
             {
                 if ( ! is_edge(p , d , E) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , N) )
                 {
                     delete_game(g);
                    fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
                 if ( ! is_edge(p , d , S) )
                 {
                     delete_game(g);
                     fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                     return EXIT_FAILURE;
                 }
             }
        }
    }
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}

/* ********** TEST is_edge_coordinates *********** */
int test_is_edge_coordinates(int argc, char *argv[])
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
    int w = game_width(g);
    int h = game_height(g);
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)            
        {
            direction d = get_current_dir(g, x, y);

            if( (y==0) || (y == h-1) || (x == 0) || (x == w-1) ){ 
               
                if (y==0 ){//ligne de bas
                        ///////////////_test_SEGMENT_///////////////// 
                    if( (get_piece(g, x, y) == SEGMENT) && ( (d == N) || (d == S) ) )  //// SEGMENT= | /////
                    {
                        if ( ! is_edge_coordinates(g, x , y , N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                    }   
                    if( (get_piece(g, x, y) == SEGMENT) && ( (d == W) || (d == E) ) )  //// SEGMENT= - /////
                    {
                        if ( ! is_edge_coordinates(g, x , y , W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y , E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }  
                        ///////////////_test_LEAF_//////////////////// 
                    if( (get_piece(g, x, y) == LEAF) && (d == N) )  //// LEAF= ^ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y , N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        
                    }   

                    if( (get_piece(g, x, y) == LEAF) && (d == W) )  //// LEAF= < /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }     
                    if( (get_piece(g, x, y) == LEAF) && (d == E) )  //// LEAF= > /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }       
                        ///////////////_test_CORNER_/////////////////// 
                    if( (get_piece(g, x, y) == CORNER) && (d == N) )  //// CORNER= └ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y , N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y , E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        
                    }   
                    if( (get_piece(g, x, y) == CORNER) && (d == S) ) //// CORNER= ┐ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }   
                    if( (get_piece(g, x, y) == CORNER) && (d == W) )//// CORNER= ┘ /////   
                    {
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }     
                    if( (get_piece(g, x, y) == CORNER) && (d == E) )//// CORNER= ┌ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                    }       
                        ///////////////_test_TEE_///////////////////
                    if( (get_piece(g, x, y) == TEE) && (d == N) )  //// TEE= ┴ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        
                    }   
                    if( (get_piece(g, x, y) == TEE) && (d == S) ) //// TEE= ┬ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }

                    }   
                    if( (get_piece(g, x, y) == TEE) && (d == W) )//// TEE= ┤ /////   
                    {
                        if ( ! is_edge_coordinates(g, x , y, W) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                    }     
                    if( (get_piece(g, x, y) == TEE) && (d == E) )//// TEE= ├ /////
                    {
                        if ( ! is_edge_coordinates(g, x , y, E) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                        if ( ! is_edge_coordinates(g, x , y, N) )
                        {
                            delete_game(g);
                            g = NULL;
                            fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                            return EXIT_FAILURE;
                        }
                    } 
                }//fin if ligne de bas
    
                if(y==h-1 ){//ligne de haut
                        
                }//fin if ligne de haut

                if (x == 0 ){//ligne de droit
                    
                }//fin if ligne de droit

                if(x == w-1 ){//ligne de gauche
                    
                }//fin if ligne de gauche
	        }
            else{//=>milieu de la grille

                    ///////////////_test_SEGMENT_///////////////// 
                if( (get_piece(g, x, y) == SEGMENT) && ( (d == N) || (d == S) ) )  //// SEGMENT= | /////
                {
                    if ( ! is_edge_coordinates(g, x , y , N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y , S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }   
                if( (get_piece(g, x, y) == SEGMENT) && ( (d == W) || (d == E) ) )  //// SEGMENT= - /////
                {
                    if ( ! is_edge_coordinates(g, x , y , W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y , E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }  
                ///////////////_test_LEAF_//////////////////// 
                if( (get_piece(g, x, y) == LEAF) && (d == N) )  //// LEAF= ^ /////
                {
                    if ( ! is_edge_coordinates(g, x , y , N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    
                }   
    
                if( (get_piece(g, x, y) == LEAF) && (d == S) )  //// LEAF= v /////
                {
                    if ( ! is_edge_coordinates(g, x , y , S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }   
                if( (get_piece(g, x, y) == LEAF) && (d == W) )  //// LEAF= < /////
                {
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }     
                if( (get_piece(g, x, y) == LEAF) && (d == E) )  //// LEAF= > /////
                {
                    if ( ! is_edge_coordinates(g, x , y, E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }       
                ///////////////_test_CORNER_/////////////////// 
                if( (get_piece(g, x, y) == CORNER) && (d == N) )  //// CORNER= └ /////
                {
                    if ( ! is_edge_coordinates(g, x , y , N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y , E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    
                }   
                if( (get_piece(g, x, y) == CORNER) && (d == S) ) //// CORNER= ┐ /////
                {
                    if ( ! is_edge_coordinates(g, x , y, S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }   
                if( (get_piece(g, x, y) == CORNER) && (d == W) )//// CORNER= ┘ /////   
                {
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }     
                if( (get_piece(g, x, y) == CORNER) && (d == E) )//// CORNER= ┌ /////
                {
                    if ( ! is_edge_coordinates(g, x , y, E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }       
                ///////////////_test_TEE_///////////////////
                if( (get_piece(g, x, y) == TEE) && (d == N) )  //// TEE= ┴ /////
                {
                    if ( ! is_edge_coordinates(g, x , y, N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    
                }   
                if( (get_piece(g, x, y) == TEE) && (d == S) ) //// TEE= ┬ /////
                {
                    if ( ! is_edge_coordinates(g, x , y, S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }   
                if( (get_piece(g, x, y) == TEE) && (d == W) )//// TEE= ┤ /////   
                {
                    if ( ! is_edge_coordinates(g, x , y, W) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }

                }     
                if( (get_piece(g, x, y) == TEE) && (d == E) )//// TEE= ├ /////
                {
                    if ( ! is_edge_coordinates(g, x , y, E) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, N) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                    if ( ! is_edge_coordinates(g, x , y, S) )
                    {
                        delete_game(g);
                        g = NULL;
                        fprintf(stderr, "Error: connection piece (%d,%d)!\n", x, y);
                        return EXIT_FAILURE;
                    }
                }       

            }//fin else
      }
    }    

    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}



/* ********** TEST opposite_dir *********** */
int test_opposite_dir(int argc, char *argv[])
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
    int w = game_width(g);
    int h = game_height(g);
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            direction d = get_current_dir(g, x, y);
            if(d==N){
                if ( opposite_dir( d ) != S )
                {
                    delete_game(g);
                    g = NULL;
                    fprintf(stderr, "Error: opposite direction (%d,%d)!\n", x, y);
                    return EXIT_FAILURE;
                }
            } 
            if(d==S){
                if ( opposite_dir( d ) != N )
                {
                    delete_game(g);
                    g = NULL;
                    fprintf(stderr, "Error: opposite direction (%d,%d)!\n", x, y);
                    return EXIT_FAILURE;
                }
            }
            if(d==W){
                if ( opposite_dir( d ) != E )
                {
                    delete_game(g);
                    g = NULL;
                    fprintf(stderr, "Error: opposite direction (%d,%d)!\n", x, y);
                    return EXIT_FAILURE;
                }
            }       
            if(d==E){
                if ( opposite_dir( d ) != W )
                {
                    delete_game(g);
                    g = NULL;
                    fprintf(stderr, "Error: opposite direction (%d,%d)!\n", x, y);
                    return EXIT_FAILURE;
                }
            }              
        }
    }    
    delete_game(g);
    g = NULL;
    return EXIT_SUCCESS;
}

/* ********** TEST copy_game *********** */
int test_copy_game (int argc, char *argv[]){

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
    game g_copy=copy_game (g);
    assert(g_copy);

    if ( game_width(g) != game_width(g_copy))
    {
        delete_game(g);
        delete_game(g_copy);
        fprintf(stderr, "Error: copy game width !\n");
        return EXIT_FAILURE;
    }
    if ( game_height(g) != game_height(g_copy))
    {
        delete_game(g);
        delete_game(g_copy);
        fprintf(stderr, "Error: copy game height !\n");
        return EXIT_FAILURE;
    }

    int w = game_width(g);
    int h = game_height(g);
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            direction d = get_current_dir(g, x, y);
            direction d_copy = get_current_dir(g_copy, x, y);

            if (   (get_piece(g, x, y) != get_piece(g_copy, x, y) )  && ( d != d_copy )   )
            {
                delete_game(g);
                delete_game(g_copy);
                fprintf(stderr, "Error: copy game (%d,%d)!\n", x, y);
                return EXIT_FAILURE;
            }
        }
    }
    delete_game(g);
    delete_game(g_copy);  
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
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            if (get_piece(g, x, y) != EMPTY)
            {
                fprintf(stderr, "Error: piece (%d,%d) is not empty!\n", x, y);
                return EXIT_FAILURE;
            }
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
    /*if (strcmp("empty", argv[1]) == 0)
	  status = test_empty(argc, argv);*/
    if (strcmp("is_edge_coordinates", argv[1]) == 0)
        status = test_is_edge_coordinates(argc, argv); 
    else if (strcmp("is_edge", argv[1]) == 0)
        status = test_is_edge(argc, argv); 
    else if (strcmp("opposite_dir", argv[1]) == 0)
        status = test_opposite_dir(argc, argv); 
    else if (strcmp("copy_game", argv[1]) == 0)
        status = test_copy_game(argc, argv);             
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
