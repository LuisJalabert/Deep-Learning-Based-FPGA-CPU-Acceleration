/*
 * This file declares functions for
 *  - writing to output file
 *  - writing to map file
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

/*
 * outputs a number of length bits, given in instr to the output stream and inserts a linebreak after each 32bit
 * instr: number to be printed
 * length: number of bits to be printed
 */
void output_instr(int instr, int length);

/*
 * outputs a number of 16bits and updates address
 * instr: number to be printed
 */
void output_instr16(int instr);

/*
 * outputs a number of 32bits and updates address
 * instr: number to be printed
 */
void output_instr32(int instr);

/*
 * outputs a line to the mapfile (if specified and if in first run)
 * s: string to be put to mapfile
 */
void output_line(char* s);


#endif /* OUTPUT_H_ */
