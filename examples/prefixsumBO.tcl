open_project prefixsumBO.proj -reset
add_file prefixsumBO.cpp
set_top prefixsum
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
