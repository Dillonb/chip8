#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "cpu.h"


chip8_instruction chip8_instructions[] = {
    // RET
    {
        0xFFFF,
        0x00EE,
        RET
    },
    // CLS
    {
        0xFFFF,
        0x00E0,
        CLS
    },
    // JP addr
    {
        0xF000,
        0x1000,
        JP_addr
    },
    // CALL addr
    {
        0xF000,
        0x2000,
        CALL_addr
    },
    // SE Vx, byte
    {
        0xF000,
        0x3000,
        SE_Vx_byte
    },
    // SNE Vx, byte
    {
        0xF000,
        0x4000,
        SNE_Vx_byte
    },
    // SE Vx, Vy
    {
        0xF00F,
        0x5000,
        SE_Vx_Vy
    },
    // LD Vx, byte
    {
        0xF000,
        0x6000,
        LD_Vx_byte
    },
    // ADD Vx, byte
    {
        0xF000,
        0x7000,
        ADD_Vx_byte
    },
    // LD Vx, Vy
    {
        0xF00F,
        0x8000,
        LD_Vx_Vy
    },
    // OR Vx, Vy
    {
        0xF00F,
        0x8001,
        OR_Vx_Vy
    },
    // AND Vx, Vy
    {
        0xF00F,
        0x8002,
        AND_Vx_Vy
    },
    // XOR Vx, Vy
    {
        0xF00F,
        0x8003,
        XOR_Vx_Vy
    },
    // ADD Vx, Vy
    {
        0xF00F,
        0x8004,
        ADD_Vx_Vy
    },
    // SUB Vx, Vy
    {
        0xF00F,
        0x8005,
        SUB_Vx_Vy
    },
    // SHR Vx {, Vy}
    {
        0xF00F,
        0x8006,
        SHR_Vx_Vy
    },
    // SUBN Vx, Vy
    {
        0xF00F,
        0x8007,
        SUBN_Vx_Vy
    },
    // SHL Vx {, Vy}
    {
        0xF00F,
        0x800E,
        SHL_Vx_Vy
    },
    // SNE Vx, Vy
    {
        0xF000,
        0x9000,
        SNE_Vx_Vy
    },
    // LD I, addr
    {
        0xF000,
        0xA000,
        LD_I_addr
    },
    // JP V0, addr
    {
        0xF000,
        0xB000,
        JP_V0_addr
    },
    // RND Vx, byte
    {
        0xF000,
        0xC000,
        RND_Vx_byte
    },
    // DRW Vx, Vy, nibble
    {
        0xF000,
        0xD000,
        DRW_Vx_Vy_nibble
    },
    // SKP Vx
    {
        0xF0FF,
        0xE09E,
        SKP_Vx
    },
    // SKNP Vx
    {
        0xF0FF,
        0xE0A1,
        SKNP_Vx
    },
    // LD Vx, DT
    {
        0xF00F,
        0xF007,
        LD_Vx_DT
    },
    // LD Vx, K
    {
        0xF00F,
        0xF00A,
        LD_Vx_K
    },
    // LD DT, Vx
    {
        0xF0FF,
        0xF015,
        LD_DT_Vx
    },
    // LD ST, Vx
    {
        0xF0FF,
        0xF018,
        LD_ST_Vx
    },
    // ADD I, Vx
    {
        0xF0FF,
        0xF01E,
        ADD_I_Vx
    },
    // LD F, Vx
    {
        0xF0FF,
        0xF029,
        LD_F_Vx
    },
    // LD B, Vx
    {
        0xF0FF,
        0xF033,
        LD_B_Vx
    },
    // LD [I], Vx
    {
        0xF0FF,
        0xF055,
        LD_I_Vx
    },
    // LD Vx, [I]
    {
        0xF0FF,
        0xF065,
        LD_Vx_I
    },
    {
        0x0000,
        0x0000,
        INVALID_INSTRUCTION
    }
};

