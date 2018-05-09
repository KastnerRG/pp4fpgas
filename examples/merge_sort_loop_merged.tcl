open_project merge_sort_loop_merged.proj -reset
add_file merge_sort_loop_merged.cpp
add_file -tb merge_sort_loop_merged-top.cpp
set_top merge_sort
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
