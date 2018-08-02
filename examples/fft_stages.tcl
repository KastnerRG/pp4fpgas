open_project fft_stages.proj -reset
add_file fft_stages.cpp
add_file -tb fft_stages-top.cpp
set_top fft_streaming
open_solution solution -reset
set_part virtex7
create_clock -period 5
csynth_design
