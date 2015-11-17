#include <stdio.h>
#include <string.h>
#include "memory.h"

#define MAX_PROGRAM_SIZE 3583

chip8_mem* get_chip8_mem() {
    chip8_mem* mem = malloc(sizeof(chip8_mem));
    int i, j;

    // Initialize memory
    // Main memory to zero
    for (i = 0; i < MEMORY_SIZE; i++) {
        mem->main[i] = 0x0;
    }

    char default_mem[] = {
        // Characters 0-F sprites
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    memcpy(&(mem->main), &default_mem, sizeof(default_mem));


    mem->I = 0;


    // V registers to 0
    for (i = 0; i < NUM_REGISTERS; i++) {
        mem->V[i] = 0x0;
    }

    // Timers
    mem->DT = 0;
    mem->ST = 0;

    // System registers
    mem->PC = 0x200;
    mem->SP = 0;

    //Stack
    for (i = 0; i < STACK_SIZE; i++) {
        mem->stack[i] = 0x00;
    }

    // Screen
    for (i = 0; i < SCREEN_X; i++) {
        for (j = 0; j < SCREEN_Y; j++) {
            mem->screen[i][j] = 0x00;
            mem->drw_screen[i][j] = 0x00;
        }
    }

    // Keyboard
    for (i = 0; i < 0x10; i++) {
        mem->keyboard[i] = 0x00;
    }

    return mem;
}

void load_program(chip8_mem* mem, char* filename) {
    FILE* file_ptr;
    file_ptr = fopen(filename, "rb");
    if (!file_ptr) {
        printf("Failed to load program.\n");
        return;
    }
    fread(&(mem->main[0x200]), 1, MAX_PROGRAM_SIZE, file_ptr);
}
