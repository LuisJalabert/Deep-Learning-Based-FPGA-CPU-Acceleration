/*
 * This file declares functions for
 *  - handling of instructions
 */

#ifndef HANDLE_H_
#define HANDLE_H_

#include "global.h"

/*
 * outputs instruction to output for instructions width or3 instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * r2: register 2
 * r3: register 3
 */
void handle_or3(op_t opcode, int r1, int r2, int r3);

/*
 * outputs instruction to output for instructions width ori instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * imm: immediate
 */
void handle_ori(op_t opcode, int r1, int imm);

/*
 * outputs instruction to output for instructions width omr2 instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 * r2: register 2
 */
void handle_omr2(op_t opcode, opmode_t mode, int r1, int r2);

/*
 * outputs instruction to output for instructions width omi instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * imm: immediate
 */
void handle_omi(op_t opcode, opmode_t mode, int imm);

/*
 * outputs instruction to output for instructions width omr instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 */
void handle_omr(op_t opcode, opmode_t mode, int r1);

/*
 * outputs instruction to output for instructions width oi instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * imm: immediate
 */
void handle_oi(op_t opcode, int imm);

/*
 * outputs instruction to output for instructions width o instruction type
 * opcode: opcode of instruction
 */
void handle_o(op_t opcode);

/*
 * outputs instruction to output for instructions width or instruction type
 * opcode: opcode of instruction
 * r1: register 1
 */
void handle_or(op_t opcode, int r1);

/*
 * outputs instruction to output for instructions width or2 instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * r2: register 2
 */
void handle_or2(op_t opcode, int r1, int r2);

/*
 * outputs instruction to output for instructions width or2i instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 * r2: register 2
 * imm: immediate
 */
void handle_or2i(op_t opcode, int r1, int r2, int imm);

/*
 * outputs instruction to output for instructions width om instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 */
void handle_om(op_t opcode, opmode_t mode);

#endif /* HANDLE_H_ */
