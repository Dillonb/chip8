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
    char main[MEMORY_SIZE];
    // Main registers: V0 - VF
    char V[NUM_REGISTERS];


    // I register
    int16_t I;

    // Delay timer
    uint32_t DT;
    // Sound timer
    uint32_t ST;

    /*******************
     * INTERNAL MEMORY *
     *******************/

    // Program Counter
    uint16_t PC;
    // Stack Pointer
    uint16_t SP;

    // Stack
    int16_t stack[STACK_SIZE];


} chip8_mem;

chip8_mem* get_chip8_mem();
void load_program(chip8_mem*, char*);

#endif // MEMORY_H_
