#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define STACK_SIZE 16

#define SCREEN_X 64
#define SCREEN_Y 32
#define SCREEN_BITS SCREEN_X * SCREEN_Y
#define SCREEN_BYTES SCREEN_BITS / 8

typedef struct chip8_mem_t {
    /**************************
     * USER ACCESSIBLE MEMORY *
     **************************/

    // 4KB main system memory
    unsigned char main[MEMORY_SIZE];
    // Main registers: V0 - VF
    unsigned char V[NUM_REGISTERS];


    // I register
    uint16_t I;

    // Delay timer
    unsigned char DT;
    // Sound timer
    unsigned char ST;

    /*******************
     * INTERNAL MEMORY *
     *******************/

    // Program Counter
    uint16_t PC;
    // Stack Pointer
    unsigned char SP;

    // Stack
    uint16_t stack[STACK_SIZE];

    // Screen
    // Temporary screen object. Code draws on this.
    unsigned char drw_screen[SCREEN_X][SCREEN_Y];
    // Real screen object. Temp object flipped here when draw flag set.
    unsigned char screen[SCREEN_X][SCREEN_Y];
    // Draw flag (to know when to update the screen)
    int draw;

    // Keyboard (from 0x0 to 0xF)
    unsigned char keyboard[16];

} chip8_mem;

chip8_mem* get_chip8_mem();
void load_program(chip8_mem*, char*);

#endif // MEMORY_H_
