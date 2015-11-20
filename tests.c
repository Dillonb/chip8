#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "cpu.h"
#include "memory.h"

static int setup_mem(void** state) {
    *state = get_chip8_mem();
    return 0;
}

static int teardown_mem(void** state) {
    free(*state);
    return 0;
}

static void test_CLS(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[1];
    uint16_t instr = 0x00E0;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_RET(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[0];
    uint16_t instr = 0x00EE;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_JP_addr(void** state) {
    chip8_mem* mem = *state;
    chip8_instruction* instr_obj = &chip8_instructions[2];
    uint16_t instr = 0x1abc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));

    execute_instruction(mem, &instr);

    assert_int_equal(mem->PC, 0xabc);
}

static void test_CALL_addr(void** state) {
    chip8_mem* mem = *state;
    chip8_instruction* instr_obj = &chip8_instructions[3];
    uint16_t instr = 0x2abc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    execute_instruction(mem, &instr);
    assert_int_equal(mem->PC, 0xabc);
    assert_int_equal(mem->SP, 1);
    assert_int_equal(mem->stack[0], 0x200);


    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SE_Vx_byte(void** state) {
    chip8_mem* mem = *state;
    chip8_instruction* instr_obj = &chip8_instructions[4];
    uint16_t instr = 0x3abc;
    mem->V[0xa] = 0xbc;
    chip8_instruction* selected_instruction = get_instruction(&instr);


    execute_instruction(mem, &instr);
    assert_int_equal(mem->PC, 0x204);

    mem->V[0xa] = 0xFF;
    mem->PC = 0x200;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->PC, 0x202);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SNE_Vx_byte(void** state) {
    chip8_mem* mem = *state;
    chip8_instruction* instr_obj = &chip8_instructions[5];
    uint16_t instr = 0x4abc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
    mem->V[0xa] = 0xFF;
    mem->PC = 0x200;
    execute_instruction(mem, &instr);

    assert_int_equal(mem->PC, 0x204);

    mem->V[0xa] = 0xbc;
    mem->PC = 0x200;
    execute_instruction(mem, &instr);

    assert_int_equal(mem->PC, 0x202);
}

static void test_SE_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[6];
    uint16_t instr = 0x5ab0;
    chip8_instruction* selected_instruction = get_instruction(&instr);
    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));

    chip8_mem* mem = *state;
    mem->V[0xa] = 0xFF;
    mem->V[0xb] = 0xFF;
    mem->PC = 0x200;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->PC, 0x204);
    mem->V[0xa] = 0x00;
    mem->V[0xb] = 0xFF;
    mem->PC = 0x200;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->PC, 0x202);
}

static void test_LD_Vx_byte(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[7];
    uint16_t instr = 0x6abc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));

    chip8_mem* mem = *state;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], 0xbc);
}

static void test_ADD_Vx_byte(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[8];
    uint16_t instr = 0x7abc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
    chip8_mem* mem = *state;
    mem->V[0xa] = 0x00;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], 0xbc);
    mem->V[0xa] = 0xFF;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], (unsigned char)(0xbc + 0xFF));
}

static void test_LD_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[9];
    uint16_t instr = 0x8ab0;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));

    chip8_mem* mem = *state;
    mem->V[0xb] = 0x12;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], 0x12);
}

static void test_OR_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[10];
    uint16_t instr = 0x8ab1;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));

    chip8_mem* mem = *state;
    mem->V[0xa] = 0x12;
    mem->V[0xb] = 0x21;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], 0x12 | 0x21);
}

static void test_AND_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[11];
    uint16_t instr = 0x8ab2;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
    chip8_mem* mem = *state;
    mem->V[0xa] = 0x12;
    mem->V[0xb] = 0x21;
    execute_instruction(mem, &instr);
    assert_int_equal(mem->V[0xa], 0x12 & 0x21);
}

static void test_XOR_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[12];
    uint16_t instr = 0x8ab3;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_ADD_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[13];
    uint16_t instr = 0x8ab4;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SUB_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[14];
    uint16_t instr = 0x8ab5;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SHR_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[15];
    uint16_t instr = 0x8ab6;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SUBN_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[16];
    uint16_t instr = 0x8ab7;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SHL_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[17];
    uint16_t instr = 0x8abE;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SNE_Vx_Vy(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[18];
    uint16_t instr = 0x9ab0;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_I_addr(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[19];
    uint16_t instr = 0xAabc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_JP_V0_addr(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[20];
    uint16_t instr = 0xBabc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_RND_Vx_byte(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[21];
    uint16_t instr = 0xCabc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_DRW_Vx_Vy_nibble(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[22];
    uint16_t instr = 0xDabc;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SKP_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[23];
    uint16_t instr = 0xEa9E;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_SKNP_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[24];
    uint16_t instr = 0xEaA1;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_Vx_DT(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[25];
    uint16_t instr = 0xFa07;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_Vx_K(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[26];
    uint16_t instr = 0xFa0A;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_DT_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[27];
    uint16_t instr = 0xFa15;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_ST_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[28];
    uint16_t instr = 0xFa18;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_ADD_I_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[29];
    uint16_t instr = 0xfa1E;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_F_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[30];
    uint16_t instr = 0xFa29;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_B_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[31];
    uint16_t instr = 0xFa33;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_I_Vx(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[32];
    uint16_t instr = 0xFa55;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

static void test_LD_Vx_I(void** state) {
    chip8_instruction* instr_obj = &chip8_instructions[33];
    uint16_t instr = 0xFa65;
    chip8_instruction* selected_instruction = get_instruction(&instr);

    assert_memory_equal(instr_obj, selected_instruction, sizeof(chip8_instruction));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_RET, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_CLS, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_JP_addr, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_CALL_addr, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SE_Vx_byte, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SNE_Vx_byte, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SE_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_Vx_byte, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_ADD_Vx_byte, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_OR_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_AND_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_XOR_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_ADD_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SUB_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SHR_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SUBN_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SHL_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SNE_Vx_Vy, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_I_addr, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_JP_V0_addr, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_RND_Vx_byte, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_DRW_Vx_Vy_nibble, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SKP_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_SKNP_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_Vx_DT, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_Vx_K, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_DT_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_ST_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_ADD_I_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_F_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_B_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_I_Vx, setup_mem, teardown_mem),
        cmocka_unit_test_setup_teardown(test_LD_Vx_I, setup_mem, teardown_mem),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
