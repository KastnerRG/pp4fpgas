############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
open_project hls_ofdm_rx
set_top ofdm_receiver
add_files fft.cpp
add_files fft.h
add_files ofdm_recvr.cpp
add_files qpsk_decode.cpp
add_files -tb ofdm_test.cpp
add_files -tb out.gold.dat
add_files -tb input.dat
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10
