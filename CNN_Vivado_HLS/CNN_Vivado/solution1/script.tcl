############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project CNN_Vivado
set_top LoopOracle
add_files src/CNNFunctions.cpp
add_files -tb src/data_loader.cpp
add_files -tb src/main.cpp
open_solution "solution1"
set_part {xczu3eg-sbva484-1-e}
create_clock -period 10 -name default
config_compile  
#source "./CNN_Vivado/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
