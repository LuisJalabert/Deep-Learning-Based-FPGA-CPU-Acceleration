/*
 * This file implements functions for
 *  - handling of instructions of type omr
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width omr instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * r1: register 1
 */
void handle_omr(op_t opcode, opmode_t mode, int r1) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_brt: // branch to table instruction
		// opcode: branch to table
		instr |= (0b1100) << 12;
		// register a: branch target register
		instr |= reg(r1) << 4;
		// mode: branch to table (un)conditional to register
		switch (mode) {
		case mode_cond_true: // if true
			instr |= (0b0011) << 8;
			break;
		case mode_cond_unconditional: // always
			instr |= (0b0010) << 8;
			break;
		default: // invalid mode for branch to table instruction
			yyerror("mode invalid for branch to table instruction.");
		}
		// output
		output_instr16(instr);

		// fill branch delay with nop if flag is set
		if (fillbds) {
			yyverbose("filled branch delay slot with nop.");
			output_instr16(nop16);
		}
		break;

	case op_br: // branch instruction to register
		// opcode: bct
		instr |= (0b1100) << 12;
		// register a: branch target register
		instr |= reg(r1) << 4;
		// mode: branch to table (un)conditional to register
		switch (mode) {
		case mode_cond_true: // if true
			instr |= (0b0111) << 8;
			break;
		case mode_cond_unconditional: // always
			instr |= (0b0110) << 8;
			break;
		default: // invalid mode for branch instruction
			yyerror("mode invalid for branch instruction.");
		}
		// output
		output_instr16(instr);

		// fill branch delay with nop if flag is set
		if (fillbds) {
			yyverbose("filled branch delay slot with nop.");
			output_instr16(nop16);
		}
		break;

	case op_call: // call instruction to register
		// opcode: bct
		instr |= (0b1100) << 12;
		// register a: call target
		instr |= reg(r1) << 4;
		// mode: call (un)conditional to register
		switch (mode) {
		case mode_cond_true: // if true
			instr |= (0b1011) << 8;
			break;
		case mode_cond_unconditional: // always
			instr |= (0b1010) << 8;
			break;
		default: // invalid mode for call instruction
			yyerror("mode invalid for call instruction.");
		}
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for omr-instruction
		yyerror("opcode not compatible with mr syntax");
		break;
	}
}
