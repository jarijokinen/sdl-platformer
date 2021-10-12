#include "player.h"
#include <SDL2/SDL_image.h>

#define SDL_PLATFORMER_PLAYER_MAX_VX 2.5
#define SDL_PLATFORMER_PLAYER_MAX_AX 0.5

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Player player_init(SDL_Renderer *renderer)
{
  SDL_Surface *player_surface = IMG_Load("assets/player_spritesheet.png");
  SDL_Texture *player_texture = 
    SDL_CreateTextureFromSurface(renderer, player_surface);
  SDL_FreeSurface(player_surface);

  return (Player){
    .x = 0.0,
    .y = 0.0,
    .w = 72.0,
    .h = 97.0,
    .vx = 0.0,
    .vy = 0.0,
    .ax = 0.0,
    .ay = 0.0,
    .renderer = renderer,
    .spritesheet = player_texture
  };
}

void player_update(Player *player)
{
  if (player->ax == 0.0) {
    player->vx = 0.0;
  }

  player->vx += player->ax;
  player->x += MAX(MIN(player->vx, SDL_PLATFORMER_PLAYER_MAX_VX), 
      -SDL_PLATFORMER_PLAYER_MAX_VX);
}

void player_render(Player *player)
{
  SDL_Rect src_rect = {
    .x = 0,
    .y = 0,
    .w = 72,
    .h = 97
  };

  SDL_Rect dst_rect = {
    .x = player->x,
    .y = player->y,
    .w = player->w,
    .h = player->h
  };

  SDL_RenderCopy(player->renderer, player->spritesheet, &src_rect, &dst_rect);
}

void player_handle_input(Player *player, const uint8_t *keys)
{
  if (keys[SDL_SCANCODE_D]) {
    player->ax = SDL_PLATFORMER_PLAYER_MAX_AX;
  }
  if (keys[SDL_SCANCODE_A]) {
    player->ax = -SDL_PLATFORMER_PLAYER_MAX_AX;
  }
  if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
    player->ax = 0.0;
  }
}
