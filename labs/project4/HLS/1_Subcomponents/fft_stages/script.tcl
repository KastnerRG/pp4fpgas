############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls
set_top fft_stages
add_files fft_stages.cpp
add_files fft_stages.h
add_files -tb fft_stages_test.cpp
add_files -tb out2.gold.dat
add_files -tb out3.gold.dat
add_files -tb out4.gold.dat
add_files -tb out5.gold.dat
add_files -tb out6.gold.dat
add_files -tb out7.gold.dat
add_files -tb out8.gold.dat
add_files -tb out9.gold.dat
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10

source "./directives.tcl"
##csynth_design
