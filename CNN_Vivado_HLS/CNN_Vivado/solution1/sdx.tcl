# ==============================================================
# File generated on Thu Apr 04 23:06:50 CEST 2019
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../../src/main.cpp -cflags { -Wno-unknown-pragmas}
add_files -tb ../../src/data_loader.cpp -cflags { -Wno-unknown-pragmas}
add_files src/CNNFunctions.cpp
set_part xczu3eg-sbva484-1-e
create_clock -name default -period 10
set_clock_uncertainty 12.5% default
config_compile -no_signed_zeros=0
config_compile -unsafe_math_optimizations=0
config_sdx -optimization_level=none
config_sdx -target=none
config_bind -effort=medium
config_schedule -effort=medium
config_schedule -relax_ii_for_timing=0
