#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"



struct game_s {

    int width;
    int height;
    piece *p;
    direction *d;
    direction *d_init;

};
#define DEFAULT_SIZE 5

game new_game_empty(){

	  game g = malloc(sizeof(struct game_s));
    g->p = (piece*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(piece));
    if  (g->p == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }
    g->d = (direction*)calloc(DEFAULT_SIZE*DEFAULT_SIZE, sizeof(direction));
    if  (g->d == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }
    g->d_init = (direction*)calloc(DEFAULT_SIZE*DEFAULT_SIZE, sizeof(direction));
        if  (g->d_init == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }

    for(int i=0; i < DEFAULT_SIZE*DEFAULT_SIZE; i++){
      g->p[i] = EMPTY;
    }
    g->height = DEFAULT_SIZE;
    g->width = DEFAULT_SIZE;

	return g;
}
    // TO DO
   

game new_game(piece *pieces, direction *initial_directions){
    if (pieces == NULL || initial_directions == NULL)
    {
        fprintf(stderr,"Pas de pieces ou de direction");
        EXIT_FAILURE;
    }
    game g = (game)malloc(sizeof(struct game_s));
    g->p = (piece*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(piece));
    if  (g->p == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }

    g->d =(direction*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(direction));
    if  (g->d == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }
    g->d_init =(direction*)malloc((DEFAULT_SIZE*DEFAULT_SIZE)*sizeof(direction));
        if  (g->d_init == NULL)
    {
       fprintf(stderr, "Error: malloc\n");
        EXIT_FAILURE; 
    }
    for(int i = 0; i < DEFAULT_SIZE*DEFAULT_SIZE; i++){
  	  g->p[i] = pieces[i];
      g->d[i] = initial_directions[i];
      g->d_init[i] = initial_directions[i];
    }
    g->height = DEFAULT_SIZE;
    g->width = DEFAULT_SIZE;
	return g;
} 
    // TO DO
 

void set_piece(game g, int x, int y, piece piece, direction orientation)
{
    
    if (g == NULL)
    {
        fprintf(stderr,"g = NULL");
        EXIT_FAILURE;
    }
    if (piece < -1 || piece > 3 || orientation <0 || orientation > 3 || x >= g->width || y >= g->height || x < 0 || y < 0)
    {
        delete_game(g);
        g = NULL;
        fprintf(stderr, "Error: Incorrect param!\n");
        EXIT_FAILURE; 
    }
 
    int w = g->width;
    g->p[x+y*w]= piece;
    g->d[x+y*w] = orientation;
    g->d_init[x+y*w] = orientation;
  
}


void shuffle_dir(game g)
{
    int w = g->width; 
    int h = g->height; 
    for (int y = 0; y < h; y++)
    {
       for (int x = 0; x < w; x++)
        {
           
        g->d[x+(w*y)]= rand()%4;

        /*
        int alea = rand()%4;
        switch(alea)
        {
         case 0: g->d[x+(5*y)]= N; break;
         case 1: g->d[x+(5*y)]= S; break;
         case 2: g->d[x+(5*y)]= E; break;
         case 3: g->d[x+(5*y)]= W; break;
        }
        */
        }
        
    }
}


int game_height(cgame game){
	if(game){
         return game->height;
     }
     fprintf(stderr,"Appel de game_width avec un pointeur NULL\n");
     exit(EXIT_FAILURE);
}
 
  

int game_width(cgame game){
     if(game){
         return game->width;
     }
     fprintf(stderr,"Appel de game_width avec un pointeur NULL\n");
     exit(EXIT_FAILURE);
}


void rotate_piece_one(game game, int x, int y){
  if(game){
    if(x < game->width&& y < game->height){
      game->p[y*game->width+x] = (game->p[y*game->width+x] + 1) % 4;
    }
  }
}


void rotate_piece(game game, int x, int y, int nb_cw_quarter_turn){
 if(game){
   if(x < game->width&& y < game->height){
     game->p[y*game->width+x] = (game->p[y*game->width+x] + nb_cw_quarter_turn) % 4;
   }
 }
}


void set_piece_current_dir (game game, int x, int y, direction dir){
  if(game){
   if(x < game->width&& y < game->height){
     game->p[y*game->width+x] = dir;
   }
 }
}


bool is_edge_coordinates(cgame g, int x, int y, direction dir){
  int index;
  int w = (*g).width;
  int h = (*g).height;
  for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            if ( (x == 0) || (x == g->width-1) || (y == 0) || (y == g->height-1) ){
              switch (dir){
                case N:
                  if (y==g->height-1){
                    return false;
                  }
                  break;
                case E:
                  if (x==g->width-1){
                    return false;
                  }
                  break;
                case S:
                  if (y==0){
                    return false;
                  }
                  break;
                case W:
                  if (x==0){
                    return false;
                  }
                  break;
                
              }
            }
        }
  }
  index=x+(y*w);
  piece p = g->p[index];
  direction d = g->d[index];
  return is_edge(p, d, dir);
 
}



