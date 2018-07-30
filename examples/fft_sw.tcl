
open_project fft_sw.proj -reset
add_file fft_sw.c
add_file -tb fft_sw-top.c

set_top fft_sw

open_solution solution -reset

set_part xc7k70tfbg676-1

create_clock -period 5

csynth_design
cosim_design
