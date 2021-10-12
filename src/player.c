#include "player.h"
#include <SDL2/SDL_image.h>

#define SDL_PLATFORMER_PLAYER_MAX_VX 2.5
#define SDL_PLATFORMER_PLAYER_MAX_AX 0.5
#define SDL_PLATFORMER_PLAYER_MAX_VY 9.0
#define SDL_PLATFORMER_PLAYER_MAX_AY 18.0
#define SDL_PLATFORMER_PLAYER_GRAVITY_AY 3.0

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static const int player_walk_sprites[3][4] = {
  { 0, 97, 72, 97 },
  { 72, 97, 72, 97 },
  { 144, 97, 72, 97 }
};

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
    .h = 92.0,
    .vx = 0.0,
    .vy = 0.0,
    .ax = 0.0,
    .ay = 0.0,
    .state = SDL_PLATFORMER_PLAYER_STATE_IDLE,
    .facing = SDL_PLATFORMER_PLAYER_FACING_RIGHT,
    .animation_frame = 0,
    .renderer = renderer,
    .spritesheet = player_texture
  };
}

int player_check_collision(Level *level, float x, float y, float w, float h)
{
  SDL_Rect player_rect = {
    .x = x,
    .y = y,
    .w = w,
    .h = h
  };
  
  for (Entity *e = level->entities_list; e->next; e = e->next) {
    SDL_Rect entity_rect = {
      .x = e->x,
      .y = e->y,
      .w = e->w,
      .h = e->h
    };

    if (SDL_HasIntersection(&player_rect, &entity_rect)) {
      return 1;
    }
  }

  return 0;
}

void player_update(Player *player, Level *level) {
  // Jumping
  if (player->state == SDL_PLATFORMER_PLAYER_STATE_JUMP_START) {
    player->vy -= 30.0;
    player->state = SDL_PLATFORMER_PLAYER_STATE_JUMP_ACCELERATE;
  }
  if (player->state == SDL_PLATFORMER_PLAYER_STATE_JUMP_ACCELERATE) {
    if (player->vy < -400.0) {
      player->state = SDL_PLATFORMER_PLAYER_STATE_IDLE;
      player->vy = 0.0;
    } else {
      player->state = SDL_PLATFORMER_PLAYER_STATE_IDLE;
      player->vy -= 16.0;
    }
  }

  // Gravity
  player->vy += SDL_PLATFORMER_PLAYER_GRAVITY_AY;

  // Collision detection for Y-axis
  float new_y = player->y + MAX(MIN(player->vy, SDL_PLATFORMER_PLAYER_MAX_VY), 
      -SDL_PLATFORMER_PLAYER_MAX_VY);
  if (player_check_collision(level, player->x, new_y, player->w, player->h)) {
    player->vy = 0.0;
  }
  else {
    player->y = new_y;
  }
  
  // Walk
  if (player->ax == 0.0) {
    player->vx = 0.0;
  }
  player->vx += player->ax;

  // Collision detection for X-axis
  float new_x = player->x + MAX(MIN(player->vx, SDL_PLATFORMER_PLAYER_MAX_VX), 
      -SDL_PLATFORMER_PLAYER_MAX_VX);
  if (player_check_collision(level, new_x, player->y, player->w, player->h)) {
    player->vx = 0.0;
  } else {
    player->x = new_x;
  }

  // Animation frame
  player->animation_frame = (SDL_GetTicks() / 100) % 3;
}

void player_render(Player *player)
{
  SDL_Rect src_rect = {
    .x = 73,
    .y = 0,
    .w = 72,
    .h = 92
  };

  switch (player->state) {
    case SDL_PLATFORMER_PLAYER_STATE_WALK:
      src_rect.x = player_walk_sprites[player->animation_frame][0];
      src_rect.y = player_walk_sprites[player->animation_frame][1];
      break;
  };

  SDL_Rect dst_rect = {
    .x = player->x,
    .y = player->y,
    .w = player->w,
    .h = player->h
  };

  if (player->facing == SDL_PLATFORMER_PLAYER_FACING_RIGHT) {
    SDL_RenderCopy(player->renderer, player->spritesheet, &src_rect, &dst_rect);
  } else {
    SDL_RenderCopyEx(player->renderer, player->spritesheet, &src_rect, &dst_rect,
        0, NULL, SDL_FLIP_HORIZONTAL);
  }
}

void player_handle_input(Player *player, const uint8_t *keys)
{
  if (keys[SDL_SCANCODE_D]) {
    player->state = SDL_PLATFORMER_PLAYER_STATE_WALK;
    player->facing = SDL_PLATFORMER_PLAYER_FACING_RIGHT;
    player->ax = SDL_PLATFORMER_PLAYER_MAX_AX;
  }
  if (keys[SDL_SCANCODE_A]) {
    player->state = SDL_PLATFORMER_PLAYER_STATE_WALK;
    player->facing = SDL_PLATFORMER_PLAYER_FACING_LEFT;
    player->ax = -SDL_PLATFORMER_PLAYER_MAX_AX;
  }
  if (!keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
    player->state = SDL_PLATFORMER_PLAYER_STATE_IDLE;
    player->ax = 0.0;
  }
  if (keys[SDL_SCANCODE_SPACE]) {
    if ((player->state == SDL_PLATFORMER_PLAYER_STATE_IDLE ||
        player->state == SDL_PLATFORMER_PLAYER_STATE_WALK) &&
        player->vy == 0.0) {
      player->state = SDL_PLATFORMER_PLAYER_STATE_JUMP_START;
    }
  }
}
