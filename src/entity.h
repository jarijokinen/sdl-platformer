#ifndef SDL_PLATFORMER_ENTITY_H
#define SDL_PLATFORMER_ENTITY_H

#include <SDL2/SDL.h>

enum {
  SDL_PLATFORMER_ENTITY_TYPE_BLOCK
};

typedef struct Entity {
  float x;
  float y;
  float w;
  float h;
  float type;
  struct Entity *next;
} Entity;

#endif
