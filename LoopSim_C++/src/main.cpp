#include <systemc.h>
#include <iostream>
#include <bitset>
#include <chrono>
#include <algorithm>
#include <random>

#include "./main.hpp"
#include "./instruction_cells.hpp"
#include "./loop_gen.hpp"
#include "./CPU_sim.hpp"


//global variables:
const int max_imm = 127;
const int min_imm = -128;

//LoopSim variables
const int instr_limit       = 256;
const int n_random_loops    = 100;
const int max_regs          = 12;
const int min_loops         = 4;
int max_loops               = 127;

//signal variables:
double fs 		= 1000;  		// sampling frequency fs = 1000Hz
double f0 		= 33;  			// signal base frequency f(Hz)
double f1 		= 313;  		// signal distortion frequency f(Hz)
double f2 		= 227;  		// signal distortion frequency f(Hz)
int amplitude0 	= 10000000;		// signal base amplitude
int amplitude1 	= 5000000;		// signal distortion amplitude
int amplitude2 	= 3000000;		// signal distortion amplitude


////////////////////////From assembler:////////////////////////////
extern "C"
{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <getopt.h>

	#include "./assembler/inc/msg.h"
	#include "./assembler/inc/label.h"
	#include "./assembler/inc/global.h"
	#include "./assembler/inc/output.h"
	#include "./assembler/obj/asm.tab.h"
}
// reference to linenumber supplied by flex/bison
extern int yylineno;

// reference to yyrestart function supplied by flex/bison
extern "C" void yyrestart(FILE* inputfile);

// file variable definitions and initialization
FILE* f_in;
FILE* f_out;
FILE* f_map;

#define YY_STDINIT 1;


std::string assemble(std::string *asm_code){

	const char* asm_char = asm_code->c_str();

	char* buffer = NULL;
	size_t bufferSize = 0;
	f_in = open_memstream(&buffer, &bufferSize);

	fprintf(f_in, "%s", asm_char);

	size_t size;
	char *ptr = NULL;
    f_out = open_memstream(&ptr, &size);

	// reset variables
	address = 0;
	label_listhead = 0;

	// start parsing f_in - first run
	isfirstrun = 1;
	yyrestart(f_in);
	yyparse();
	// go back to first character in input file
	fseek(f_in, 0, SEEK_SET);
	yylineno = 1;

	// start parsing f_in - second run
	address = 0;
	isfirstrun = 0;
	yyrestart(f_in);
	yyparse();

	// fill last word
	if (address % 4 == 2) {
		output_instr16(nop16);
	}
    free(buffer);
    fclose(f_out);
    fclose(f_in);

	std::string machine_code = ptr;
	return machine_code;
}
//////////////////////END From assembler://////////////////////////


SC_MODULE (LoopGen) {
        SC_CTOR (LoopGen) {
        }
};

//////////////////////
// ..::LOOP SIM::.. //
//////////////////////

