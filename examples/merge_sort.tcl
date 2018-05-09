open_project merge_sort.proj -reset
add_file merge_sort.cpp
add_file -tb merge_sort-top.cpp
set_top merge_sort
open_solution solution -reset
set_part virtex7
create_clock -period 5
config_schedule -verbose
csynth_design
