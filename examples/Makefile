EXAMPLES = $(shell ls *-top.c)
EXAMPLES_CPP = $(shell ls *-top.cpp)
EXAMPLES_BIN = $(patsubst %.c,%,$(EXAMPLES))
EXAMPLES_BIN += $(patsubst %.cpp,%,$(EXAMPLES_CPP))
EXAMPLES_LOG = $(patsubst %.c,%.log,$(EXAMPLES))
EXAMPLES_LOG += $(patsubst %.cpp,%.log,$(EXAMPLES_CPP))

$(warning $(EXAMPLES_LOG))

INPUTFILE=BBC_HD_test_1920x1080.bmp
INPUTFILE=test_20x20.bmp
video_simple-top.log: video_simple-top.bin
	./$< $(INPUTFILE) video_simple.bmp > $@

video_2dfilter-top.log: video_2dfilter-top.bin
	./$< $(INPUTFILE) video_2dfilter.bmp > $@	

video_2dfilter_boundary_condition-top.log: video_2dfilter_boundary_condition-top.bin
	./$< $(INPUTFILE) video_2dfilter_boundary_condition.bmp > $@	

video_2dfilter_linebuffer-top.log: video_2dfilter_linebuffer-top.bin
	./$< $(INPUTFILE) video_2dfilter_linebuffer.bmp > $@	

video_2dfilter_linebuffer_extended-top.log: video_2dfilter_linebuffer_extended-top.bin
	./$< $(INPUTFILE) video_2dfilter_linebuffer_extended.bmp > $@

video_2dfilter_linebuffer_extended_constant-top.log: video_2dfilter_linebuffer_extended_constant-top.bin
	./$< $(INPUTFILE) video_2dfilter_linebuffer_extended_constant.bmp > $@

%-top.bin: %-top.c %.c bitmap.c
	gcc -std=c99 $? -g -o $@

%-top.bin: %-top.cpp %.cpp
	g++ $? -g -o $@

 #: %-top.bin
%.tcl:
	rm -f $@
	echo "open_project $*.proj -reset" > $@
	echo "add_file $*.c" >> $@
	echo "add_file -tb $*-top.c" >> $@
	echo "set_top $*" >> $@
	echo "open_solution solution -reset" >> $@
	echo "set_part virtex7" >> $@
	echo "create_clock -period 5" >> $@
	echo "csynth_design" >> $@

%.proj: %.tcl
	vivado_hls $?

%.log: %.bin
	./$< > $@

test: $(EXAMPLES_LOG)

