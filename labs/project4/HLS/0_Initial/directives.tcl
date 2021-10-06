############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2012 Xilinx Inc. All rights reserved.
############################################################
set_directive_loop_tripcount -min 1024 -max 1024 -avg 1024 "fft/bit_reverse0"
set_directive_loop_tripcount -min 10 -max 10 -avg 10 "fft/bit_reverse1"
set_directive_loop_tripcount -min 2 -max 1024 "fft/butterfly"
set_directive_loop_tripcount -min 2 -max 1024 "fft/DFTpts"
