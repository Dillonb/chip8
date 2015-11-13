#include <stdio.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"

int main(int argc, char** argv) {
    chip8_mem* mem = get_chip8_mem();

    int16_t instr = 0x00EE;

    printf("%d\n", get_instruction(&instr)->name);
}
