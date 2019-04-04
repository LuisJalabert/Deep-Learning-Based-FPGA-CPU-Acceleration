/*
 * This file implements functions for
 *  - writing to output file
 *  - writing to map file
 */

#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/global.h"

/*
 * outputs a number of length bits, given in instr to the output stream and inserts a linebreak after each 32bit
 * instr: number to be printed
 * length: number of bits to be printed
 */
void output_instr(int instr, int length) {
	// index of outputted bit
	int i;

	for (i=length-1; i>=0; i--) {
		// iterate through length bits

		if(instr & (1<<i)) {
			// if bit is 1 output '1'
			fprintf(f_out, "1");
		} else {
			// if bit is 0 output '0'
			fprintf(f_out, "0");
		}
	}
}

/*
 * outputs a number of 16bits and updates address
 * instr: number to be printed
 */
void output_instr16(int instr) {
	if ((instr & 0xFFFF) == instr) {
		// instruction fits into 16 bits
		if (!isfirstrun) {
			// in second run, output instruction
			output_instr(instr, 16);
		}

		// increment address
		address += 2;

		// add line break
		if ((!isfirstrun) && ((address % 4) == 0)) {
			// not in first run and word is filled
			fprintf(f_out, "\n");
		}

	} else {
		// instruction does not fit into 16 bit
		yyerror("internal error. 16bit instruction did not fit");
	}
}

/*
 * outputs a number of 32bits and updates address
 * instr: number to be printed
 */
void output_instr32(int instr) {
	if ((instr & 0xFFFFFFFF) == instr) {
		// instruction fits into 32bits
		if ((address % 4) != 0) {
			// address not aligned

			if (autoalign) {
				// auto-align flag set
				output_instr16(nop16);

			} else {
				// auto-align flag not set, output error
				yyerror("32bit instruction not aligned.");
				return;
			}
		}

		// increment address
		address += 4;

		if (!isfirstrun) {
			// in second run, output instruction
			output_instr(instr, 32);
			fprintf(f_out, "\n");
		}

	} else {
		// instruction does not fit into 32bits
		yyerror("internal error. 32bit instruction did not fit");
	}
}

/*
 * outputs a line to the mapfile (if specified and if in first run)
 * s: string to be put to mapfile
 */
void output_line(char* s) {
	if (isfirstrun && f_map) {
		// if in first run and mapfile is specified
		fprintf(f_map, "\t%s\n", s);
	}
}
