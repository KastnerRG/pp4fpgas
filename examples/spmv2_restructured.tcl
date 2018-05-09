open_project spmv2_restructured.proj -reset
add_file spmv2_restructured.cpp
add_file -tb spmv2_restructured-top.cpp
set_top spmv
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
cosim_design
