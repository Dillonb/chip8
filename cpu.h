#ifndef CPU_H_
#define CPU_H_
#include <stdint.h>
#include "memory.h"
#include "config.h"

// Types
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
    uint16_t filter;
    uint16_t command;
    chip8_instruction_name name;
} chip8_instruction;

// Constants
extern chip8_instruction chip8_instructions[];
extern const char* instruction_names[];

void cpu_init();
chip8_instruction* get_instruction(uint16_t* instr);
void execute_instruction(chip8_mem*, uint16_t* instr);
void cpu_tick(chip8_mem*);
uint16_t get_single_nibble(uint16_t*, int);
uint16_t get_kk(uint16_t*);
uint16_t get_byte(uint16_t*);
uint16_t get_nnn(uint16_t*);
uint16_t get_x(uint16_t*);
uint16_t get_y(uint16_t*);

#endif // CPU_H_
