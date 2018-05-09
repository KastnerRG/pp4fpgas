
open_project fir.proj -reset
add_file fir.c
add_file -tb fir-top.c

set_top fir

open_solution solution -reset

set_part xc7k70tfbg676-1

create_clock -period 5

elaborate
autosyn
#automg -export

