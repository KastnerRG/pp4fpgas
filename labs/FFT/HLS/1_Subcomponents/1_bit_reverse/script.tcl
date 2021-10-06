############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls
set_top bit_reverse
add_files bit_reverse.cpp
add_files bit_reverse.h
add_files -tb bit_reverse_test.cpp
add_files -tb out.gold.dat
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10

source "./directives.tcl"
##csynth_design
