open_project phasedetector
set_top phasedetector
add_files fir.cpp
add_files -tb out.gold.dat
add_files -tb input_i.dat
add_files -tb input_q.dat
add_files cordiccart2pol.cpp
add_files phasedetector.cpp
add_files phasedetector.h
add_files -tb phasedetector_test.cpp
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10