const char* instruction_names[] = {
    "CLS",
    "RET",
    "JP_addr",
    "CALL_addr",
    "SE_Vx_byte",
    "SNE_Vx_byte",
    "SE_Vx_Vy",
    "LD_Vx_byte",
    "ADD_Vx_byte",
    "LD_Vx_Vy",
    "OR_Vx_Vy",
    "AND_Vx_Vy",
    "XOR_Vx_Vy",
    "ADD_Vx_Vy",
    "SUB_Vx_Vy",
    "SHR_Vx_Vy",
    "SUBN_Vx_Vy",
    "SHL_Vx_Vy",
    "SNE_Vx_Vy",
    "LD_I_addr",
    "JP_V0_addr",
    "RND_Vx_byte",
    "DRW_Vx_Vy_nibble",
    "SKP_Vx",
    "SKNP_Vx",
    "LD_Vx_DT",
    "LD_Vx_K",
    "LD_DT_Vx",
    "LD_ST_Vx",
    "ADD_I_Vx",
    "LD_F_Vx",
    "LD_B_Vx",
    "LD_I_Vx",
    "LD_Vx_I",
    "INVALID_INSTRUCTION"
};

void cpu_init() {
    srand(time(NULL));
}

void cpu_tick(chip8_mem* mem) {
    uint16_t instr = mem->main[mem->PC] << 8 | mem->main[mem->PC + 1];
    if (mem->DT > 0) {
        mem->DT--;
    }
    if (mem->ST > 0) {
        mem->ST--;
    }
    execute_instruction(mem, &instr);
    return;
}

uint16_t get_single_nibble(uint16_t* instr, int nibblenum) {
    uint16_t num = *instr;
    nibblenum = 3 - nibblenum;
    return (num >> 4*nibblenum) & 0xF;
}

uint16_t get_kk(uint16_t* instr) {
    return get_single_nibble(instr, 3) | (get_single_nibble(instr, 2) << 4);
}

uint16_t get_byte(uint16_t* instr) {
    return get_kk(instr);
}

uint16_t get_nnn(uint16_t* instr) {
    return *instr & 0x0FFF;
}

uint16_t get_addr(uint16_t* instr) {
    return get_nnn(instr);
}

uint16_t get_x(uint16_t* instr) {
    return get_single_nibble(instr, 1);
}

uint16_t get_y(uint16_t* instr) {
    return get_single_nibble(instr, 2);
}

uint16_t get_n(uint16_t* instr) {
    return get_single_nibble(instr, 3);
}

unsigned char* temp_keyboard = NULL;

int waiting_message_output = 0;

