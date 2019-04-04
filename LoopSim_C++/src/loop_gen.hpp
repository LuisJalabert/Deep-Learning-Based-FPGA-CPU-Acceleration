/*
 * loop_gen.hpp
 *
 *  Created on: Oct 16, 2018
 *      Author: luis
 */

#ifndef LOOP_GEN
#define LOOP_GEN

extern const int max_imm;
extern const int min_imm;

extern double fs;
extern double f0;
extern double f1;
extern double f2;
extern int amplitude0;
extern int amplitude1;
extern int amplitude2;


#include <iostream>
#include <random>
#include <initializer_list>

std::string instr_str(std::string instr, int op1, int op2, int op3, std::string mode, std::string label);

std::string loop_independent(   int loop_id,
                                const std::string& loop_type,
                                int temp_reg0, int temp_reg1, int temp_reg2, int temp_reg3,
                                int n_loops, int n_loops_reg,
                                std::vector<std::string>& arrays_base, int n_arrays, int base_reg0, int base_reg1,
                                int *fir_taps, int n_taps, int fir_temp_reg0, int fir_temp_reg1);

std::string loop_dependent(int loop_id, const std::string& loop_type, int n_loops, int n_loops_reg,
                           int temp_reg0, int temp_reg1, int temp_reg2, int temp_reg3,
                           std::vector<std::string>& arrays_base, int n_arrays,
                           int base_reg0, int base_reg1, int base_reg2,
                           int *iir_x_taps, int *iir_y_taps, int n_x_taps, int n_y_taps,
                           int iir_temp_reg0, int iir_temp_reg1
                           );

#endif /* LOOP_GEN*/
