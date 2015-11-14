#include <stdio.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"
#include "display_tty.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: chip8 [program.ch8]\n");
        return 0;
    }
    chip8_mem* mem = get_chip8_mem();

    load_program(mem, argv[1]);

    for (;;) {
        cpu_tick(mem);
        draw_tty(mem);
    }

    return 0;
}
