#include <stdbool.h>
#include "game.h"
#include "level.h"
#include "player.h"

void game_update(Level *level, Player *player)
{
  player_update(player, level);
}

void game_render(SDL_Renderer *renderer, Level *level, Player *player)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  level_render(level);
  player_render(player);
  SDL_RenderPresent(renderer);
}

void game_loop(SDL_Renderer *renderer)
{
  bool running = true;
  SDL_Event event;

  Level level = level_init(renderer);
  Player player = player_init(renderer); 
  const uint8_t *keys = SDL_GetKeyboardState(NULL);

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    player_handle_input(&player, keys);
    game_update(&level, &player);
    game_render(renderer, &level, &player);
  }

  level_destroy(&level);
}
