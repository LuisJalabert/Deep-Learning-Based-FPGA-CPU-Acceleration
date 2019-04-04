/*
 * This file implements functions for
 *  - handling of instructions of type omr2
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width omr2 instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 * r2: register 2
 */
void handle_omr2(op_t opcode, opmode_t mode, int r1, int r2) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_cmp: // compare instruction
		// opcode: compare
		instr |= (0b1000) << 12;
		// register a: first register
		instr |= r1 << 4;
		// register b: second register
		instr |= r2 << 0;
		// mode
		switch (mode) {
		case mode_eq: // equal
			instr |= (0b0000) << 8;
			break;
		case mode_neq: // not equal
			instr |= (0b1000) << 8;
			break;
		case mode_gg: // greater than
			instr |= (0b0010) << 8;
			break;
		case mode_ge: // greater than or equal
			instr |= (0b0001) << 8;
			break;
		case mode_ll: // less than
			instr |= (0b1001) << 8;
			break;
		case mode_le: // less than or equal
			instr |= (0b1010) << 8;
			break;
		default: // invalid mode for compare instruction
			yyerror("mode invalid for call instruction.");
			break;
		}
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for omr2-instruction
		yyerror("opcode not compatible with omr2 syntax");
		break;
	}
}
