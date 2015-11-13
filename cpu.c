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

void cpu_tick() {
    return;
}

chip8_instruction* get_instruction(int16_t* instr) {
    int i;
    for (i = 0; i < sizeof(chip8_instructions) / sizeof(chip8_instruction); i++) {
        if ((*instr & chip8_instructions[i].command) == chip8_instructions[i].command) {
            return &chip8_instructions[i];
        }
    }
    return &chip8_instructions[sizeof(chip8_instructions)/sizeof(chip8_instruction) - 1];
}
