#ifndef DISPLAY_SDL_H_
#define DISPLAY_SDL_H_
#include <SDL2/SDL.h>
#include "memory.h"
#define SCREEN_X_SCALE_FACTOR 20
#define SCREEN_Y_SCALE_FACTOR 20

#define SDL_SCREEN_X SCREEN_X * SCREEN_X_SCALE_FACTOR
#define SDL_SCREEN_Y SCREEN_Y * SCREEN_Y_SCALE_FACTOR

#define SDL_FPS 30
#define SDL_TICKS_PER_FRAME 1000 / SDL_FPS

#define EMULATION_SPEED 120
#define MS_PER_TICK 1000 / EMULATION_SPEED

void init_display_sdl();
int should_quit_sdl();
void update_keyboard_sdl(chip8_mem*);
void draw_sdl(chip8_mem*);
void cleanup_display_sdl();
void pre_tick_sdl();
void post_tick_sdl();

extern SDL_Window* screen;

#endif
