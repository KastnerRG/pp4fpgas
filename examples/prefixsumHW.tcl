open_project prefixsumHW.proj -reset
add_file prefixsumHW.cpp
set_top prefixsum
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
