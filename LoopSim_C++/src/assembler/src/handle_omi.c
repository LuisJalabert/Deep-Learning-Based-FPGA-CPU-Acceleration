/*
 * This file implements functions for
 *  - handling of instructions of type omi
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width omi instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * imm: immediate
 */
void handle_omi(op_t opcode, opmode_t mode, int imm) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_br: // branch instruction to immediate
		// opcode: bct
		instr |= (0b1100) << 12;
		// immediate: branch target
		instr |= signed8(imm) << 0;
		// mode: branch and (un)conditional to immediate
		switch (mode) {
		case mode_cond_true: // if true
			instr |= (0b0101) << 8;
			break;
		case mode_cond_unconditional: // always
			instr |= (0b0100) << 8;
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

	case op_call: // call instruction to immediate
		// opcode: bct
		instr |= (0b1100) << 12;
		// immediate: call target
		instr |= signed8(imm) << 0;
		// mode: call (un)conditional to immediate
		switch (mode) {
		case mode_cond_true: // if true
			instr |= (0b1001) << 8;
			break;
		case mode_cond_unconditional: // always
			instr |= (0b1000) << 8;
			break;
		default: // invalid mode for branch instruction
			yyerror("mode invalid for call instruction.");
		}
		// output
		output_instr16(instr);
		break;

	default: // invalid opcode for omi-instruction
		yyerror("opcode not compatible with mi syntax");
		break;
	}
}
