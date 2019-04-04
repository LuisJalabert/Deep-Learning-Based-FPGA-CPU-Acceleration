cmake_minimum_required(VERSION 3.12)
project(LoopGen)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/assembler/inc)
include_directories(src/assembler/obj)
include_directories(/usr/local/systemc-2.3.3/include)
link_directories(/usr/local/systemc-2.3.3/lib-linux64)


add_executable(systemc_test
        src/assembler/inc/check.h
        src/assembler/inc/global.h
        src/assembler/inc/handle.h
        src/assembler/inc/label.h
        src/assembler/inc/msg.h
        src/assembler/inc/output.h
        src/assembler/obj/asm.tab.c
        src/assembler/obj/asm.tab.h
        src/assembler/obj/lex.yy.c
        src/assembler/src/check.c
        src/assembler/src/handle_o.c
        src/assembler/src/handle_oi.c
        src/assembler/src/handle_om.c
        src/assembler/src/handle_omi.c
        src/assembler/src/handle_omr.c
        src/assembler/src/handle_omr2.c
        src/assembler/src/handle_or.c
        src/assembler/src/handle_or2.c
        src/assembler/src/handle_or2i.c
        src/assembler/src/handle_or3.c
        src/assembler/src/handle_ori.c
        src/assembler/src/label.c
        src/assembler/src/msg.c
        src/assembler/src/output.c
        src/CPU_sim.cpp
        src/CPU_sim.hpp
        src/instruction_cells.cpp
        src/instruction_cells.hpp
        src/loop_gen.cpp
        src/loop_gen.hpp
        src/LT16memorymodel.cpp
        src/LT16memorymodel.h
        src/main.cpp
        src/main.hpp
        src/memport.h)

FILE(GLOB R_SRC *.cpp *.hpp *.h)
target_link_libraries(systemc_test systemc)