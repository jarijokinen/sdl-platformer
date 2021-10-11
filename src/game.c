#include <stdbool.h>
#include "game.h"

void game_loop(SDL_Renderer *renderer)
{
  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
      }
    }
  }
}
