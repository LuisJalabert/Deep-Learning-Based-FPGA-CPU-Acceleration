/*
 * This file implements functions for
 *  - handling of instructions of type or2i
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width or2i instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 * r2: register 2
 * imm: immediate
 */
void handle_or2i(op_t opcode, int r1, int r2, int imm) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_lsh: // left shift instruction
		// immediate must not be 0
		if (imm == 0)
			yyerror("lsh with immediate=0 not allowed");

		// opcode: left shift instruction
		instr |= (0b0101) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// register a: register 2
		instr |= reg(r2) << 4;
		// immediate: imm-1 (+1 in processor)
		instr |= unsigned4(imm - 1) << 0;
		// output
		output_instr16(instr);
		break;

	case op_rsh: // right shift instruction
		// immediate must not be zero
		if (imm == 0)
			yyerror("rsh with immediate=0 not allowed");
		// opcode: right shift instruction
		instr |= (0b0110) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// register a: register 2
		instr |= reg(r2) << 4;
		// immediate: imm-1 (+1 in processor)
		instr |= unsigned4(imm - 1) << 0;
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for or2i-instruction
		yyerror("opcode not compatible with or2i syntax");
		break;
	}
}
