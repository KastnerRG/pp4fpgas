open_project baseline
set_top fir
add_files fir.cpp
add_files fir.h
add_files -tb fir_test.cpp
add_files -tb out.gold.dat
add_files -tb input_i.dat
add_files -tb input_q.dat
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10
