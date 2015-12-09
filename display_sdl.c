#include "display_sdl.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "cpu.h"

SDL_Window* screen;
SDL_Renderer* renderer;
SDL_Texture* screen_tex;

#ifdef DEBUG
SDL_Window* status_screen;
SDL_Renderer* status_renderer;
SDL_Texture* status_screen_tex;
TTF_Font* terminus = NULL;
SDL_Surface* textSurface = NULL;
SDL_Texture* textTexture = NULL;
char* statusText;
#endif // DEBUG

SDL_Scancode keymappings[0x10];

void init_display_sdl(char* filename) {
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_CreateWindow("Chip-8", 475, SDL_WINDOWPOS_CENTERED,
            SDL_SCREEN_X, SDL_SCREEN_Y, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    screen_tex = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SDL_SCREEN_X,
        SDL_SCREEN_Y);
    statusText = malloc(10000);
#ifdef DEBUG
    status_screen = SDL_CreateWindow("Status", 0, SDL_WINDOWPOS_CENTERED,
            400, 600, SDL_WINDOW_OPENGL);

    status_renderer = SDL_CreateRenderer(status_screen, -1, SDL_RENDERER_ACCELERATED);

    status_screen_tex = SDL_CreateTexture(status_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SDL_SCREEN_X,
        SDL_SCREEN_Y);
    TTF_Init();
    terminus = TTF_OpenFont( "./fonts/TerminusTTF-4.39.ttf", 20 );

#endif // DEBUG

    size_t len = strlen(filename);

    char *newfilename = malloc(len);
    memcpy(newfilename, filename, len-3);
    newfilename[len - 3] = 0;
    filename = strcat(newfilename, "key");

    FILE * fp;
    char * line = NULL;
    ssize_t read;

    fp = fopen(newfilename, "r");
    if (fp == NULL) {
        keymappings[0x0] = SDL_SCANCODE_1;
        keymappings[0x1] = SDL_SCANCODE_2;
        keymappings[0x2] = SDL_SCANCODE_3;
        keymappings[0x3] = SDL_SCANCODE_4;
        keymappings[0x4] = SDL_SCANCODE_Q;
        keymappings[0x5] = SDL_SCANCODE_W;
        keymappings[0x5] = SDL_SCANCODE_E;
        keymappings[0x6] = SDL_SCANCODE_R;
        keymappings[0x7] = SDL_SCANCODE_A;
        keymappings[0x8] = SDL_SCANCODE_S;
        keymappings[0x9] = SDL_SCANCODE_D;
        keymappings[0xA] = SDL_SCANCODE_F;
        keymappings[0xB] = SDL_SCANCODE_Z;
        keymappings[0xC] = SDL_SCANCODE_X;
        keymappings[0xD] = SDL_SCANCODE_C;
        keymappings[0xF] = SDL_SCANCODE_V;

    }
    else {
        unsigned char keycode = 0x0;

        while ((read = getline(&line, &len, fp)) != -1) {
            line[strlen(line) - 1] = '\0';
            keymappings[keycode] = SDL_GetScancodeFromName(line);
            keycode++;
        }
    }

    return;

}

int shouldQuit = 0;

int should_quit_sdl() {
    return shouldQuit;
}

void menu_quit_sdl() {
    shouldQuit = 1;
    return;
}

void newGame() {
    shouldQuit = 0;
}

void update_keyboard_sdl(chip8_mem* mem) {

    SDL_PumpEvents();

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE]) {
        SDL_Quit();
        shouldQuit = 1;
        // menu_quit_sdl();
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

#ifdef DEBUG
    uint16_t instr = mem->main[mem->PC] << 8 | mem->main[mem->PC + 1];
    chip8_instruction* instruction = get_instruction(&instr);

    SDL_SetRenderDrawColor(status_renderer, 0, 0, 0, 255);
    SDL_RenderClear(status_renderer);
    SDL_Color textColor = {255, 255, 255};

    sprintf(statusText, "PC: 0x%x\n"
            "OPCODE: 0x%04x\n"
            "Instruction: %s\n"
            "V0: 0x%x\n"
            "V1: 0x%x\n"
            "V2: 0x%x\n"
            "V3: 0x%x\n"
            "V4: 0x%x\n"
            "V5: 0x%x\n"
            "V6: 0x%x\n"
            "V7: 0x%x\n"
            "V8: 0x%x\n"
            "V9: 0x%x\n"
            "Va: 0x%x\n"
            "Vb: 0x%x\n"
            "Vc: 0x%x\n"
            "Vd: 0x%x\n"
            "Ve: 0x%x\n"
            "Vf: 0x%x\n"
            "DT: 0x%x\n"
            "ST: 0x%x\n"
            "I: 0x%x\n",
            mem->PC,
            instr,
            instruction_names[instruction->name],
            mem->V[0x0],
            mem->V[0x1],
            mem->V[0x2],
            mem->V[0x3],
            mem->V[0x4],
            mem->V[0x5],
            mem->V[0x6],
            mem->V[0x7],
            mem->V[0x8],
            mem->V[0x9],
            mem->V[0xa],
            mem->V[0xb],
            mem->V[0xc],
            mem->V[0xd],
            mem->V[0xe],
            mem->V[0xf],
            mem->DT,
            mem->ST,
            mem->I
    );

    for (i = 0; i < mem->SP; i++) {
        sprintf(statusText, "%sS%d: 0x%04x\n", statusText, i, mem->stack[i]);
    }

    sprintf(statusText, "%sSP: 0x%x",statusText, mem->SP);
    textSurface = TTF_RenderText_Blended_Wrapped(terminus,
            statusText,
            textColor, 400);
    SDL_Rect textRect;
    SDL_GetClipRect(textSurface, &textRect);

    textTexture = SDL_CreateTextureFromSurface(status_renderer, textSurface);

    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(status_renderer, textTexture, &textRect, &textRect);
    SDL_RenderPresent(status_renderer);
    SDL_DestroyTexture(textTexture);


#endif // DEBUG
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
        SDL_Delay(MS_PER_TICK - elapsedTime);
    }
}


void cleanup_display_sdl() {
    SDL_Quit();
    return;
}
