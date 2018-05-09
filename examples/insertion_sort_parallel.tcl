open_project insertion_sort_parallel.proj -reset
add_file insertion_sort_parallel.cpp
add_file -tb insertion_sort_parallel-top.cpp
set_top insertion_sort_parallel
open_solution solution -reset
set_part virtex7
config_schedule -verbose
create_clock -period 5
csynth_design
