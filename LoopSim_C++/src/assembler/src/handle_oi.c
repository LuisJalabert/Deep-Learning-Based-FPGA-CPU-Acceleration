/*
 * This file implements functions for
 *  - handling of instructions of type i
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/output.h"
#include "../inc/check.h"
#include "../inc/global.h"

/*
 * outputs instruction to output for instructions width oi instruction type
 * opcode: opcode of instruction
 * mode: mode of instruction
 * imm: immediate
 */
void handle_oi(op_t opcode, int imm) {

	// instruction to be build
	int instr = 0;

	switch (opcode) {
	case op_word: // add immediate word

		// immediate word
		instr = word(imm);
		// output instruction
		output_instr32(instr);
		break;

	case op_addr: // move to new address
		if (imm >= address) {
			// if new address is larger than current address
			while (imm - 2 >= address) {
				// add nop until next new address is equal to immediate value
				output_instr16(nop16);
			}
		} else {
			// new address smaller than current address
			// backward setting of address not possible
			yyerror("can't move backwards with .address");
		}
		break;

	case op_trap: // trap instruction
		// opcode: bct
		instr |= (0b1100) << 12;
		// mode: trap
		instr |= (0b1100) << 8;
		// immediate: irq number
		instr |= signed8(imm) << 0;
		// output
		output_instr16(instr);
		break;

	case op_br: // branch instruction to immediate (unconditional)
		// opcode: bct
		instr |= (0b1100) << 12;
		// immediate: branch target
		instr |= signed8(imm) << 0;
		// mode: branch and unconditional to immediate
		instr |= (0b0100) << 8;
		// output
		output_instr16(instr);

		// fill branch delay with nop if flag is set
		if (fillbds) {
			yyverbose("filled branch delay slot with nop.");
			output_instr16(nop16);
		}
		break;

	case op_call: // call instruction to immediate (unconditional)
		// opcode: bct
		instr |= (0b1100) << 12;
		// immediate: call target
		instr |= signed8(imm) << 0;
		// mode: call unconditional to immediate
		instr |= (0b1000) << 8;
		// output
		output_instr16(instr);
		break;

	default:
		// invalid opcode for oi-instruction
		yyerror("opcode not compatible with i syntax");
		break;
	}
}
