# This makefile was tested with Vivado HLS 2019.2
# and Vitis v2024.1
# 
#

# select the HLS compiler to use (vivado_hls or vitis)
USE_VITIS=1

ifeq ($(USE_VITIS),1)
VITIS_COMPILER := $(shell dirname $(shell which vitis_hls))

VHLS = $(VITIS_COMPILER)/../../../Vitis/2024.2
HLS_COMPILER=vitis-run --mode hls --tcl 
else
VHLS := $(shell vivado_hls -r)
HLS_COMPILER=vivado_hls -f
endif

EXAMPLES = $(shell ls *-top.c)
EXAMPLES_CPP = $(shell ls *-top.cpp)
EXAMPLES_BIN = $(patsubst %.c,%,$(EXAMPLES))
EXAMPLES_BIN += $(patsubst %.cpp,%,$(EXAMPLES_CPP))
EXAMPLES_LOG = $(patsubst %.c,%.log,$(EXAMPLES))
EXAMPLES_LOG += $(patsubst %.cpp,%.log,$(EXAMPLES_CPP))

#CC = $(VHLS)/lnx64/tools/gcc/bin/gcc
#CXX = $(VHLS)/lnx64/tools/gcc/bin/g++
#CC = $(VHLS)/lnx64/tools/clang/bin/clang 
#CXX = $(VHLS)/lnx64/tools/clang/bin/clang++
CC = gcc
CXX = g++

# insert new LD path to the LD_LIBRARY_PATH if it is not already there
# 
LD_PATH_NEW = /usr/lib/x86_64-linux-gnu
LD_LIBRARY_PATH := $(shell echo $(value LD_LIBRARY_PATH) | grep -q $(LD_PATH_NEW) || echo $(LD_PATH_NEW):)$(value LD_LIBRARY_PATH)

#GEN_TCL = $(CURDIR)/../scripts/gen_hls_csynth_script.py
GEN_TCL = $(CURDIR)/../scripts/gen_hls_runner_script.py

#HLS_CONFIG_FILE = $(CURDIR)/__hls_config__.ini
HLS_CONFIG_FILE = $(CURDIR)/__hls_config__versal500__.ini

$(warning $(EXAMPLES_LOG))

INPUTFILE=test_20x20.bmp
INPUTFILE_GOLDEN_REF=test_20x20_filtered_opencv.bmp
video_simple-top.log: video_simple-top.bin
	./$< $(INPUTFILE) video_simple.bmp > $@

video_2dfilter-top.log: video_2dfilter-top.bin
	./$< $(INPUTFILE) $(INPUTFILE_GOLDEN_REF) video_2dfilter.bmp > $@	

video_2dfilter_boundary_condition-top.log: video_2dfilter_boundary_condition-top.bin
	./$< $(INPUTFILE) $(INPUTFILE_GOLDEN_REF) video_2dfilter_boundary_condition.bmp > $@	

video_2dfilter_linebuffer-top.log: video_2dfilter_linebuffer-top.bin
	./$< $(INPUTFILE) $(INPUTFILE_GOLDEN_REF) video_2dfilter_linebuffer.bmp > $@	

video_2dfilter_linebuffer_extended-top.log: video_2dfilter_linebuffer_extended-top.bin
	./$< $(INPUTFILE) $(INPUTFILE_GOLDEN_REF) video_2dfilter_linebuffer_extended.bmp > $@

video_2dfilter_linebuffer_extended_constant-top.log: video_2dfilter_linebuffer_extended_constant-top.bin
	./$< $(INPUTFILE) $(INPUTFILE_GOLDEN_REF) video_2dfilter_linebuffer_extended_constant.bmp > $@

%.o: %.c
	$(CC) -I$(VHLS)/include -c $< -o $@
%.o: %.cpp
	$(CXX) -I$(VHLS)/include -c $< -o $@

complex_fir-top.bin: complex_fir-top.o complex_fir.o fir.o
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(CXX) -I$(VHLS)/include -g -o $@ $^

%-top.bin: %-top.c %.c bitmap.c
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(CC) -I$(VHLS)/include -std=c99 $^ -g -o $@

%-top.bin: %-top.cpp %.cpp
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(CXX) -I$(VHLS)/include $? -g -o $@

insertion_cell_sort-top.bin: insertion_cell_sort-top.cpp insertion_cell_sort.cpp insertion_sort.cpp
	echo $(LD_LIBRARY_PATH)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) $(CXX) -I$(VHLS)/include $? -g -o $@

#  missing cos_table and sin_table definition. No testbench files available
#	dft.c \
#	dft_precompute.c \

CC_HLS_TARGET_FILES = \
	block_fir.c \
	fir.c \
	fir11_initial.c \
	fir_cslowed.c \
	firrolled.c \
	matrix_vector_base.c \
	matrix_vector_base_unroll_inner.c \
	matrix_vector_optimized.c \
	matrix_vector_unroll_inner2.c \
	video_2dfilter.c \
	video_2dfilter_boundary_condition.c \
	video_2dfilter_linebuffer.c \
	video_2dfilter_linebuffer_extended.c \
	video_2dfilter_linebuffer_extended_constant.c \
	video_simple.c

CXX_HLS_TARGET_FILES = \
	block_mm.cpp \
	complex_fir.cpp \
	cordic.cpp \
	cordic_fixed.cpp \
	fft_stages.cpp \
	fft_stages_loop.cpp \
	fft_sw.cpp \
	histogramSW.cpp \
	histogram_dependence.cpp \
	histogram_opt1.cpp \
	huffman_encoding.cpp \
	insertion_cell_sort.cpp \
	insertion_sort.cpp \
	insertion_sort_parallel.cpp \
	insertion_sort_relaxed.cpp \
	matrixmultiplication.cpp \
	merge_sort.cpp \
	merge_sort_loop_merged.cpp \
	merge_sort_parallel.cpp \
	merge_sort_restructured.cpp \
	prefixsumBO.cpp \
	prefixsumHW.cpp \
	prefixsumSW.cpp \
	prefixsum_optimized.cpp \
	prefixsum_unrolled.cpp \
	restructured_merge_sort.cpp \
	spmv.cpp \
	spmv_restructured.cpp \
	spmv2.cpp \
	spmv2_interleaved.cpp \
	spmv2_restructured.cpp \
	spmv_unrolled.cpp

HLS_TARGETS = $(patsubst %.c,%.comp,$(CC_HLS_TARGET_FILES))
HLS_TARGETS += $(patsubst %.cpp,%.comp,$(CXX_HLS_TARGET_FILES))

%.comp: %.tcl
#	vivado_hls -f $?
	$(HLS_COMPILER) $? || (echo "$(HLS_COMPILER) $? failed $$?"; exit 0)

%.tcl: %.c
	$(GEN_TCL) -c $(HLS_CONFIG_FILE) -i $< -o $@

%.tcl: %.cpp
	$(GEN_TCL) -c $(HLS_CONFIG_FILE) -i $< -o $@

%.log: %.bin
	-./$< > $@ || (echo "./$< > $@ failed $$?"; exit 1)


hls: $(HLS_TARGETS)

test: $(EXAMPLES_LOG)


clean:
	rm -rf *.o *.log *.bin *.tcl *.comp logs/* hls/*

.PHONY: clean hls test

# Prevent make from deleting the .bin intermediate files
.PRECIOUS: %.bin %.tcl block_fir-top.bin fir-top.bin