bool is_edge(piece piece, direction orientation, direction dir){
	///////////////_SEGMENT_/////////////////
    if(piece==SEGMENT){ 
        switch(orientation){
            
            case N: //// SEGMENT= | /////
                    if(dir == N || dir == S)
                    {
                        return true;
                    }
                    break;
            case S: //// SEGMENT= | /////
                    if(dir == N || dir == S)
                    {
                        return true;
                    } 
                    break;
            case E: //// SEGMENT= - /////
                    if ( dir == W || dir == E )
                    {    
                        return true;
                    }
                    break;        
            case W: //// SEGMENT= - /////
                    if ( dir == W || dir == E )
                    {    
                        return true;
                    }        
                    break;
            default: return false;
        } 
    }

///////////////_test_LEAF_////////////////////        
	if(piece==LEAF){ 
        switch(orientation){
            
            case N: //// LEAF= ^ /////
                    if(dir == N)
                    {
                        return true;
                    }
                    break;
            case S: //// LEAF= v /////
                    if(dir == S)
                    {
                        return true;
                    } 
                    break;
            case E: //// LEAF= > /////
                    if (dir == E)
                    {    
                        return true;
                    }
                    break;
            case W: //// LEAF= < /////
                    if ( dir == W)
                    {    
                        return true;
                    }
                    break;        
            default: return false;
        } 
    }

///////////////_test_CORNER_///////////////////
    if(piece==CORNER){ 
        switch(orientation){
            
            case N: //// CORNER= └ /////
                    if(dir == N || dir == E)
                    {
                        return true;
                    }
                    break;
            case S: //// CORNER= ┐ /////
                    if(dir == S|| dir == W )
                    {
                        return true;
                    } 
                    break;
            case E: //// CORNER= ┌ /////
                    if ( dir == S || dir == E )
                    {    
                        return true;
                    }
                    break;
            case W: //// CORNER= ┘ ///// 
                    if ( dir == W || dir == N)
                    {    
                        return true;
                    }
                    break;        
            default: return false;
        } 
    }

///////////////_test_TEE_///////////////////
    if(piece==TEE){ 
        switch(orientation){

            case N:  //// TEE= ┴ /////
                    if ( dir == N || dir == E || dir == W )
                    {
                        return true;
                    }
                    break;
            case S: //// TEE= ┬ /////            
                    if ( dir == S || dir == E || dir == W )
                        {
                            return true;
                        }
                    break;
            case W://// TEE= ┤ /////   
                    if ( dir == N || dir == S || dir == W )
                    {
                        return true;
                    }
                    break;    
            case E: //// TEE= ├ /////
                    if ( dir == N || dir == E || dir == S )
                    {
                        return true;
                    }
                    break;  
            default: return false;
        } 
    }

///////////////////////////////////////////////
    return false;
}
  


direction opposite_dir(direction dir){
	
	if ( dir == S )
    {
        return N;
    }
            
    if(dir == N)
    {
        return S;        
    }

    if(dir == W)
    {     
        return E;       
    }       

    if(dir==E)
    {
        return W;
    }    
    else{
       fprintf(stderr, "incompatible direction!\n");
       exit (EXIT_FAILURE); 
    }   
} 



game copy_game (cgame g_src){
	 struct game_s* g=(struct game_s*) malloc (sizeof(struct game_s));
      // On verifie si la memoire a ete allouee
    if (g == NULL) { 
        fprintf(stderr, "not enough memory!\n");
        exit (EXIT_FAILURE);
    }
    
      /////////////////////////  

    (*g).width = (*g_src).width;
    (*g).height = (*g_src).height;
    if ( (*g).width == 0 ) 
    {
        fprintf(stderr, "paramétre copy invalid! width = 0!\n");
        exit (EXIT_FAILURE);
    }
    if ((*g).height == 0) {
        fprintf(stderr, "paramétre copy invalid! height = 0!\n");
        exit (EXIT_FAILURE);
    }

      //////////////////////////

    (*g).p =(piece*) malloc (  (sizeof( (*g_src).p) )  );
      // On verifie si la memoire a ete allouee
    if ((*g).p == NULL) {
        fprintf(stderr, "not enough memory!\n");
        exit(EXIT_FAILURE);
    }

    (*g).d =(direction*) malloc (  (sizeof( (*g_src).d) )  );
      // On verifie si la memoire a ete allouee
    if ((*g).d == NULL) {
        fprintf(stderr, "not enough memory!\n");
        exit(EXIT_FAILURE);
    }
    
    (*g).d_init =(direction*) malloc (  (sizeof( (*g_src).d_init) )  );
      // On verifie si la memoire a ete allouee
    if ((*g).d_init == NULL) {
        fprintf(stderr, "not enough memory!\n");
        exit(EXIT_FAILURE);
    }
    
      ///////////////////////////

    int w = (*g).width;
    int h = (*g).height;
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++)
        {
            (*g).d[y*x+x] = (*g_src).d[y*x+x];
            (*g).p[y*x+x] = (*g_src).p[y*x+x];
            (*g).d_init[y*x+x] = (*g_src).d_init[y*x+x];
        }
    }
    g = new_game((*g).p, (*g).d);
	return g;
}
  


void delete_game (game g){
}
     // TO DO


piece get_piece(cgame game, int x, int y){
	return 0;
}
     // TO DO


direction get_current_dir(cgame g, int x, int y){
	return 0;
}
     // TO DO


bool is_game_over (cgame g){
	return true;
}
     // TO DO


void restart_game(game g){
}
     // TO DO

