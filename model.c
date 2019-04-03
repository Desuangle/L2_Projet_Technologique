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
#define IMG_FOND "./sdl/fond.png"
#define IMG_EMPTY "./sdl/empty.png"
#define IMG_LEAF "./sdl/leaf.png"
#define IMG_SEGMENT "./sdl/segment.png"
#define IMG_CORNER "./sdl/corner.png"
#define IMG_TEE "./sdl/tee.png"
#define IMG_CROSS "./sdl/cross.png"
#define IMGRED_LEAF "./sdl/leaf_red.png"
#define IMGRED_SEGMENT "./sdl/segment_red.png"
#define IMGRED_CORNER "./sdl/corner_red.png"
#define IMGRED_TEE "./sdl/tee_red.png"
#define IMGRED_CROSS "./sdl/cross_red.png"
#define FONT "./sdl/Arial.ttf"
#define FONTSIZE 56


/* **************************************************************** */
     
struct Env_t {  
  SDL_Texture *background;
  SDL_Texture *leaf;
  SDL_Texture *endleaf;
  SDL_Texture *segment;
  SDL_Texture *endsegment;
  SDL_Texture *corner;
  SDL_Texture *endcorner;
  SDL_Texture *tee;
  SDL_Texture *endtee;
  SDL_Texture *cross;
  SDL_Texture *endcross;
  SDL_Texture *empty;
  game jeu;
  int piece_x, piece_y;
  SDL_Texture *text;
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

  env->empty = IMG_LoadTexture(ren, IMG_EMPTY);
  if(!env->empty) ERROR("IMG_LoadTexture: %s\n", IMG_EMPTY);

  /* these piieces textures will be loaded when the game is over */
  env->endleaf = IMG_LoadTexture(ren, IMGRED_LEAF);
  if(!env->endleaf) ERROR("IMG_LoadTexture: %s\n", IMGRED_LEAF);

  env->endsegment = IMG_LoadTexture(ren, IMGRED_SEGMENT);
  if(!env->endsegment) ERROR("IMG_LoadTexture: %s\n", IMGRED_SEGMENT);

  env->endcorner = IMG_LoadTexture(ren, IMGRED_CORNER);
  if(!env->endcorner) ERROR("IMG_LoadTexture: %s\n", IMGRED_CORNER);

  env->endtee = IMG_LoadTexture(ren, IMGRED_TEE);
  if(!env->endtee) ERROR("IMG_LoadTexture: %s\n", IMGRED_TEE);

  env->endcross = IMG_LoadTexture(ren, IMGRED_CROSS);
  if(!env->endcross) ERROR("IMG_LoadTexture: %s\n", IMGRED_CROSS);

  /* init text texture using Arial font */
  SDL_Color color = { 0, 158, 253, 56 }; 
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "You Win!", color); 
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);

  /* load_game */
  if (argc==2) {
    env->jeu = load_game(argv[1]);
  }
  else {
    env->jeu = load_game("default.txt");
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

  if (w < h)
    h = w;
  else
    w = h;
  
  /* render background texture */
  SDL_RenderCopy(ren, env->background, NULL, NULL); /* stretch it */

  piece p;
  direction d;
  bool gameover = is_game_over(env->jeu);

  int w_jeu = game_width(env->jeu);
  int h_jeu = game_height(env->jeu);

  /* init positions */
  SDL_Texture* current_piece;
  for(int y=game_height(env->jeu)-1; y>=0 ;y--){
    for(int x=0; x<w_jeu; x++){
      p=get_piece(env->jeu,x,y);
      d=get_current_dir(env->jeu,x,y);
      if (gameover){
	/* render text texture */
  	SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  	rect.x = w/2 - rect.w/2; rect.y = h/2 - rect.h/2; 
  	SDL_RenderCopy(ren, env->text, NULL, &rect);
	if(p == LEAF)
          current_piece = env->endleaf;
        else if (p == SEGMENT)
          current_piece = env->endsegment;
        else if (p == CORNER)
          current_piece = env->endcorner;
        else if (p == TEE)
          current_piece = env->endtee;
        else if (p == CROSS)
          current_piece = env->endcross;
        else
          current_piece = env->empty;
	      }
      else{
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
          current_piece = env->empty;
      }
      SDL_QueryTexture(current_piece, NULL, NULL, &rect.w, &rect.h);
      rect.x = x * (w / w_jeu); rect.y = (h_jeu - 1 - y) * (h / h_jeu); rect.w = w / w_jeu; rect.h = h/h_jeu;
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

  if (w < h)
    h = w;
  else
    w = h;

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
    if(e->button.button == SDL_BUTTON_LEFT)
      {
	rotate_piece(env->jeu, mouse.x /(w / game_width(env->jeu)), game_height(env->jeu) - 1 - mouse.y /(h / game_height(env->jeu)),3);
      }
    else
      {
        rotate_piece_one(env->jeu, mouse.x /(w / game_width(env->jeu)), game_height(env->jeu) - 1 - mouse.y /(h / game_height(env->jeu)));
      }
  }
  else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
	    /*
    case SDLK_LEFT:  env->piece_x -= 10; break;
    case SDLK_RIGHT: env->piece_x += 10; break;
    case SDLK_UP:    env->piece_y -= 10; break;
    case SDLK_DOWN:  env->piece_y += 10; break;
	    */
    case SDLK_ESCAPE:  return true; break;      
    }
  }  
#endif

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

/* **************************************************************** */
