// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "model.h"
#include "game.h"

#define FOND "sdl/fond.png"
#define LEAF "sdl/leaf.png"
#define SEGMENT "sdl/segment.png"
#define CORNER "sdl/corner.png"
#define TEE "sdl/tee.png"
#define CROSS "sdl/cross.png"

/* **************************************************************** */
     
struct Env_t {  
  SDL_Texture *background;
  SDL_Texture *leaf;
  SDL_Texture *segment;
  SDL_Texture *corner;
  SDL_Texture *tee;
  SDL_Texture *cross;
  int** piece_x, piece_y;
  piece** pieces;
  direction** dir;
}; 
     
/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[])
{  
  Env * env = malloc(sizeof(struct Env_t));
  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init background texture from PNG image */
  env->background = IMG_LoadTexture(ren, FOND);
  if(!env->background) ERROR("IMG_LoadTexture: %s\n", FOND);

  /*init pieces texture from PNG image*/
  env->leaf = IMG_LoadTexture(ren, LEAF);
  if(!env->leaf) ERROR("IMG_LoadTexture: %s\n", LEAF);

  env->segment = IMG_LoadTexture(ren, SEGMENT);
  if(!env->segment) ERROR("IMG_LoadTexture: %s\n", SEGMENT);

  env->corner = IMG_LoadTexture(ren, CORNER);
  if(!env->corner) ERROR("IMG_LoadTexture: %s\n", CORNER);

  env->tee = IMG_LoadTexture(ren, TEE);
  if(!env->tee) ERROR("IMG_LoadTexture: %s\n", TEE);

  env->cross = IMG_LoadTexture(ren, CROSS);
  if(!env->cross) ERROR("IMG_LoadTexture: %s\n", CROSS);

  return env;
}
     
/* **************************************************************** */
     
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{     

  if (e->type == SDL_QUIT) {
    return true;
  }

  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  
  return false; 
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
     
/* **************************************************************** */
