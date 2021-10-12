#ifndef SDL_PLATFORMER_PLAYER_H
#define SDL_PLATFORMER_PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
  float vx;
  float vy;
  float ax;
  float ay;
  SDL_Renderer *renderer;
  SDL_Texture *spritesheet;
} Player;

Player player_init(SDL_Renderer *renderer);
void player_update(Player *player);
void player_render(Player *player);
void player_handle_input(Player *player, const uint8_t *keys);

#endif
