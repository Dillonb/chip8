#ifndef CONFIG_H_
#define CONFIG_H_

// Debug mode
#define DEBUG
// How many hz the CPU should run at (standard CHIP-8 is 60, but many games are too sluggish at this speed)
#define EMULATION_SPEED 240

// How many pixels should we use to represent one pixel?
// Mapping pixels 1 to 1 is not ideal with modern high-res displays.
#define SCREEN_X_SCALE_FACTOR 20
#define SCREEN_Y_SCALE_FACTOR 20

// How many FPS should the SDL renderer run at?
#define SDL_FPS 60

// Should we wait for a key press after every instruction?
// #define SINGLE_STEP

// Calculated internals. Do not modify.
#define MS_PER_TICK 1000 / EMULATION_SPEED
#define SDL_TICKS_PER_FRAME 1000 / SDL_FPS
#define SDL_SCREEN_X SCREEN_X * SCREEN_X_SCALE_FACTOR
#define SDL_SCREEN_Y SCREEN_Y * SCREEN_Y_SCALE_FACTOR
#endif // CONFIG_H_
