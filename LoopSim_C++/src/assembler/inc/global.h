/*
 * This file
 *  - defines globally used constants
 *  - defines enum types
 *  - declares globally used variables
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>

// maximal filename length
#define MAX_FILENAME_LENGTH (128);
// nop instruction for 16bit
#define nop16 (0b0000000000000000)
// number of link register
#define lr_num (13)


// all supported modes
typedef enum {
	mode_eq, mode_neq, mode_ge, mode_gg, mode_le, mode_ll,

	mode_cond_true, mode_cond_unconditional
} opmode_t;

// all supported (pseudo) instructions and directives
typedef enum {
	op_add, op_sub, op_and, op_or, op_xor, op_lsh, op_rsh, op_addi,

	op_cmp, op_ssr,

	op_ldr, op_ld08, op_ld16, op_ld32, op_st08, op_st16, op_st32,

	op_brt, op_br, op_call, op_trap, op_reti,

	op_tst,

	op_mov, op_nop, op_ret, op_clr,

	op_word,  // used for direct placement of words (=32 bit)
	op_addr,  // used for setting of current address (forward movement only)
	op_align, // used for aligning next instruction/immediate value
} op_t;

// input file
extern FILE* f_in;
// output file
extern FILE* f_out;
// map file, 0 if unused
extern FILE* f_map;

// input filename
char* inputfile;

// do verbose output, boolean value
int verbose;
// automatically align 32bit instructions, boolean value
int autoalign;
// fill branch delay slot with nop, boolean value
int fillbds;
// continue even after error, boolean value
int continueonerror;

// error has happened in first run, boolean value
int errorhappened;

// buffer of the currently parsed line
char linebuf[500];

/* in first run, boolean value
 * 1 if in first run
 * 0 if in second run
 */
int isfirstrun;

// current address (byte address)
int address;

// destructor, closes programs and cleans up memory
// exitvalue: value for exit
void destruct();

#endif /* GLOBAL_H_ */
