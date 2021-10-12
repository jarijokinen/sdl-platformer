#ifndef SDL_PLATFORMER_PLAYER_H
#define SDL_PLATFORMER_PLAYER_H

#include <SDL2/SDL.h>
#include "level.h"

enum {
  SDL_PLATFORMER_PLAYER_STATE_IDLE,
  SDL_PLATFORMER_PLAYER_STATE_WALK,
  SDL_PLATFORMER_PLAYER_STATE_JUMP_START,
  SDL_PLATFORMER_PLAYER_STATE_JUMP_ACCELERATE
};

typedef struct {
  float x;
  float y;
  float w;
  float h;
  float vx;
  float vy;
  float ax;
  float ay;
  int state;
  SDL_Renderer *renderer;
  SDL_Texture *spritesheet;
} Player;

Player player_init(SDL_Renderer *renderer);
void player_update(Player *player, Level *level);
void player_render(Player *player);
void player_handle_input(Player *player, const uint8_t *keys);

#endif
