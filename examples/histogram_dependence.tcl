open_project histogram_dependence.proj -reset
add_file histogram_dependence.cpp
add_file -tb histogram_dependence-top.cpp
set_top histogram
open_solution solution -reset
set_part virtex7
create_clock -period 5
config_schedule -verbose
csynth_design
cosim_design
