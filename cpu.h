#ifndef CPU_H_
#define CPU_H_
#include <stdint.h>

typedef enum chip8_instruction_name_t {
    CLS,
    RET,
    JP_addr,
    CALL_addr,
    SE_Vx_byte,
    SNE_Vx_byte,
    SE_Vx_Vy,
    LD_Vx_byte,
    ADD_Vx_byte,
    LD_Vx_Vy,
    OR_Vx_Vy,
    AND_Vx_Vy,
    XOR_Vx_Vy,
    ADD_Vx_Vy,
    SUB_Vx_Vy,
    SHR_Vx_Vy,
    SUBN_Vx_Vy,
    SHL_Vx_Vy,
    SNE_Vx_Vy,
    LD_I_addr,
    JP_V0_addr,
    RND_Vx_byte,
    DRW_Vx_Vy_nibble,
    SKP_Vx,
    SKNP_Vx,
    LD_Vx_DT,
    LD_Vx_K,
    LD_DT_Vx,
    LD_ST_Vx,
    ADD_I_Vx,
    LD_F_Vx,
    LD_B_Vx,
    LD_I_Vx,
    LD_Vx_I,


    INVALID_INSTRUCTION,
} chip8_instruction_name;

typedef struct chip8_instruction_t {
    int16_t command;
    chip8_instruction_name name;
} chip8_instruction;


chip8_instruction* get_instruction(int16_t* instr);
void cpu_tick();

#endif // CPU_H_
