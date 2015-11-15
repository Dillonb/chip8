#include <stdio.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"
/*#include "display_tty.h"*/
#include "display_sdl.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: chip8 [program.ch8]\n");
        return 0;
    }
    chip8_mem* mem = get_chip8_mem();

    load_program(mem, argv[1]);

    init_display_sdl();

    for (;;) {
        cpu_tick(mem);
        update_keyboard_sdl(mem);
        /*if (mem->draw) {*/
            draw_sdl(mem);
        /*}*/
    }
    cleanup_display_sdl();
    return 0;
}
