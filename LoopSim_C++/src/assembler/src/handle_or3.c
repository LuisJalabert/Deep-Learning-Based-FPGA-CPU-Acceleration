/*
 * This file implements functions for
 *  - handling of instructions of type or3
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width or3 instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * r2: register 2
 * r3: register 3
 */
void handle_or3(op_t opcode, int r1, int r2, int r3) {

	// instruction to be build
	int instr = 0;

	// here, scheme is simple and always the same

	// register d: register 1
	instr |= r1 << 8;
	// register a: register 2
	instr |= r2 << 4;
	// register b: register 3
	instr |= r3 << 0;

	// opcode
	switch (opcode) {
	case op_add: // add instruction
		// opcode
		instr |= (0b0011) << 12;
		// output
		output_instr16(instr);
		break;

	case op_sub: // subtract instruction
		// opcode
		instr |= (0b0001) << 12;
		// output
		output_instr16(instr);
		break;

	case op_and: // bitwise and instruction
		// opcode
		instr |= (0b0010) << 12;
		// output
		output_instr16(instr);
		break;

	case op_or: // bitwise or instruction
		// opcode
		instr |= (0b0000) << 12;
		// output
		output_instr16(instr);
		break;

	case op_xor: // bitwise xor instruction
		// opcode
		instr |= (0b0100) << 12;
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for or3-instruction
		yyerror("opcode not compatible with or3 syntax");
		break;
	}
}
