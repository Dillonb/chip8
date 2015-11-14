#include "display_tty.h"

void draw_tty(chip8_mem* mem) {
    int i, j;
    for (i = 0; i < SCREEN_X; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < SCREEN_Y; i++) {
        printf("|");
        for (j = 0; j < SCREEN_X; j++) {
            if (mem->screen[j][i]) {
                printf("█");
            }
            else {
                printf(" ");
            }
        }
        printf("|\n");
    }
    for (i = 0; i < SCREEN_X; i++) {
        printf("-");
    }
    printf("\n");
}
