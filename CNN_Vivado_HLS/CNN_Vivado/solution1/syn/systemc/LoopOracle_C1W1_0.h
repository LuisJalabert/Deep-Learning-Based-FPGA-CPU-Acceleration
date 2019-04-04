// ==============================================================
// File generated on Thu Apr 04 23:06:48 CEST 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __LoopOracle_C1W1_0_H__
#define __LoopOracle_C1W1_0_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct LoopOracle_C1W1_0_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 32;
  static const unsigned AddressRange = 8;
  static const unsigned AddressWidth = 3;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(LoopOracle_C1W1_0_ram) {
        ram[0] = "0b00111110011111110111110011101110";
        ram[1] = "0b00111111001100011111100010100001";
        ram[2] = "0b10111100000110000101111100000111";
        ram[3] = "0b10111110100010100111111011111010";
        ram[4] = "0b00111111010000111010100100101010";
        ram[5] = "0b00111111001001101100001000100111";
        ram[6] = "0b10111110001110001000011001011001";
        ram[7] = "0b00111110001101010010010101000110";


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


SC_MODULE(LoopOracle_C1W1_0) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 8;
static const unsigned AddressWidth = 3;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


LoopOracle_C1W1_0_ram* meminst;


SC_CTOR(LoopOracle_C1W1_0) {
meminst = new LoopOracle_C1W1_0_ram("LoopOracle_C1W1_0_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);

meminst->reset(reset);
meminst->clk(clk);
}
~LoopOracle_C1W1_0() {
    delete meminst;
}


};//endmodule
#endif
