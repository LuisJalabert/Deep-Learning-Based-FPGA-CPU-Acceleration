/*
 * This file declares functions for
 *  - checking instruction parameters for their validity
 */

#ifndef CHECK_H_
#define CHECK_H_

/*
 * returns a valid register number or throws error if r out of range
 * r: number of register to be checked
 */
int reg(int r);

/*
 * returns a valid 8bit signed value or throws error if imm out of range
 * imm: immediate to be checked
 */
int signed8(int imm);

/*
 * returns a valid 4bit unsigned value or throws error if imm out of range
 * imm: immediate to be checked
 */
int unsigned4(int imm);

/*
 * returns a valid 32bit signed value or throws error if imm out of range
 * imm: immediate to be checked
 */
int word(int imm);

#endif /* CHECK_H_ */
