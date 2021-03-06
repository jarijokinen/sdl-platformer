#ifndef SDL_PLATFORMER_LEVEL_H
#define SDL_PLATFORMER_LEVEL_H

#include "entity.h"
#include <SDL2/SDL.h>

typedef struct {
  float camx;
  SDL_Renderer *renderer;
  SDL_Texture *spritesheet;
  Entity *entities_list;
} Level;

Level level_init(SDL_Renderer *renderer);
void level_render(Level *level);
void level_destroy(Level *level);

#endif
