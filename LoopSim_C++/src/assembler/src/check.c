/*
 * This file implements functions for
 *  - checking instruction parameters for their validity
 */
#include <stdio.h>
#include <limits.h>
#include "../inc/msg.h"
#include "../inc/global.h"

/*
 * returns a valid register number or throws error if r out of range
 * r: number of register to be checked
 */
int reg(int r) {
	if ((r >= 0) && (r <= 15)) {
		// in valid range
		return r;
	} else {
		// out of valid range
		yyerror("register number out of range");
		return 0;
	}
}

/*
 * returns a valid 8bit signed value or throws error if imm out of range
 * imm: immediate to be checked
 */
int signed8(int imm) {
	if ((imm >= -128) && (imm <= 127)) {
		// in valid range
		return imm & 0xFF;
	} else {
		// out of valid range
		yyerror(
				"immediate value out of bounds. expecting 8bit signed immediate.");
		return 0;
	}
}

/*
 * returns a valid 4bit unsigned value or throws error if imm out of range
 * imm: immediate to be checked
 */
int unsigned4(int imm) {
	if ((imm >= 0) && (imm <= 15)) {
		// in valid range
		return imm & 0x0F;
	} else {
		// out of valid range
		yyerror(
				"immediate value out of bounds. expecting 4bit unsigned immediate.");
		return 0;
	}
}

/*
 * returns a valid 32bit signed value or throws error if imm out of range
 * imm: immediate to be checked
 */
int word(int imm) {
	if ((imm >= INT_MIN) && (imm <= INT_MAX)) {
		// in valid range
		return imm;
	} else {
		// out of valid range
		yyerror(
				"immediate value out of bounds. expecting 32bit signed immediate.");
		return 0;
	}
}
