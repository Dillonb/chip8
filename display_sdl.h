#ifndef DISPLAY_SDL_H_
#define DISPLAY_SDL_H_
#include <SDL2/SDL.h>
#include "memory.h"
#include "config.h"


void init_display_sdl(char*);
int should_quit_sdl();
void update_keyboard_sdl(chip8_mem*);
void draw_sdl(chip8_mem*);
void cleanup_display_sdl();
void pre_tick_sdl();
void post_tick_sdl();
void newGame();
void menu_quit_sdl();

extern SDL_Window* screen;

#endif
