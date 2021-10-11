#ifndef SDL_PLATFORMER_VIDEO_H
#define SDL_PLATFORMER_VIDEO_H

#include <SDL2/SDL.h>

SDL_Window *video_init(void);
SDL_Renderer *video_create_renderer(SDL_Window *window);
void video_destroy(SDL_Window *window, SDL_Renderer *renderer);

#endif
