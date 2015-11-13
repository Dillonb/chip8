#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

chip8_instruction chip8_instructions[] = {
    // RET
    {
        0x00EE,
        RET
    },
    // CLS
    {
        0x00E0,
        CLS
    },
    // JP addr
    {
        0x1000,
        JP_addr
    },
    // CALL addr
    {
        0x2000,
        CALL_addr
    },
    // SE Vx, byte
    {
        0x3000,
        SE_Vx_byte
    },
    // SNE Vx, byte
    {
        0x4000,
        SNE_Vx_byte
    },
    // SE Vx, Vy
    {
        0x5000,
        SE_Vx_Vy
    },
    // LD Vx, byte
    {
        0x6000,
        LD_Vx_byte
    },
    // ADD Vx, byte
    {
        0x7000,
        ADD_Vx_byte
    },
    // LD Vx, Vy
    {
        0x8000,
        LD_Vx_Vy
    },
    // OR Vx, Vy
    {
        0x8001,
        OR_Vx_Vy
    },
    // AND Vx, Vy
    {
        0x8002,
        AND_Vx_Vy
    },
    // XOR Vx, Vy
    {
        0x8003,
        XOR_Vx_Vy
    },
    // ADD Vx, Vy
    {
        0x8004,
        ADD_Vx_Vy
    },
    // SUB Vx, Vy
    {
        0x8005,
        SUB_Vx_Vy
    },
    // SHR Vx {, Vy}
    {
        0x8006,
        SHR_Vx_Vy
    },
    // SUBN Vx, Vy
    {
        0x8007,
        SUBN_Vx_Vy
    },
    // SHL Vx {, Vy}
    {
        0x800E,
        SHL_Vx_Vy
    },
    // SNE Vx, Vy
    {
        0x9000,
        SNE_Vx_Vy
    },
    // LD I, addr
    {
        0xA000,
        LD_I_addr
    },
    // JP V0, addr
    {
        0xB000,
        JP_V0_addr
    },
    // RND Vx, byte
    {
        0xC000,
        RND_Vx_byte
    },
    // DRW Vx, Vy, nibble
    {
        0xD000,
        DRW_Vx_Vy_nibble
    },
    // SKP Vx
    {
        0xE09E,
        SKP_Vx
    },
    // SKNP Vx
    {
        0xE0A1,
        SKNP_Vx
    },
    // LD Vx, DT
    {
        0xF007,
        LD_Vx_DT
    },
    // LD Vx, K
    {
        0xF00A,
        LD_Vx_K
    },
    // LD DT, Vx
    {
        0xF018,
        LD_DT_Vx
    },
    // LD ST, Vx
    {
        0xF018,
        LD_ST_Vx
    },
    // ADD I, Vx
    {
        0xF01E,
        ADD_I_Vx
    },
    // LD F, Vx
    {
        0xF029,
        LD_F_Vx
    },
    // LD B, Vx
    {
        0xF033,
        LD_B_Vx
    },
    // LD [I], Vx
    {
        0xF055,
        LD_I_Vx
    },
    // LD Vx, [I]
    {
        0xF065,
        LD_Vx_I
    },
    {
        0x0000,
        INVALID_INSTRUCTION
    }
};

