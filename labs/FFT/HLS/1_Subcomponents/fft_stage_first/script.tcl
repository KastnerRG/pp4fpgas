############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls
set_top fft_stage_first
add_files fft_stage_first.cpp
add_files fft_stage_first.h
add_files -tb fft_stage_first_test.cpp
add_files -tb out.gold.dat
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10

source "./directives.tcl"
##csynth_design
