#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "system.h"
#include "cpu.h"
/*#include "display_tty.h"*/
#include "display_sdl.h"
#define TRUE 1
#define FALSE 0

int main(int argc, char** argv) {
    int choice = 0; //for switch statement below
    char* gameName; // name of the game file

    //Program now has no arguments, game file is specified later
    if (argc != 1) {
        printf("Usage: chip8 [program.ch8]\n");
        return 0;
    }

    cpu_init();

    //do/while loop for menu/game selection starts here
    do
    {

        int isValid = FALSE; //while loop for game switch statement
        newGame(); //in display_sdl added newGame to set shouldQuit to 0. 
        chip8_mem* mem = get_chip8_mem();
        cpu_init();

        while (isValid == FALSE) //loop for game menu
        {
            isValid = TRUE;
            printf("Games Menu:\n\n");
            printf("1. Tetris\n");
            printf("2. Tank\n");
            printf("3. Pong\n");
            printf("4. Space Invaders\n");
            printf("5. Connect Four\n");
            printf("6. Demo: Trip8\n");
            printf("7. Demo: Maze\n");
            printf("8. Demo: Sierpinski\n");
            printf("9. Exit\n");
            scanf("%d",&choice);
            switch (choice) 
            {

                case 1: gameName = "games/Tetris.ch8";
                    break;
                case 2: gameName = "games/Tank.ch8";
                    break;
                case 3: gameName = "games/Pong-paul.ch8";
                    break;
                case 4: gameName = "games/SpaceInvaders.ch8";
                    break;
                case 5: gameName = "games/ConnectFour.ch8";
                    break;
                case 6: gameName = "demos/Trip8Demo.ch8";
                    break;
                case 7: gameName = "demos/Maze.ch8";
                    break;
                case 8: gameName = "demos/Sierpinski.ch8";
                    break;
                case 9: printf("Goodbye\n"); 
                        menu_quit_sdl();  //menu_quit_sdl is in display_sdl and sets shouldQuit = 1
                    break;
                default: printf("Wrong Choice. Enter again\n");
                        isValid = FALSE;
            }

       }

        if (!should_quit_sdl() && choice != 9) 
        {
            load_program(mem, gameName);
            init_display_sdl(gameName);
        }

        while (!should_quit_sdl() && choice != 9) 
        {
            pre_tick_sdl();
            cpu_tick(mem);
            post_tick_sdl();
            update_keyboard_sdl(mem);
            draw_sdl(mem);
        }

        cleanup_display_sdl();

        if (choice != 9) //sets choice to undefined unless the exit option is chosen. 
        {
            choice = 0;
        }

} while (choice == 0); //repeats until user chooses exit option

}
