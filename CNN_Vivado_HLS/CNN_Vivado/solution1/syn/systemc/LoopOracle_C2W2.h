// ==============================================================
// File generated on Thu Apr 04 23:06:48 CEST 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __LoopOracle_C2W2_H__
#define __LoopOracle_C2W2_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct LoopOracle_C2W2_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 32;
  static const unsigned AddressRange = 32;
  static const unsigned AddressWidth = 5;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(LoopOracle_C2W2_ram) {
        ram[0] = "0b00111110100000000010011101010010";
        ram[1] = "0b00111111000100010000011000100101";
        ram[2] = "0b00111011011010111110110111111010";
        ram[3] = "0b00111110110010111110000011011111";
        ram[4] = "0b00111101101111110001010000010010";
        ram[5] = "0b10111110010101101101010111010000";
        ram[6] = "0b10111110101101010000101100001111";
        ram[7] = "0b00111101101111001001111011101101";
        ram[8] = "0b00111101100101111100000110111110";
        ram[9] = "0b00111110010111011001011111110110";
        ram[10] = "0b10111110001100011111100010100001";
        ram[11] = "0b10111110101010100111000111011110";
        ram[12] = "0b00111111000101010110110101011101";
        ram[13] = "0b00111110101011111100010100000101";
        ram[14] = "0b10111101100011010001101101110001";
        ram[15] = "0b10111110101110111011001011111111";
        ram[16] = "0b10111110011001111010000011111001";
        ram[17] = "0b10111110100011101011111011100000";
        ram[18] = "0b10111110001010110000001000001100";
        ram[19] = "0b10111110010100000100100000010111";
        ram[20] = "0b10111110100100111011011001000110";
        ram[21] = "0b10111110000001011011110000000010";
        ram[22] = "0b10111110100111010010000111111111";
        ram[23] = "0b10111110100001110100010100111001";
        ram[24] = "0b10111110101101100001111001001111";
        ram[25] = "0b10111110001100001011111000001110";
        ram[26] = "0b10111110110001100010010011011101";
        ram[27] = "0b00111110111000110000010101010011";
        ram[28] = "0b10111111000000001111111110010111";
        ram[29] = "0b00111101100001100101100101001011";
        ram[30] = "0b00111110111010000000100111010101";
        ram[31] = "0b00111110000111000000111010111111";


SC_METHOD(prc_write_0);
  sensitive<<clk.pos();
   }


void prc_write_0()
{
    if (ce0.read() == sc_dt::Log_1) 
    {
            if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
              q0 = ram[address0.read().to_uint()];
            else
              q0 = sc_lv<DataWidth>();
    }
}


}; //endmodule


SC_MODULE(LoopOracle_C2W2) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 32;
static const unsigned AddressWidth = 5;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


LoopOracle_C2W2_ram* meminst;


SC_CTOR(LoopOracle_C2W2) {
meminst = new LoopOracle_C2W2_ram("LoopOracle_C2W2_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);

meminst->reset(reset);
meminst->clk(clk);
}
~LoopOracle_C2W2() {
    delete meminst;
}


};//endmodule
#endif
