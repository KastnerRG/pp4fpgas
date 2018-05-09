open_project insertion_cell_sort.proj -reset
add_file insertion_cell_sort.cpp
add_files -tb "insertion_cell_sort-top.cpp insertion_sort.cpp"
set_top insertion_cell_sort
open_solution solution -reset
set_part virtex7
create_clock -period 5
csim_design
csynth_design
