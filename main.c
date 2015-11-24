#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"
#include "menu.h"
/*#include "display_tty.h"*/
#include "display_sdl.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: chip8 [program.ch8]\n");
        return 0;
    }
    chip8_mem* mem = get_chip8_mem();

    get_games();

    load_program(mem, argv[1]);

    init_display_sdl();

    while (!should_quit_sdl()) {
        pre_tick_sdl();
        cpu_tick(mem);
        post_tick_sdl();
        update_keyboard_sdl(mem);
        draw_sdl(mem);
    }
    cleanup_display_sdl();
    return 0;
}
