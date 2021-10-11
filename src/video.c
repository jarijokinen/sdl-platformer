#include "video.h"

SDL_Window *video_init(char *title, int window_width, int window_height)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
    return NULL;
  }

  SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
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
