#include "video.h"

#define SDL_PLATFORMER_WINDOW_TITLE "Platformer"
#define SDL_PLATFORMER_WINDOW_WIDTH 800
#define SDL_PLATFORMER_WINDOW_HEIGHT 600

SDL_Window *video_init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL: %s", SDL_GetError());
    return NULL;
  }

  SDL_Window *window = SDL_CreateWindow(SDL_PLATFORMER_WINDOW_TITLE,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SDL_PLATFORMER_WINDOW_WIDTH, SDL_PLATFORMER_WINDOW_HEIGHT, 
      SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "Failed to create window: %s", SDL_GetError());
    return NULL;
  }

  return window;
}

SDL_Renderer *video_create_renderer(SDL_Window *window)
{
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
    return NULL;
  }

  return renderer;
}

void video_destroy(SDL_Window *window, SDL_Renderer *renderer)
{
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }

  SDL_Quit();
}
