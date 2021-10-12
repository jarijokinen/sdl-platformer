#define _POSIX_C_SOURCE 200809L
#include "level.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

Level level_init(SDL_Renderer *renderer)
{
  SDL_Surface *level_surface = IMG_Load("assets/level_spritesheet.png");
  SDL_Texture *level_texture = SDL_CreateTextureFromSurface(renderer, 
      level_surface);
  SDL_FreeSurface(level_surface);

  FILE *level_map;
  char *line = NULL;
  size_t len = 0;

  size_t entities_len = 2;
  Entity *entities = malloc(sizeof(*entities) * entities_len);

  level_map = fopen("levels/level1.map", "r");
  if (!level_map) {
    fprintf(stderr, "Failed to read the level map file\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < entities_len; i++) {
    getline(&line, &len, level_map);
    sscanf(line, "%f %f %f %f", 
      &(entities[i].x),
      &(entities[i].y),
      &(entities[i].w),
      &(entities[i].h)
    );
  }

  return (Level){
    .renderer = renderer,
    .spritesheet = level_texture,
    .entities_len = entities_len,
    .entities = entities
  };
}

void level_render(Level *level)
{
  SDL_Rect src_rect = {
    .x = 0,
    .y = 0,
    .w = 70,
    .h = 70
  };

  for (size_t i = 0; i < level->entities_len; i++) {
    SDL_Rect dst_rect = {
      .x = level->entities[i].x,
      .y = level->entities[i].y,
      .w = level->entities[i].w,
      .h = level->entities[i].h
    };
    SDL_RenderCopy(level->renderer, level->spritesheet, &src_rect, &dst_rect);
  }
}

void level_destroy(Level *level)
{
  free(level->entities);
}
