#include <stdio.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"

int main(int argc, char** argv) {
    chip8_mem* mem = get_chip8_mem();

    load_program(mem, "Airplane.ch8");

    for (;;) {
        cpu_tick(mem);
    }
}
