#ifndef DISPLAY_SDL_H_
#define DISPLAY_SDL_H_
#include <SDL2/SDL.h>
#include "memory.h"
#define SCREEN_X_SCALE_FACTOR 10
#define SCREEN_Y_SCALE_FACTOR 10

#define SDL_SCREEN_X SCREEN_X * SCREEN_X_SCALE_FACTOR
#define SDL_SCREEN_Y SCREEN_Y * SCREEN_Y_SCALE_FACTOR


void init_display_sdl();
void update_keyboard_sdl(chip8_mem*);
void draw_sdl(chip8_mem*);
void cleanup_display_sdl();

extern SDL_Window* screen;

#endif
