open_project histogram_parallel.proj -reset
add_file histogram_parallel.cpp
add_file histogram_parallel-top.cpp
set_top histogram
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
cosim_design
