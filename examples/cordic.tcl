############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls_cordic
set_top cordic_circ
add_files cordic.h
add_files cordic.cpp
add_files -tb out.gold.dat
add_files -tb cordic_test.cpp
open_solution "solution1"
set_part  {xc7z020clg484-1}
create_clock -period 10

source "./directives.tcl"
csynth_design