void execute_instruction(chip8_mem* mem, uint16_t* instr) {
    chip8_instruction* instruction = get_instruction(instr);

    int i, j;

#ifdef SINGLE_STEP
    getchar();
#endif // SINGLE_STEP

    mem->draw = 0;

    int temp; // Used for some instructions
    int increment_pc = 1; // Set to 0 if we shouldn't increment the PC (for jump instructions, for example)

    switch(instruction->name) {
        case CLS:
            // Clear display
            for (i = 0; i < SCREEN_X; i++) {
                for (j = 0; j < SCREEN_Y; j++) {
                    mem->drw_screen[i][j] = 0;
                }
            }
            mem->draw = 1;
            break;

        case RET:
            // Return from subroutine
            /*printf("Returning from 0x%x to 0x%x, SP=%d\n", mem->PC, mem->stack[mem->SP], mem->SP);*/
            mem->SP--;
            mem->PC = mem->stack[mem->SP];
            increment_pc = 0;
            break;

        case JP_addr:
            // Jump to address
            mem->PC = get_nnn(instr);
            increment_pc = 0;
            break;

        case CALL_addr:
            // Call subroutine at addr. Push current location to stack, set PC to addr.
            /*printf("Jumping to 0x%x from 0x%x, SP=%d\n", get_nnn(instr), mem->PC, mem->SP);*/
            mem->stack[mem->SP] = mem->PC + 0x2;
            mem->SP++;
            mem->PC = get_nnn(instr);
            increment_pc = 0;
            break;

        case SE_Vx_byte:
            // Skip next instruction if Vx == kk
            if (mem->V[get_x(instr)] == get_kk(instr)) {
                mem->PC += 2;
            }
            break;

        case SNE_Vx_byte:
            // Skip next instruction if Vx != kk
            if (mem->V[get_x(instr)] != get_kk(instr)) {
                mem->PC += 2;
            }
            break;

        case SE_Vx_Vy:
            // Skip next instruction if Vx == Vy
            if (mem->V[get_x(instr)] == mem->V[get_y(instr)]) {
                mem->PC += 2;
            }
            break;

        case LD_Vx_byte:
            // Set Vx = kk
            mem->V[get_x(instr)] = get_kk(instr);
            /*printf("Setting V%x to %x.\n", get_x(instr), get_kk(instr));*/
            break;

        case ADD_Vx_byte:
            // Vx = Vx + kk
            mem->V[get_x(instr)] += get_kk(instr);
            break;

        case LD_Vx_Vy:
            // Set Vx = Vy
            mem->V[get_x(instr)] = mem->V[get_y(instr)];
            break;

        case OR_Vx_Vy:
            // Vx = Vx OR Vy
            mem->V[get_x(instr)] |= mem->V[get_y(instr)];
            break;

        case AND_Vx_Vy:
            // Vx = Vx AND Vy
            mem->V[get_x(instr)] &= mem->V[get_y(instr)];
            break;

        case XOR_Vx_Vy:
            // Vx = Vx XOR Vy
            mem->V[get_x(instr)] ^= mem->V[get_y(instr)];
            break;

        case ADD_Vx_Vy:
            // Vx = Vx + Vy, VF = Carry
            temp = mem->V[get_x(instr)] + mem->V[get_y(instr)];
            mem->V[0xF] = (temp > 255 ? 1 : 0);
            mem->V[get_x(instr)] = (unsigned char)(temp & 0x000000FF);
            break;

        case SUB_Vx_Vy:
            // Vx = Vx - Vy, VF = 1 if Vx > Vy, otherwise 0
            mem->V[0xF] = mem->V[get_x(instr)] > mem->V[get_y(instr)] ? 1: 0;
            mem->V[get_x(instr)] -= mem->V[get_y(instr)];
            break;

        case SHR_Vx_Vy:
            // If least significant bit of Vx is 1, set VF to 1, otherwise 0. Then divide Vx by 2.
            mem->V[0xF] = mem->V[get_x(instr)] % 2;
            mem->V[get_x(instr)] /= 2;
            break;

        case SUBN_Vx_Vy:
            // If Vy > Vx, VF = 1, else VF = 0. Then Vx = Vy - Vx
            if (mem->V[get_y(instr)] > mem->V[get_x(instr)]) {
                mem->V[0xF] = 1;
            }
            else {
                mem->V[0xF] = 0;
            }
            mem->V[get_x(instr)] = mem->V[get_y(instr)] - mem->V[get_x(instr)];
            break;

        case SHL_Vx_Vy:
            // If most significant bit of Vx is 1, then VF=1, otherwise 0. Vx = Vx * 2
            mem->V[0xF] = (mem->V[get_x(instr)] >> 7) & 0x01;
            mem->V[get_x(instr)] *= 2;
            break;

        case SNE_Vx_Vy:
            // Skip next instruction if Vx != Vy
            if (mem->V[get_x(instr)] != mem->V[get_y(instr)]) {
                mem->PC += 2;
            }
            break;

        case LD_I_addr:
            // I = nnn
            mem->I = get_nnn(instr);
            break;

        case JP_V0_addr:
            // Jump to V0 + nnn
            mem->PC = mem->V[0] + get_nnn(instr);
            increment_pc = 0;
            break;

        case RND_Vx_byte:
            // Vx = (random byte) AND kk
            mem->V[get_x(instr)] = rand() & get_kk(instr);
            break;

        case DRW_Vx_Vy_nibble:
            // Display n byte sprite starting at memory location I at (Vx, Vy) set VF = collision.
            // XOR sprites onto the screen. if any pixels are erased, set VF = 1
            mem->V[0xF] = 0;
#ifdef DEBUGaaa
            printf("Drawing a %d-byte sprite onto the screen, starting at (%d, %d)\n", get_n(instr), mem->V[get_x(instr)], mem->V[get_y(instr)]);
            printf("I: 0x%x\n", mem->I);
#endif
            for (i = 0; i < get_n(instr); i++) {
                unsigned char row = mem->main[mem->I + i];
#ifdef DEBUG
                /*
                printf("Row: %x\n", row);
                */
#endif
                int j;
                for (j = 0; j < 8; j++) {
                    int xcoord = (mem->V[get_x(instr)] + j) % SCREEN_X;
                    int ycoord = mem->V[get_y(instr)] + i;
                    int px = (row >> (7 - j)) & 0x01;
                    if (px == 1 && mem->drw_screen[xcoord][ycoord] == 1) {
                        mem->V[0xF] = 1;
                    }
                    mem->drw_screen[xcoord][ycoord] ^= px;
                }
            }
#ifdef DEBUG
            /*getchar();*/
#endif
            mem->draw = 1;
            break;

        case SKP_Vx:
            // Skip next instruction if key with value of Vx is pressed.
            if (mem->keyboard[mem->V[get_x(instr)]]) {
                mem->PC += 2;
            }
            break;

        case SKNP_Vx:
            // Skip next instruction if key with value of Vx is NOT pressed.
            if (!mem->keyboard[mem->V[get_x(instr)]]) {
                mem->PC += 2;
            }
            break;

        case LD_Vx_DT:
            // Vx = Delay timer value
            mem->V[get_x(instr)] = mem->DT;
            break;

        case LD_Vx_K:
            // Wait for a key press, store the value of the key in Vx

            if (temp_keyboard == NULL) {
                temp_keyboard = malloc(sizeof(unsigned char) * 0x10);
                memcpy(temp_keyboard, &(mem->keyboard), sizeof(mem->keyboard));
            }

            int success = 0;

            if (!waiting_message_output) {
                printf("Waiting for a key press\n");
                waiting_message_output = 1;
            }

            for (i = 0; i < 0x10; i++) {
                if (!mem->keyboard[i] && temp_keyboard[i]) {
                    printf("Pressed %x\n", i);
                    mem->V[get_x(instr)] = i;
                    success = 1;
                    waiting_message_output = 0;
                    break;
                }
            }

            memcpy(temp_keyboard, &(mem->keyboard), sizeof(mem->keyboard));

            if (!success) {
                increment_pc = 0;
            }
            break;

        case LD_DT_Vx:
            // Set delay timer = Vx
            mem->DT = mem->V[get_x(instr)];
            break;

        case LD_ST_Vx:
            // Set sound timer = Vx
            mem->ST = mem->V[get_x(instr)];
            break;

        case ADD_I_Vx:
            // I = I + Vx
            mem->I += mem->V[get_x(instr)];
            break;

        case LD_F_Vx:
            // I = location of sprite for digit Vx
            // Sprites start at 0x00 and are 5 bytes long, so can just multiply Vx by 5
            mem->I = mem->V[get_x(instr)] * 0x5;
            break;

        case LD_B_Vx:
            // BCD representation of Vx in memory locations I, I+1 and I+2
            // Hundreds digit at I, tens at I+1, ones at I+2
            mem->main[mem->I]     = mem->V[get_x(instr)] / 100;
            mem->main[mem->I + 1] = (mem->V[get_x(instr)] % 100 / 10);
            mem->main[mem->I + 2] = mem->V[get_x(instr)] % 10;
            break;

        case LD_I_Vx:
            // Store registers V0 through Vx in memory starting at location I.
            for (i = 0; i <= get_x(instr); i++) {
                mem->main[mem->I + i] = mem->V[i];
            }
            break;

        case LD_Vx_I:
            // Read registers V0 through Vx from memory starting at location I.
            for (i = 0; i <= get_x(instr); i++) {
                mem->V[i] = mem->main[mem->I + i];
            }
            break;

        case INVALID_INSTRUCTION:
            printf("ERROR: hit invalid instruction at 0x%04x.\n", mem->PC);
            increment_pc = 0;
            break;
    }
    if (increment_pc) {
        mem->PC += 2;
    }
    if (mem->draw) {
        memcpy(&mem->screen, &mem->drw_screen, sizeof(mem->screen));
        mem->draw = 0;
    }
}

chip8_instruction* get_instruction(uint16_t* instr) {
    int i;
    for (i = 0; i < sizeof(chip8_instructions) / sizeof(chip8_instruction); i++) {
        if ((*instr & chip8_instructions[i].filter) == chip8_instructions[i].command) {
            return &chip8_instructions[i];
        }
    }
    return &chip8_instructions[sizeof(chip8_instructions)/sizeof(chip8_instruction) - 1];
}
