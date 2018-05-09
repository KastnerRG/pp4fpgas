open_project insertion_sort.proj -reset
add_file insertion_sort.cpp
add_file -tb insertion_sort-top.cpp
set_top insertion_sort
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
