#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/luis/Desktop/Thesis/CNN_Vivado_HLS/CNN_Vivado/solution1/.autopilot/db/a.g.bc ${1+"$@"}
