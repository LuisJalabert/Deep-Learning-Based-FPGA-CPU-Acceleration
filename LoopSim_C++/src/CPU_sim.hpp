/*
 * CPU_sim.hpp
 *
 *  Created on: Oct 16, 2018
 *      Author: luis
 */

#ifndef CPU_SIM_HPP_
#define CPU_SIM_HPP_

#include <systemc.h>
#include <iostream>
#include <sstream>
#include "./instruction_cells.hpp"
#include "./main.hpp"

void load_prog(std::string machine_code, LT16_v0_1::LT16_memory_model *mem);

std::string decode_execute(sc_uint<16> *instr, LT16_v0_1::processor *proc);

#endif /* CPU_SIM_HPP_ */
