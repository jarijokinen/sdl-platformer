#include "level.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

static Entity *level_load_map(void)
{
  char line[128];
  FILE *level_map = fopen("levels/level1.map", "r");

  if (!level_map) {
    fprintf(stderr, "Failed to read the level map file\n");
    exit(EXIT_FAILURE);
  }

  Entity *next = NULL;
  
  while (fgets(line, sizeof(line), level_map)) {
    Entity *entity = malloc(sizeof(Entity));
    sscanf(line, "%f %f %f %f", 
        &(entity->x), &(entity->y), &(entity->w), &(entity->h));
    entity->next = (next) ? next : NULL;
    next = entity;
  }

  fclose(level_map);

  return next;
}

Level level_init(SDL_Renderer *renderer)
{
  SDL_Surface *level_surface = IMG_Load("assets/level_spritesheet.png");
  SDL_Texture *level_texture = SDL_CreateTextureFromSurface(renderer, 
      level_surface);
  SDL_FreeSurface(level_surface);

  Entity *entity = level_load_map();

  return (Level){
    .camx = 0.0,
    .renderer = renderer,
    .spritesheet = level_texture,
    .entities_list = entity
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

  for (Entity *e = level->entities_list; e->next; e = e->next) {
    SDL_Rect dst_rect = {
      .x = e->x - level->camx,
      .y = e->y,
      .w = e->w,
      .h = e->h
    };
    SDL_RenderCopy(level->renderer, level->spritesheet, &src_rect, &dst_rect);
  }
}

void level_destroy(Level *level)
{
  Entity *entity = level->entities_list;
  while (entity) {
    Entity *e = entity;
    entity = entity->next;
    free(e);
  }
}
