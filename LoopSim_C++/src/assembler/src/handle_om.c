/*
 * This file implements functions for
 *  - handling of instructions of type om
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width om instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 */
void handle_om(op_t opcode, opmode_t mode) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {

	case op_ret: // return instruction
		// model with branch to lr
		// opcode: branch
		instr |= (0b1100) << 12;
		// mode: to register and condition
		switch (mode) {
			case mode_cond_true: // if true
				instr |= (0b0111) << 8;
				break;
			case mode_cond_unconditional: // always
				instr |= (0b0110) << 8;
				break;
			default: // invalid mode for branch instruction
				yyerror("mode invalid for ret instruction.");
		}
		// register a: LR
		instr |= lr_num << 4;
		// output instruction
		output_instr16(instr);

		// fill branch delay with nop if flag is set
		if (fillbds) {
			yyverbose("filled branch delay slot with nop.");
			output_instr16(nop16);
		}
		break;

	default: // invalid opcode for o-instruction
		yyerror("opcode not compatible with om syntax");
		break;
	}
}
