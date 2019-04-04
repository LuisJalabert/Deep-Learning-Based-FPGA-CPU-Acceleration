/*
 * This file implements functions for
 *  - handling of instructions of type oi
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width ori instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * imm: immediate
 */
void handle_ori(op_t opcode, int r1, int imm) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_addi: // add immediate instruction
		// opcode: add immediate instruction
		instr |= (0b0111) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// immediate: value to add
		instr |= signed8(imm) << 0;
		// output
		output_instr16(instr);
		break;

	case op_ldr: // load pc-relative instruction
		// opcode: load pc-relative instruction
		instr |= (0b1010) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// immediate: pc-offset
		instr |= signed8(imm) << 0;
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for ori-instruction
		yyerror("opcode not compatible with ori syntax");
		break;
	}
}
