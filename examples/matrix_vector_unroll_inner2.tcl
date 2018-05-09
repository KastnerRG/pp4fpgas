open_project matrix_vector_unroll_inner2.proj -reset
add_file matrix_vector_unroll_inner2.c
set_top matrix_vector
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
