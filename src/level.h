#ifndef SDL_PLATFORMER_LEVEL_H
#define SDL_PLATFORMER_LEVEL_H

#include "entity.h"
#include <SDL2/SDL.h>

typedef struct {
  SDL_Renderer *renderer;
  SDL_Texture *spritesheet;
  size_t entities_len;
  Entity *entities;
} Level;

Level level_init(SDL_Renderer *renderer);
void level_render(Level *level);

#endif
