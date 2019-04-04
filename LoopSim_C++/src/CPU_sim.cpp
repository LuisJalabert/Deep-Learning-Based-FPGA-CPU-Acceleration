#include "CPU_sim.hpp"


void load_prog(std::string machine_code, LT16_v0_1::LT16_memory_model *mem){
	int addr = 0;
	char delimiter = '\n';
	std::string token;
	std::istringstream tokenStream(machine_code);
	while (std::getline(tokenStream, token, delimiter)){
		#ifdef show_machine_code
		std::cout << addr << ": " << token << "\n";
		#endif
		uint ival = std::stoul(token, nullptr, 2);
		sc_uint<32> val = sc_uint<32>(ival);
		mem->set32(addr, val);
		addr += 4;
	}
}


std::string decode_execute(sc_uint<16> *instr, LT16_v0_1::processor *proc){
	sc_uint<4> 	opcode 	= instr->range(15,12);
	sc_uint<4> 	Rd 		= instr->range(11,8);
	sc_uint<4> 	Ra 		= instr->range(7,4);
	sc_uint<4> 	Rb 		= instr->range(3,0);
	sc_int<4> 	Imm4	= sc_int<4>(instr->range(3,0));
	sc_int<8> 	Imm8	= sc_int<8>(instr->range(7,0));
	sc_uint<4> 	mode	= instr->range(11,8);
	sc_uint<1> 	condit	= instr->range(8,8);
	sc_uint<32> addr	= sc_uint<32>(proc->S.REGFILE[15]);

    #ifdef output_to_csv
    // This is a template one-hot encoded vector which will contain a 1 in the position associated with the instruction:
    // (ADD,SUB,AND,OR,XOR,LSH,RSH,ADDI,CMP,LDIMM,LDPTR,STPTR,BIMM,BREG,CIMM,CREG,TRAP,RETI,BRT,TST)
    int n_instr = 20;
    std::string opcode_vector_template;
	for (int i = 0; i < n_instr; i++){
        opcode_vector_template += "0,";
	}

    // This creates a template and a filled one-hot vectors that encode the instruction mode as follows:
    // (EQU,NEQ,GR,GROREQ,LESS,LESSOREQ)
    int n_mode = 6;
    std::string mode_vector_template;
    for (int i = 0; i < n_mode; i++){
        mode_vector_template += "0,";
    }

    std::string mode_vector = mode_vector_template;
    if(mode == 0b0000)
    {
        mode_vector[0] = '1';
    }
    if(mode == 0b1000)
    {
        mode_vector[2] = '1';
    }
    if(mode == 0b0010)
    {
        mode_vector[4] = '1';
    }
    if(mode == 0b0001)
    {
        mode_vector[6] = '1';
    }
    if(mode == 0b1001)
    {
        mode_vector[8] = '1';
    }
    if(mode == 0b1010)
    {
        mode_vector[10] = '1';
    }

    // This creates a template and a filled one-hot vectors that encode the instruction condition as follows:
    // (ALWAYS,TRUE)
    int n_cond = 2;
    std::string cond_vector_template;
    for (int i = 0; i < n_cond; i++){
        cond_vector_template += "0,";
    }

    std::string cond_vector = cond_vector_template;
    if(condit == 0b0)
    {
        cond_vector[0] = '1';
    }
    if(condit == 0b1)
    {
        cond_vector[2] = '1';
    }

    // This creates a template and filled one-hot vectors with a 1 in the position corresponding to the register number:
    int n_regs = 16;
    std::string Rd_vector_template;
    std::string Ra_vector_template;
    std::string Rb_vector_template;
    for (int i = 0; i < n_regs; i++){
        Rd_vector_template += "0,";
    }
    Ra_vector_template = Rd_vector_template;
    Rb_vector_template = Rd_vector_template;

    std::string Rd_vector = Rd_vector_template;
    Rd_vector[2*int(Rd)] = '1';
    std::string Ra_vector = Ra_vector_template;
    Ra_vector[2*int(Ra)] = '1';
    std::string Rb_vector = Rb_vector_template;
    Rb_vector[2*int(Rb)] = '1';

/*


    // This creates a template and filled one-hot vectors with a 1 in the position corresponding to the immediate:
    int n_imm = 256;
    std::string Imm8_vector_template;
    for (int i = 0; i < n_imm; i++){
        Imm8_vector_template += "0,";
    }
    std::string Imm8_vector = Imm8_vector_template;
    Imm8_vector[2*uint8_t(Imm8)] = '1';		// we multiply by two because each dimension in the vector
    										// has a 0 or 1, and a comma
    std::string Imm4_vector_template = Imm8_vector_template;
    std::string Imm4_vector = Imm8_vector_template;
    Imm4_vector[2*uint8_t(Imm4)] = '1';

*/

	std::string Imm8_vector_template = "0";
	std::string Imm8_vector = std::to_string(Imm8);
	std::string Imm4_vector_template = Imm8_vector_template;
	std::string Imm4_vector = std::to_string(Imm4);
    #endif

    //branch delay slot variables:
	static 	sc_uint<32> delay_addr	= 0;

	switch(opcode) {
	    case 0b0011 : {	proc->ADD(Rd,Ra,Rb,addr);
						#ifdef show_execution
	    				std::cout << "add  r" << Rd << " r" << Ra << " r"<< Rb << "\t";
                        #endif
	    				#ifdef output_to_csv
                        opcode_vector_template[0] = '1';
                        Rd_vector_template = Rd_vector;
                        Ra_vector_template = Ra_vector;
                        Rb_vector_template = Rb_vector;
                        #endif
	    				break;
	    }
	    case 0b0001 : { proc->SUB(Rd,Rb,Ra,addr);
						#ifdef show_execution
						std::cout << "sub  r" << Rd << " r" << Ra << " r"<< Rb << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[2] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Rb_vector_template = Rb_vector;
						#endif
	    				break;
	    }
	    case 0b0010 : { proc->AND(Rd,Rb,Ra,addr);
						#ifdef show_execution
						std::cout << "and  r" << Rd << " r" << Ra << " r"<< Rb << "\t";
						#endif
						#ifdef output_to_csv
						opcode_vector_template[4] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Rb_vector_template = Rb_vector;
						#endif
	    				break;
	    }
	    case 0b0000 : { proc->OR(Rd,Rb,Ra,addr);
						#ifdef show_execution
						std::cout << "or   r" << Rd << " r" << Ra << " r"<< Rb << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[6] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Rb_vector_template = Rb_vector;
                        #endif
						break;
	    }
	    case 0b0100 : { proc->XOR(Rd, Rb, Ra, addr);
						#ifdef show_execution
						std::cout << "xor  r" << Rd << " r" << Ra << " r"<< Rb << "\t";
						#endif
						#ifdef output_to_csv
						opcode_vector_template[8] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Rb_vector_template = Rb_vector;
						#endif
						break;

		}
	    case 0b0101 : { proc->LSH(Rd, Ra, Imm4, addr);
						#ifdef show_execution
						std::cout << "lsh  r" << Rd << " r" << Ra << " imm:"<< Imm4 << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[10] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Imm8_vector_template = Imm4_vector;
						#endif
						break;
		}
	    case 0b0110 : { proc->RSH(Rd, Ra, Imm4, addr);
						#ifdef show_execution
						std::cout << "rsh  r" << Rd << " r" << Ra << " imm:"<< Imm4 << "\t";
						#endif
						#ifdef output_to_csv
						opcode_vector_template[12] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						Imm8_vector_template = Imm4_vector;
						#endif
						break;
		}
	    case 0b0111 : { proc->ADDI(Imm8, Rd, addr);
						#ifdef show_execution
						std::cout << "addi r" << Rd << " imm:"<< Imm8 << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[14] = '1';
						Rd_vector_template = Rd_vector;
						Imm8_vector_template = Imm8_vector;
                        #endif
                        break;
		}
	    case 0b1000 : { proc->CMP(mode, Rb, Ra, addr);
						#ifdef show_execution
						std::cout << "cmp  mode:" << mode << " r" << Ra << " r"<< Rb << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[16] = '1';
						Rb_vector_template = Rb_vector;
						Ra_vector_template = Ra_vector;
						mode_vector_template = mode_vector;
						#endif
						break;
		}
	    case 0b1010 : { proc->LDR(Rd, Imm8+1, addr);
						#ifdef show_execution
						std::cout << "ldr  r" << Rd << " imm:" << Imm8 << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[18] = '1';
						Rd_vector_template = Rd_vector;
						Imm8_vector_template = Imm8_vector;
						#endif
						break;
		}
	    case 0b1011 : {
			switch(mode){
				case 0b0000:{	proc->LD08(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "ld08 r" << Ra << " r"<< Rb << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[20] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
								#endif
								break;
				}
				case 0b0001:{	proc->LD16(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "ld16 r" << Ra << " r"<< Rb << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[20] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
								#endif
								break;
				}
				case 0b0010:{	proc->LD32(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "ld32 r" << Ra << " r"<< Rb << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[20] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
								#endif
								break;
				}
				case 0b1000:{	proc->ST08(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "st08 r" << Ra << " r"<< Rb << "\t";
								#endif
								#ifdef output_to_csv
								opcode_vector_template[22] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
								#endif
								break;
				}
				case 0b1001:{	proc->ST16(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "st16 r" << Ra << " r"<< Rb << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[22] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
                                #endif
								break;
				}
				case 0b1010:{	proc->ST32(Ra, Rb, addr);
								#ifdef show_execution
								std::cout << "st32 r" << Ra << " r"<< Rb << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[22] = '1';
								Ra_vector_template = Ra_vector;
								Rb_vector_template = Rb_vector;
								#endif
								break;
				}
				default: 	{
								#ifdef show_execution
								std::cout << "FATAL ERROR: Invalid instruction!";
								#endif
					break;
				}
			}
			break;
	    }
	    case 0b1100 : {
			switch(mode.range(3,1)){
				case 0b010:	{	proc->BIMM(condit, Imm8+1, addr);
								#ifdef show_execution
								std::cout << "br  imm:" << Imm8 << "\t";
								#endif
								#ifdef output_to_csv
								opcode_vector_template[24] = '1';
								cond_vector_template = cond_vector;
								Imm8_vector_template = Imm8_vector;
								#endif
								break;
				}
				case 0b011: {	proc->BREG(condit, Ra, addr);
								#ifdef show_execution
								std::cout << "br  r:" << Ra << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[26] = '1';
								Ra_vector_template = Ra_vector;
								cond_vector_template = cond_vector;
                                #endif
								break;
				}
				case 0b100: {	proc->CIMM(condit, Imm8+1, addr);
								#ifdef show_execution
								std::cout << "call imm:" << Imm8 << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[28] = '1';
								cond_vector_template = cond_vector;
								Imm8_vector_template = Imm8_vector;
                                #endif
								break;
				}
				case 0b101: {	proc->CREG(condit, Ra, addr);
								#ifdef show_execution
								std::cout << "call r" << Ra << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[30] = '1';
								Ra_vector_template = Ra_vector;
								cond_vector_template = cond_vector;
                                #endif
								break;
				}
				case 0b110: {	proc->TRAP(Imm8, addr);
								#ifdef show_execution
								std::cout << "trap imm:" << Imm8 << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[32] = '1';
								Imm8_vector_template = Imm8_vector;
                                #endif
								break;
				}
				case 0b111: {	proc->TRAP(Imm8, addr);
								#ifdef show_execution
								std::cout << "trap imm:" << Imm8 << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[32] = '1';
								Imm8_vector_template = Imm8_vector;
								#endif
								break;
				}
				case 0b000: {	proc->RETI(addr);
								#ifdef show_execution
								std::cout << "reti" << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[34] = '1';
                                #endif
								break;
				}
				case 0b001: {	proc->BRT(condit, Ra, addr);
								#ifdef show_execution
								std::cout << "brt  r" << Ra << "\t";
                                #endif
								#ifdef output_to_csv
								opcode_vector_template[36] = '1';
								Ra_vector_template = Ra_vector;
								cond_vector_template = cond_vector;
								#endif
								break;
				}
				default: 	{
								#ifdef show_execution
								std::cout << "FATAL ERROR: Invalid instruction!";
								#endif
								break;
				}
			}
			break;
		}
	    case 0b1001 : {	proc->TST(Ra, Rd, addr);
						#ifdef show_execution
						std::cout << "tst  r" << Rd << " r" << Ra << "\t";
                        #endif
						#ifdef output_to_csv
						opcode_vector_template[38] = '1';
						Rd_vector_template = Rd_vector;
						Ra_vector_template = Ra_vector;
						#endif
	    				break;
		}
		default:
            #ifdef show_execution
            std::cout << "FATAL ERROR: Invalid instruction!";
            #endif
            break;
    }

	proc->S = proc->Z;

	//deal with branch delay slot: (I assume that there cannot be a branch inside the bsd)
	if (proc->S.BDS == 1){
		proc->S.REGFILE[15] = delay_addr;
		proc->S.BDS= 0;
	} else {
		if(proc->Z.PC != sc_uint<32>(proc->Z.REGFILE[15])) {
			proc->S.BDS= 1;
			delay_addr 	= proc->Z.PC;
		}
	}

	std::string csv_file;

    #ifdef output_to_csv
	csv_file = opcode_vector_template
			 + mode_vector_template
			 + cond_vector_template
			 + Rd_vector_template
			 + Ra_vector_template
			 + Rb_vector_template.substr(0, Rb_vector_template.size()-1) + "\n";
//			 + Imm8_vector_template + ","
//			 + std::to_string(addr)
//			 + "\n";
//			 + Imm8_vector_template.substr(0, Imm8_vector_template.size()-1) + "\n"; // substr removes the last ","

//	csv_file = std::to_string(addr) + "\n";
    #endif
	return csv_file;
}
