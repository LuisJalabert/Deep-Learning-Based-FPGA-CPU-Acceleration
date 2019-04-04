// ==============================================================
// File generated on Thu Apr 04 23:06:48 CEST 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __LoopOracle_C3B4_H__
#define __LoopOracle_C3B4_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct LoopOracle_C3B4_ram : public sc_core::sc_module {

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


   SC_CTOR(LoopOracle_C3B4_ram) {
        ram[0] = "0b10111101110001101101110001011101";
        ram[1] = "0b00111110000011001100110011001101";
        ram[2] = "0b10111110101010111001001000111010";
        ram[3] = "0b10111110100010010010101000110000";
        ram[4] = "0b00111110110010111001111101010110";
        ram[5] = "0b00111101111010000111001010110000";
        ram[6] = "0b10111101101000101101000011100101";
        ram[7] = "0b00111101001000110000010101010011";


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


SC_MODULE(LoopOracle_C3B4) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 8;
static const unsigned AddressWidth = 3;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


LoopOracle_C3B4_ram* meminst;


SC_CTOR(LoopOracle_C3B4) {
meminst = new LoopOracle_C3B4_ram("LoopOracle_C3B4_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);

meminst->reset(reset);
meminst->clk(clk);
}
~LoopOracle_C3B4() {
    delete meminst;
}


};//endmodule
#endif
