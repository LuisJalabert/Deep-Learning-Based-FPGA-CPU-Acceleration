/*
 * This file implements functions for
 *  - handling of instructions of type o
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width o instruction type
 * opcode: opcode of instruction
 */
void handle_o(op_t opcode) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_reti: // reti instruction
		// opcode: bct
		instr |= (0b1100) << 12;
		// mode: reti
		instr |= (0b0000) << 8;
		// output instruction
		output_instr16(instr);
		break;

	case op_ret: // return instruction (unconditional)
		// model with branch always to lr
		// opcode: branch
		instr |= (0b1100) << 12;
		// mode: to register
		instr |= (0b0110) << 8;
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

	case op_nop: // no operation instruction
		// model with or r0, r0, r0
		// opcode: or
		instr |= (0b0000) << 12;
		// all registers: r0
		// output instruction
		output_instr16(instr);
		break;

	case op_align: // make address be word-aligned
		if ((address % 4) != 0) {
			// not word-aligned, insert nop
			output_instr16(nop16);
		} else {
			// already word-aligned, put verbose message
			yyverbose("Already aligned, ignoring .align directive.");
		}
		break;

	default: // invalid opcode for o-instruction
		yyerror("opcode not compatible with o syntax");
		break;
	}
}
