open_project merge_sort_restructured.proj -reset
add_file merge_sort_restructured.cpp
add_file -tb merge_sort_restructured-top.cpp
set_top merge_sort
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
