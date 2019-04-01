// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include "game.h"
#include "game_io.h"
#define IMG_FOND "../sdl/fond.png"
#define IMG_LEAF "../sdl/leaf.png"
#define IMG_SEGMENT "../sdl/segment.png"
#define IMG_CORNER "../sdl/corner.png"
#define IMG_TEE "../sdl/tee.png"
#define IMG_CROSS "../sdl/cross.png"

void TournePiece(game g,int mouse_x, int mouse_y, int click, int hfenetre, int wfenetre, int hgame, int wgame);

/* **************************************************************** */
     
struct Env_t {  
  SDL_Texture *background;
  SDL_Texture *leaf;
  SDL_Texture *segment;
  SDL_Texture *corner;
  SDL_Texture *tee;
  SDL_Texture *cross;
  game jeu;
  int piece_x, piece_y;
  //SDL_Texture **pieces;
  //direction** dir;
}; 
     
/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));
  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, IMG_FOND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", IMG_FOND);

  /*init pieces texture from PNG image*/
  env->leaf = IMG_LoadTexture(ren, IMG_LEAF);
  if(!env->leaf) ERROR("IMG_LoadTexture: %s\n", IMG_LEAF);

  env->segment = IMG_LoadTexture(ren, IMG_SEGMENT);
  if(!env->segment) ERROR("IMG_LoadTexture: %s\n", IMG_SEGMENT);

  env->corner = IMG_LoadTexture(ren, IMG_CORNER);
  if(!env->corner) ERROR("IMG_LoadTexture: %s\n", IMG_CORNER);

  env->tee = IMG_LoadTexture(ren, IMG_TEE);
  if(!env->tee) ERROR("IMG_LoadTexture: %s\n", IMG_TEE);

  env->cross = IMG_LoadTexture(ren, IMG_CROSS);
  if(!env->cross) ERROR("IMG_LoadTexture: %s\n", IMG_CROSS);

  /* load_game */
  if (argc==2) {
    env->jeu = load_game(argv[1]);
  }
  else {
    env->jeu = load_game("game34.txt");
  }
  return env;
}
     
/* **************************************************************** */
     
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  SDL_Rect rect;  
 
  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h); // Récupère la taille actuelle de la fenêtre dans w et h

  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  piece p;
  direction d;

  int w_jeu = game_width(env->jeu);
  int h_jeu = game_height(env->jeu);

  /* init positions */
  // env->piece_x = w_jeu/2;
  // env->piece_y = h_jeu/2;
  SDL_Texture* current_piece;
  for(int y=game_height(env->jeu)-1; y>=0 ;y--){
    for(int x=0; x<w_jeu; x++){
      p=get_piece(env->jeu,x,y);
      d=get_current_dir(env->jeu,x,y);

      

      if(p == LEAF)
        current_piece = env->leaf;
      else if (p == SEGMENT)
        current_piece = env->segment;
      else if (p == CORNER)
        current_piece = env->corner;
      else if (p == TEE)
        current_piece = env->tee;
      else if (p == CROSS)
        current_piece = env->cross;
      else
        current_piece = env->cross;
      SDL_QueryTexture(current_piece, NULL, NULL, &rect.w, &rect.h);
      rect.x = x * (w / w_jeu)/* - rect.w/2*/; rect.y = (h_jeu - y) * (h / h_jeu); rect.w = w / w_jeu; rect.h = h/h_jeu;
      //SDL_RenderCopy(ren, current_piece, NULL, &rect);
      SDL_RenderCopyEx(ren, current_piece, NULL, &rect, 90*d, NULL, SDL_FLIP_NONE);  
    }
  }

}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{     

  int w, h;
  SDL_GetWindowSize(win, &w, &h);  

  /* generic events */  
  if (e->type == SDL_QUIT) {
    return true;
  }
  /* Android events */  
#ifdef __ANDROID__ 
  else if (e->type == SDL_FINGERDOWN) {    
    env->piece_x = e->tfinger.x * w; /* tfinger.x, normalized in [0..1] */
    env->piece_y = e->tfinger.y * h; /* tfinger.y, normalized in [0..1] */
  }
  /* other events */  
#else
  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse; 
    SDL_GetMouseState(&mouse.x, &mouse.y);    
    env->piece_x = mouse.x;
    env->piece_y = mouse.y;    
  }
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
    case SDLK_LEFT:  env->piece_x -= 10; break;
    case SDLK_RIGHT: env->piece_x += 10; break;
    case SDLK_UP:    env->piece_y -= 10; break;
    case SDLK_DOWN:  env->piece_y += 10; break;
    case SDLK_ESCAPE:  return true; break;      
    }
  }  
#endif

  if(e->type == SDL_MOUSEBUTTONDOWN){
  SDL_Point mouse; 
  SDL_GetMouseState(&mouse.x, &mouse.y);
  fprintf(stderr, "mouse x : %d mouse y : %d\n", mouse.x, mouse.y);
  
  if(e->button.button == SDL_BUTTON_LEFT)
  {
    TournePiece(env->jeu,mouse.x,mouse.y,1,w,h,game_height(env->jeu),game_width(env->jeu));
    fprintf(stderr, "Dir_piece : %d\n", get_current_dir(env->jeu,0,0));
    }
  else
  {
    TournePiece(env->jeu,mouse.x,mouse.y,2,w,h,game_height(env->jeu),game_width(env->jeu));
    }
  }

  return false; /* don't quit */
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  SDL_DestroyTexture(env->background);
  SDL_DestroyTexture(env->leaf);
  SDL_DestroyTexture(env->segment);
  SDL_DestroyTexture(env->corner);
  SDL_DestroyTexture(env->tee);
  SDL_DestroyTexture(env->cross);

  free(env);
}

void TournePiece(game g,int mouse_x, int mouse_y, int click, int hfenetre, int wfenetre, int hgame, int wgame)
{
  int piece_x= mouse_x /(wfenetre/wgame);
  int piece_y= mouse_y /(hfenetre/hgame);
  fprintf(stderr, "Func x : %d Func y : %d\n", piece_x, piece_y);
  if (click==1)
  {
    rotate_piece(g,piece_x,piece_y,3);
  }
  else
  {
    rotate_piece_one(g,piece_x,piece_y);
  }
}
/* **************************************************************** */
