/*
 * main.hpp
 *
 *  Created on: Oct 16, 2018
 *      Author: luis
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <fstream>

extern const int max_imm;
extern const int min_imm;

extern double fs;
extern double f0;
extern double f1;
extern double f2;
extern int amplitude0;
extern int amplitude1;
extern int amplitude2;

//extern std::ofstream csv_file;
//#define	show_signals


//#define show_assembly_code
//#define show_machine_code

//#define show_execution
#define output_to_csv

//#define show_r0
//#define show_r1
//#define show_r2
//#define show_r3
//#define show_r4
//#define show_r5
//#define show_r6
//#define show_r7
//#define show_r8
//#define show_r9
//#define show_r10
//#define show_r11
//#define show_r12
//#define show_r13
//#define show_r14
//#define show_r15



#endif /* MAIN_HPP_ */




//	int x_taps[] = {-7, 8,
//					-7, 9,
//					4, -7,
//					2, -4,
//					2, 4,
//					2, 4,
//					2, -4,
//					4, -7,
//					-7, 9,
//					-7, 8};
//
//	int x_iir_taps[] = {7, -10,
//						8, -10,
//						7, 10,
//						8, -10,
//						7, -10};
//
//	int y_iir_taps[] = {2, 0,
//						1, 4,
//						-1, -5,
//						2, -6,
//						-5, -7};


//
//		int x_iir_taps[] = {4, -6,
//							4, -7,
//							4, -7,
//							4, -6};
//
//		int y_iir_taps[] = {1, 0,
//							1, 2,
//							-1, -4,
//							2, -4};
//

// independent loops demos:
//	array = {"first_array", "second_array", "x_array", "y_array"};
//  std::string assembly_code = loop_independent(0, "add_constant", 0, 1, 2, 3, 16, 4, array, 2, 5, 6, x_taps, 6, 7, 8);
//	std::string assembly_code = loop_independent(1, "add_arrays", 0, 1, 2, 3, 16, 4, array, 2, 5, 6, x_taps, 6, 7, 8);
//	std::string assembly_code = loop_independent(2, "swap_arrays", 0, 1, 2, 3, 16, 4, array, 4, 5, 6, x_taps, 6, 7, 8);
//	std::string assembly_code = loop_independent(3, "fir_filter", 0, 1, 2, 3, 127, 4, array, 1, 5, 6, x_taps, 20, 7, 8);


//dependent loop demos:
//	std::string assembly_code = loop_dependent(0, "fibonacci", 24, 4, 0, 1, 2, 3, array ,1, 5, 6, 7, x_iir_taps, y_iir_taps, 2, 0, 0, 0);
//  std::string assembly_code = loop_dependent(0, "IIR_filter", 127, 4, 0, 1, 2, 3, array, 2, 5, 6, 7, x_iir_taps, y_iir_taps, 8, 8, 8, 9);
//	std::string assembly_code = loop_dependent(0, "binom_coeffs", 127, 4, 0, 1, 2, 3, array, 2, 5, 6, 7, x_iir_taps, y_iir_taps, 9, 5, 8, 9);