int sc_main(int argc, char* argv[]) {

	//#ifdef output_to_csv
	std::ofstream csv_file;
	//#endif

	// Start measuring time:
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	// Initialize the Random Registers (rr) array
    int rr[max_regs];
    for (int reg = 0; reg<max_regs; reg++){
        rr[reg] = reg;
    }
    for (int loop_id = 0; loop_id < n_random_loops; loop_id++){

		std::random_shuffle(std::begin(rr), std::end(rr)); // randomize registers

		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni01(0,1);
		int random_target = uni01(rng);  // creates the target for the ANN: 0 means parallelizable, 1 non-parallelizable

		std::string assembly_code;

		//randomize loop type
		std::uniform_int_distribution<int> uni03(0,3);
        int loop_type_int = uni03(rng);


//		random_target = 1;
//		loop_type_int = 3;
//		std::cout << "target " + std::to_string(random_target) + "\n";
//		std::cout << "type " + std::to_string(loop_type_int) + "\n";

		int n_loops = 1;
		int n_arrays = 1;

		//initialize FIR parameters
        int fir_taps[20];
        int n_taps = 0;

		if (random_target==0) {
			std::string loop_type;
			if (loop_type_int == 0){
			    loop_type = "add_constant";
				//randomize number of loops
				max_loops = 46;
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

				//randomize number of arrays;
				int max_arrays = int(floor((max_loops+1)/(1+n_loops)));
				std::uniform_int_distribution<int> uniarrays(1, max_arrays);
				n_arrays = uniarrays(rng);
			}
			if (loop_type_int == 1) {
                loop_type = "add_arrays";

				//randomize number of loops
				max_loops = 54;
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

				//randomize number of arrays
				int max_arrays = int(floor((max_loops+1)/(1+n_loops))) + 1;
				std::uniform_int_distribution<int> uniarrays(2, max_arrays);
				n_arrays = uniarrays(rng);
			}
			if (loop_type_int == 2){
			    loop_type = "swap_arrays";

				//randomize number of loops
				max_loops = 56;
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

				//randomize number of arrays
				int max_arrays = int(floor((max_loops+1)/(1+n_loops))) + 1;
				std::uniform_int_distribution<int> uniarrays(1, max_arrays-1);
				n_arrays = uniarrays(rng);
				n_arrays = n_arrays + (n_arrays%2);
            }
			if (loop_type_int == 3){
			    loop_type = "fir_filter";

				//randomize number of loops
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

                n_arrays = 1;

                // Create filter taps randomly

                //randomize even number of taps (2 - 20):
                std::uniform_int_distribution<int> tapsdist(1,10);
                n_taps = 2*tapsdist(rng);

                //create distribution for taps between -15 and 15, excluding 0:
                std::uniform_int_distribution<int> unitaps(-15,15);
                int temp_tap;
                for (int i = 0; i < n_taps; i++){
                    temp_tap = unitaps(rng);
                    while (temp_tap == 0){      //this is not a very efficient way of excluding 0...
                        temp_tap = unitaps(rng);
                    }
                    fir_taps[i] = temp_tap;
                }
            }

			// Create the names of the arrays_base:
            std::vector<std::string> arrays_base = {};

			for (int i = 0; i< n_arrays; i++){
                arrays_base.push_back("array_" + std::to_string(loop_id) + "_arr_n" + std::to_string(i));
			}

			//Create le assembly string:
			assembly_code = loop_independent(loop_id, loop_type,
											rr[0], rr[1], rr[2], rr[3],
											n_loops, rr[4],
											arrays_base, n_arrays, rr[5], rr[6],
											fir_taps, n_taps, rr[7], rr[8]);
		}else{

            //initialize IIR parameters
            int iir_x_taps[10];
            int iir_y_taps[10];
            int n_x_taps = 0;
            int n_y_taps = 0;

			std::string loop_type;
			if (loop_type_int == 0){
			    loop_type = "fibonacci";
				//randomize number of loops
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

			    n_arrays = 1;
			}
			if (loop_type_int == 1){
			    loop_type = "dep_array_sum";

				//randomize number of loops
				max_loops = 52;
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

				//randomize number of arrays
				int max_arrays = int(floor((max_loops+1)/(1+n_loops))) + 1;
				std::uniform_int_distribution<int> uniarrays(1, max_arrays);
				n_arrays = uniarrays(rng);
			}
			if (loop_type_int == 2){
			    loop_type = "binom_coeffs";

			    //randomize n_x_taps and n_y_taps
				std::uniform_int_distribution<int> nxdist(2,max_imm);
				n_x_taps = nxdist(rng);
				std::uniform_int_distribution<int> nydist(1,n_x_taps-1);
				n_y_taps = nydist(rng);

				//randomize number of loops
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

			}
			if (loop_type_int == 3){
			    loop_type = "IIR_filter";

				//randomize number of loops
				std::uniform_int_distribution<int> uniloops(min_loops,max_loops);
				n_loops = uniloops(rng);

                n_arrays = 2;

                // Create filter taps randomly

                //randomize even number of x,y taps (2 - 10):
                std::uniform_int_distribution<int> tapsdist(2,5);
                n_x_taps = 2*tapsdist(rng);
                n_y_taps = 2*tapsdist(rng);

                //create distribution for taps between -15 and 15, excluding 0:
                std::uniform_int_distribution<int> unitaps(-15,15);
                int temp_x_tap;
                int temp_y_tap;

                //randomize x taps:
                for (int i = 0; i < n_x_taps; i++){
                    temp_x_tap = unitaps(rng);
                    while (temp_x_tap == 0){    //this is not a very efficient way of excluding 0...
                        temp_x_tap = unitaps(rng);
                    }
                    iir_x_taps[i] = temp_x_tap;
                }

                //randomize y taps:

                //first, let's randomize the positive multiplying power:
                std::uniform_int_distribution<int> pospower(0,15);
                iir_y_taps[0] = pospower(rng);
                //next, let's create the remaining taps:
                for (int i = 2; i < n_y_taps; i++){
                    temp_y_tap = unitaps(rng);
                    while (temp_y_tap == 0){        //this is not a very efficient way of excluding 0...
                        temp_y_tap = unitaps(rng);
                    }
                    iir_y_taps[i] = temp_y_tap;
				}
            }

            // Create the names of the arrays_base:
            std::vector<std::string> arrays_base = {};

            for (int i = 0; i< n_arrays; i++){
                arrays_base.push_back("array_" + std::to_string(loop_id) + "_arr_n" + std::to_string(i));
            }

			//Create le assembly string:
			assembly_code = loop_dependent( loop_id, loop_type, n_loops,
											rr[0], rr[1], rr[2], rr[3], rr[4],
											arrays_base, n_arrays, rr[5], rr[6], rr[7],
											iir_x_taps, iir_y_taps, n_x_taps, n_y_taps, rr[8], rr[9]);
		}


		#ifdef show_assembly_code
		std::cout << assembly_code;
		#endif

		std::string machine_code = assemble(&assembly_code);

		//Create CPU and memory
		LT16_v0_1::processor_state state;
		LT16_v0_1::LT16_memory_model mem;
		LT16_v0_1::processor proc(&mem);

		load_prog(machine_code, &mem);

		//Reset CPU
		state.arch_state.PC		= 0;
		state.arch_state.BDS	= 0;

		for(int i=0;i < 16; i++){
			state.arch_state.REGFILE[i]= 0;
		}
		proc.S = state.arch_state;
		proc.Z = proc.S;
		//define variables for csv output:
		std::string vectorized_code;
		int head = 0;
		int tail = 0;


		//Start the CPU:
		sc_uint<16> instr_bitcode;
		for (int i=0; i <= instr_limit; i++){
			// fetch next instruction:
			instr_bitcode =	mem.get16(proc.S.REGFILE[15]);
			// show stuff:
			#ifdef show_execution
			std::cout << "\n\nPC: " << proc.S.REGFILE[15] << ", opcode: " << std::bitset<16>(instr_bitcode) << "\n";
			#ifdef show_r0
			std::cout << " R0: " << proc.Z.REGFILE[0];
			#endif
			#ifdef show_r1
			std::cout << " R1: " << proc.Z.REGFILE[1];
			#endif
			#ifdef show_r2
			std::cout << " R2: " << proc.Z.REGFILE[2];
			#endif
			#ifdef show_r3
			std::cout << " R3: " << proc.Z.REGFILE[3];
			#endif
			#ifdef show_r4
			std::cout << " R4: " << proc.Z.REGFILE[4];
			#endif
			#ifdef show_r5
			std::cout << " R5: " << proc.Z.REGFILE[5];
			#endif
			#ifdef show_r6
			std::cout << " R6: " << proc.Z.REGFILE[6];
			#endif
			#ifdef show_r7
			std::cout << " R7: " << proc.Z.REGFILE[7];
			#endif
			#ifdef show_r8
			std::cout << " R8: " << proc.Z.REGFILE[8];
			#endif
			#ifdef show_r9
			std::cout << " R9: " << proc.Z.REGFILE[9];
			#endif
			#ifdef show_r10
			std::cout << " R10: " << proc.Z.REGFILE[10];
			#endif
			#ifdef show_r11
			std::cout << " R11: " << proc.Z.REGFILE[11];
			#endif
			#ifdef show_r12
			std::cout << " R12: " << proc.Z.REGFILE[12];
			#endif
			#ifdef show_r13
			std::cout << " R13: " << proc.Z.REGFILE[13];
			#endif
			#ifdef show_r14
			std::cout << " R14: " << proc.Z.REGFILE[14];
			#endif
			#ifdef show_r15
			std::cout << " R15: " << proc.Z.REGFILE[15];
			#endif
			std::cout << "\n";
			#endif

			// decode instruction and execute it:

			// catch dummy traps, get head or tail addres, and replace with nop
			if (instr_bitcode == 0b1100110000000000){
				head = int(proc.S.REGFILE[15]);
				instr_bitcode = 0b0000000000000000;
			}
			if (instr_bitcode == 0b1100110000000001){
				tail = int(proc.S.REGFILE[15]);
				instr_bitcode = 0b0000000000000000;
			}

			vectorized_code += decode_execute(&instr_bitcode, &proc);

		}

//		for (int i=0; i<= 200; i = i + 4){
//			int put = mem.get32(i);
//			std::cout << put  << ",\n";
//		}

		if ((random_target==1) && (loop_type_int == 2)){
			head = head-2; //fixes head for binomial recursive function, which is not even a loop...
		}

		#ifdef output_to_csv
		csv_file.open("/home/luis/Desktop/Thesis/dataset/"
					+ std::to_string(random_target)
					+ "_l_id" + std::to_string(loop_id)
					+ "_l_type" + std::to_string(loop_type_int)
					+ "_n_loops" + std::to_string(n_loops)
					+ "_n_arrays" + std::to_string(n_arrays)
					+ "_head" + std::to_string(head+2) 	//loop head is the next instruction, hence +2.
					+ "_tail" + std::to_string(tail)	//tail is technically -2, but this instruction gets executed
														//in every loop since it's in the branch delay slot.
					+ ".csv");
		csv_file << vectorized_code;
		csv_file.close();
		#endif

		#ifdef show_signals
		std::cout << "\n\nOriginal = [";
		//show mem contents:
		double normalized;
		for (int i=768; i<= 768 + 128*4; i = i + 4){
			int put = mem.get32(i);
			normalized = double(put)/amplitude0;
			std::cout << normalized << ",\n";
		}
		std::cout << "]\n";

		//for FIR:
	//    std::cout << "\n\nFiltered = [";
	//	for (int i=768; i<= 768 + 127*4; i = i + 4){
	//		int put = mem.get32(i);
	//		normalized = double(put)/amplitude0;
	//		std::cout << normalized << ",\n";
	//	}
	//	std::cout << "]";
	//	//for IIR:
		std::cout << "\n\nFiltered = [";
		for (int i=1280; i<= 1280 + 127*4; i = i + 4){
			int put = mem.get32(i);
			normalized = double(put)/amplitude0;
			std::cout << normalized << ",\n";
		}
		std::cout << "]";
		#endif

	}
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
	std::cout << "\n\nExecution Time (msec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000.0 <<std::endl;

	return(0);
}

