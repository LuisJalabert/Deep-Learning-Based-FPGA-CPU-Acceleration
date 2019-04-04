/*
 * This file implements functions for
 *  - handling of instructions of type or
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width or instruction type
 * opcode: opcode of instruction
 * r1: register 1
 */
void handle_or(op_t opcode, int r1) {
	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_clr: // clear register, model as xor r1, r1, r1
		// opcode: cor
		instr |= (0b0100) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 1
		instr |= reg(r1) << 0;
		// output
		output_instr16(instr);
		break;
	case op_call: // call instruction to register
		// opcode: bct
		instr |= (0b1100) << 12;
		// register a: call target
		instr |= reg(r1) << 4;
		// mode: call unconditional to register
		instr |= (0b1010) << 8;
		// output
		output_instr16(instr);
		break;
	default: // invalid opcode for or-instruction
		yyerror("opcode not compatible with or syntax");
		break;
	}
}
