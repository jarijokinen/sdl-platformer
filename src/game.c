#include <SDL2/SDL_keyboard.h>
#include <stdbool.h>
#include "game.h"
#include "player.h"

void game_update(Player *player)
{
  player_update(player);
}

void game_render(SDL_Renderer *renderer, Player *player)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  player_render(player);
  SDL_RenderPresent(renderer);
}

void game_loop(SDL_Renderer *renderer)
{
  bool running = true;
  SDL_Event event;

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
    game_update(&player);
    game_render(renderer, &player);
  }
}
