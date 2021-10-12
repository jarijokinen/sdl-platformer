#ifndef SDL_PLATFORMER_ENTITY_H
#define SDL_PLATFORMER_ENTITY_H

#include <SDL2/SDL.h>

enum {
  SDL_PLATFORMER_ENTITY_TYPE_BLOCK
};

typedef struct {
  float x;
  float y;
  float h;
  float w;
  float type;
} Entity;

#endif
