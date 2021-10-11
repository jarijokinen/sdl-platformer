#include <stdlib.h>
#include "game.h"
#include "video.h"

#define SDL_PLATFORMER_WINDOW_TITLE "Platformer"
#define SDL_PLATFORMER_WINDOW_WIDTH 800
#define SDL_PLATFORMER_WINDOW_HEIGHT 600

int main(void)
{
  SDL_Window *window;
  SDL_Renderer *renderer;

  window = video_init(SDL_PLATFORMER_WINDOW_TITLE, SDL_PLATFORMER_WINDOW_WIDTH, 
      SDL_PLATFORMER_WINDOW_HEIGHT);
  if (!window) {
    exit(EXIT_FAILURE);
  }

  renderer = video_create_renderer(window);
  if (!renderer) {
    exit(EXIT_FAILURE);
  }

  game_loop(renderer);

  video_destroy(window, renderer);

  exit(EXIT_SUCCESS);
}
