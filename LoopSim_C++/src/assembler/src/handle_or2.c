/*
 * This file implements functions for
 *  - handling of instructions of type or2
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width or2 instruction type
 * opcode: opcode of instruction
 * r1: register 1
 * r2: register 2
 */
void handle_or2(op_t opcode, int r1, int r2) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_mov: // move instruction, model with or r1, r2, r2
		// opcode: or
		instr |= (0b0000) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// register a: register 2
		instr |= reg(r2) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_ld08: // load byte instruction
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: load byte
		instr |= (0b0000) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_ld16: // load halfword
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: load halfword
		instr |= (0b0001) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_ld32: // load word
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: load word
		instr |= (0b0010) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_st08: // store byte
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: store byte
		instr |= (0b1000) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_st16: // store halfword
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: store halfword
		instr |= (0b1001) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_st32: // store word
		// opcode: mem
		instr |= (0b1011) << 12;
		// mode: store word
		instr |= (0b1010) << 8;
		// register a: register 1
		instr |= reg(r1) << 4;
		// register b: register 2
		instr |= reg(r2) << 0;
		// output
		output_instr16(instr);
		break;

	case op_tst: // test and set
		// opcode: test and set instruction
		instr |= (0b1001) << 12;
		// register d: register 1
		instr |= reg(r1) << 8;
		// register a: register 2
		instr |= reg(r2) << 4;
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for ri-instruction
		yyerror("opcode not compatible with ri syntax");
		break;
	}
}
