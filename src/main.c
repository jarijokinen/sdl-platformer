#include <stdlib.h>
#include "game.h"
#include "video.h"

int main(void)
{
  SDL_Window *window;
  SDL_Renderer *renderer;

  window = video_init();
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
