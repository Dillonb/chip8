#include "display_sdl.h"
#include <sys/time.h>

SDL_Window* screen;
SDL_Renderer* renderer;
SDL_Texture* screen_tex;

void init_display_sdl() {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SDL_SCREEN_X, SDL_SCREEN_Y, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    screen_tex = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SDL_SCREEN_X,
        SDL_SCREEN_Y);
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

    mem->keyboard[0x0] = state[SDL_SCANCODE_1];
    mem->keyboard[0x1] = state[SDL_SCANCODE_2];
    mem->keyboard[0x2] = state[SDL_SCANCODE_3];
    mem->keyboard[0x3] = state[SDL_SCANCODE_4];
    mem->keyboard[0x4] = state[SDL_SCANCODE_Q];
    mem->keyboard[0x5] = state[SDL_SCANCODE_W];
    mem->keyboard[0x5] = state[SDL_SCANCODE_E];
    mem->keyboard[0x6] = state[SDL_SCANCODE_R];
    mem->keyboard[0x7] = state[SDL_SCANCODE_A];
    mem->keyboard[0x8] = state[SDL_SCANCODE_S];
    mem->keyboard[0x9] = state[SDL_SCANCODE_D];
    mem->keyboard[0xA] = state[SDL_SCANCODE_F];
    mem->keyboard[0xB] = state[SDL_SCANCODE_Z];
    mem->keyboard[0xC] = state[SDL_SCANCODE_X];
    mem->keyboard[0xD] = state[SDL_SCANCODE_C];
    mem->keyboard[0xF] = state[SDL_SCANCODE_V];

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

    if (elapsedTime < MS_PER_TICK) {
        usleep((MS_PER_TICK - elapsedTime) * 1000);
        printf("Sleeping for %d ms\n", MS_PER_TICK - elapsedTime);
    }
}


void cleanup_display_sdl() {
    SDL_Quit();
    return;
}
