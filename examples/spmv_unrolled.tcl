open_project spmv_unrolled.proj -reset
add_file spmv_unrolled.cpp
set_top spmv
open_solution solution -reset
set_part virtex7
config_compile -unsafe_math_optimizations
create_clock -period 5
csynth_design
