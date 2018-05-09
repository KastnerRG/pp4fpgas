open_project matrixmultiplication.proj -reset
add_file matrixmultiplication.cpp
set_top matrixmul
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
