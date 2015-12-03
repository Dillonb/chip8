#include "display_sdl.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window* screen;
SDL_Renderer* renderer;
SDL_Texture* screen_tex;

SDL_Scancode keymappings[0x10];

void init_display_sdl(char* filename) {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SDL_SCREEN_X, SDL_SCREEN_Y, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    screen_tex = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SDL_SCREEN_X,
        SDL_SCREEN_Y);

    size_t len = strlen(filename);

    char *newfilename = malloc(len);
    memcpy(newfilename, filename, len-3);
    newfilename[len - 3] = 0;
    filename = strcat(newfilename, "key");
    printf("%s\n", filename);

    FILE * fp;
    char * line = NULL;
    ssize_t read;

    fp = fopen(newfilename, "r");

    unsigned char keycode = 0x0;

    while ((read = getline(&line, &len, fp)) != -1) {
        line[strlen(line) - 1] = '\0';
        keymappings[keycode] = SDL_GetScancodeFromName(line);
        keycode++;
    }

    return;

}

int shouldQuit = 0;

int should_quit_sdl() {
    return shouldQuit;
}

void update_keyboard_sdl(chip8_mem* mem) {

    SDL_PumpEvents();

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE]) {
        SDL_Quit();
        shouldQuit = 1;
    }

    unsigned char keycode = 0x0;

    for (keycode = 0x0; keycode < 0x10; keycode++) {
        mem->keyboard[keycode] = state[keymappings[keycode]];
    }

    return;
}

void draw_sdl(chip8_mem* mem) {
    int i, j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (i = 0; i < SCREEN_Y; i++) {
        for (j = 0; j < SCREEN_X; j++) {
            if (mem->screen[j][i]) {
                SDL_Rect dstRect;
                dstRect.x = j * SCREEN_X_SCALE_FACTOR;
                dstRect.y = i * SCREEN_Y_SCALE_FACTOR;
                dstRect.w = SCREEN_X_SCALE_FACTOR;
                dstRect.h = SCREEN_Y_SCALE_FACTOR;

                SDL_RenderFillRect(renderer, &dstRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

long long startTime = 0;
long long endTime = 0;
long long elapsedTime = 0;
struct timeval tv;

void pre_tick_sdl() {
    gettimeofday(&tv, NULL);
    startTime = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

long long timeSince(long long startTime) {
    gettimeofday(&tv, NULL);
    long long temp = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    return temp - startTime;
}

void post_tick_sdl() {
    gettimeofday(&tv, NULL);
    elapsedTime = timeSince(startTime);

    // Sleep for the remaining time per frame
    if (elapsedTime < MS_PER_TICK) {
        usleep((MS_PER_TICK - elapsedTime) * 1000);
    }
}


void cleanup_display_sdl() {
    SDL_Quit();
    return;
}
