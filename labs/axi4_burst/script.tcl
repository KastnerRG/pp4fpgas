############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project axi4_sqrt
set_top axi4_sqrt
add_files axi4_sqrt.cpp
add_files axi4_sqrt.hpp
add_files -tb axi4_sqrt_test.cpp
open_solution "solution1"
set_part {xc7z020clg400-1} -tool vivado
create_clock -period 10 -name default

