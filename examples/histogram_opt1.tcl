open_project histogram_opt1.proj -reset
add_file histogram_opt1.cpp
add_file -tb histogram_opt1-top.cpp
set_top histogram
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
cosim_design