void cpu_tick(chip8_mem* mem) {
    uint16_t instr = mem->main[mem->PC] << 8 | mem->main[mem->PC + 1];
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
uint16_t get_nnn(uint16_t* instr) {
    return get_kk(instr) | (get_single_nibble(instr, 1) << 8);
}

void execute_instruction(chip8_mem* mem, uint16_t* instr) {
    chip8_instruction* instruction = get_instruction(instr);

    printf("PC: %04x\n", mem->PC);
    printf("Instruction: %04x \n", *instr);
    printf("Instruction name index: %d\n", instruction->command);
    int i = 0;
    for (i = 0; i < 4; i++) {
        printf("Nibble #%d - %01x\n", i, get_single_nibble(instr, i));
    }
    printf("nnn: %03x\n", get_nnn(instr));
    mem->PC += 2;
    return;

    switch(instruction->name) {
        case CLS:
            // Clear display
            // TODO
            break;
        case RET:
            // Return from subroutine
            // TODO
            break;
        case JP_addr:
            // Jump to address
            mem->PC = get_nnn(instr);
            break;
        case CALL_addr:
            // Call subroutine at addr. Push current location to stack, set PC to addr.
            // TODO
            break;
        case SE_Vx_byte:
            // Skip next instruction if Vx == kk
            // TODO
            break;
        case SNE_Vx_byte:
            // Skip next instruction if Vx != kk
            // TODO
            break;
        case SE_Vx_Vy:
            // Skip next instruction if Vx == Vy
            // TODO
            break;
        case LD_Vx_byte:
            // Set Vx = kk
            // TODO
            break;
        case ADD_Vx_byte:
            // Vx = Vx + kk
            // TODO
            break;
        case LD_Vx_Vy:
            // Set Vx = Vy
            // TODO
            break;
        case OR_Vx_Vy:
            // Vx = Vx OR Vy
            // TODO
            break;
        case AND_Vx_Vy:
            // Vx = Vx AND Vy
            // TODO
            break;
        case XOR_Vx_Vy:
            // Vx = Vx XOR Vy
            // TODO
            break;
        case ADD_Vx_Vy:
            // Vx = Vx + Vy, VF = Carry
            // TODO
            break;
        case SUB_Vx_Vy:
            // Vx = Vx - Vy, VF = 1 if Vx > Vy, otherwise 0
            // TODO
            break;
        case SHR_Vx_Vy:
            // If least significant bit of Vx is 1, set VF to 1, otherwise 0. Then divide Vx by 2.
            // TODO
            break;
        case SUBN_Vx_Vy:
            // If Vy > Vx, VF = 1, else VF = 0. Then Vx = Vy - Vx
            // TODO
            break;
        case SHL_Vx_Vy:
            // If most significant bit of Vx is 1, then VF=1, otherwise 0. Vx = Vx * 2
            // TODO
            break;
        case SNE_Vx_Vy:
            // Skip next instruction if Vx != Vy
            // TODO
            break;
        case LD_I_addr:
            // I = nnn
            // TODO
            break;
        case JP_V0_addr:
            // Jump to V0 + nnn
            // TODO
            break;
        case RND_Vx_byte:
            // Vx = (random byte) AND kk
            // TODO
            break;
        case DRW_Vx_Vy_nibble:
            // Display n byte sprite starting at memory location I at (Vx, Vt) set VF = collision.
            // XOR sprites onto the screen. if any pixels are erased, set VF = 1
            // TODO
            break;
        case SKP_Vx:
            // Skip next instruction if key with value of Vx is pressed.
            // TODO
            break;
        case SKNP_Vx:
            // Skip next instruction if key with value of Vx is NOT pressed.
            // TODO
            break;
        case LD_Vx_DT:
            // Vx = Detay timer value
            // TODO
            break;
        case LD_Vx_K:
            // Wait for a key press, store the value of the key in Vx
            // TODO
            break;
        case LD_DT_Vx:
            // Set delay timer = Vx
            // TODO
            break;
        case LD_ST_Vx:
            // Set sound timer = Vx
            // TODO
            break;
        case ADD_I_Vx:
            // I = I + Vx
            // TODO
            break;
        case LD_F_Vx:
            // I = location of sprite for digit Vx
            // TODO
            break;
        case LD_B_Vx:
            // BCD representation of Vx in memory locations I, I+1 and I+2
            // Value of I is set to the location for the hexidecimal sprite corresponding to the value of Vx.
            // TODO
            break;
        case LD_I_Vx:
            // Store registers V0 through Vx in memory starting at location I.
            // TODO
            break;
        case LD_Vx_I:
            // Read registers V0 through Vx from memory starting at location I.
            // TODO
            break;
        case INVALID_INSTRUCTION:
            printf("WARNING: hit invalid instruction at 0x%04F. Skipping.\n", mem->PC);
            mem->PC += 2; // Just skip it.
            break;
    }
}

chip8_instruction* get_instruction(uint16_t* instr) {
    int i;
    for (i = 0; i < sizeof(chip8_instructions) / sizeof(chip8_instruction); i++) {
        if ((*instr & chip8_instructions[i].command) == chip8_instructions[i].command) {
            return &chip8_instructions[i];
        }
    }
    return &chip8_instructions[sizeof(chip8_instructions)/sizeof(chip8_instruction) - 1];
}
