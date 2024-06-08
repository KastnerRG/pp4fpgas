"""
This module contains unit tests for the functions in the gen_hls_component_compile_report module.

The gen_hls_component_compile_report module provides functions for reading input files, parsing YAML configuration files,
and splitting input file strings into sections.

The unit tests in this module verify the correctness of these functions by creating temporary files, writing data to them,
and then using the functions to read and process the data.

"""

import os
import tempfile
import logging
import pytest
import yaml

from gen_hls_component_log_data import *

# get script directory
script_dir = os.path.dirname(os.path.realpath(__file__))

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

# get script directory
script_dir = os.path.dirname(os.path.realpath(__file__))


def test_read_input_file():
    """
    Test case for the read_input_file function.

    This test case creates a temporary file, writes some data to it, and then uses the
    read_input_file function to read the data from the file.
    It checks that the data read from the file is correct.

    """
    # Create a temporary file and write some data to it
    with tempfile.NamedTemporaryFile(delete=False, mode="w", encoding="utf-8") as f:
        f.write("Test data")
        temp_file_name = f.name

    # Use the function to read the data from the file
    data = read_input_file(temp_file_name)

    # Check that the data is correct
    assert data == "Test data"


def test_read_yaml_config():
    """
    Test case for the read_yaml_config function.

    This test case creates a temporary file, writes some data to it using the yaml.dump function,
    and then uses the read_yaml_config function to read the data from the file. It checks that
    the data read from the file is correct.

    Returns:
        None
    """
    # Create a temporary file and write some data to it
    with tempfile.NamedTemporaryFile(delete=False, mode="w", encoding="utf-8") as f:
        yaml.dump({"key": "value"}, f)
        temp_file_name = f.name

    # Use the function to read the data from the file
    data = read_yaml_config(temp_file_name)

    # Check that the data is correct
    assert data == {"key": "value"}


def test_get_hls_compiler_type():
    """
    Test function for the get_hls_compiler_type function.

    This function tests the get_hls_compiler_type function by providing different input data and
    checking if the returned result matches the expected output.

    """

    # Define the input data and the expected output
    input_data = "vivado_hls"
    yaml_data = {
        "hls_compiler_type": {
            "vivado_hls": {"pattern": "vivado_hls"},
            "vitis_hls": {"pattern": "vitis_hls"},
        }
    }
    expected_output = "vivado_hls"

    # Call the function with the input data
    result = get_hls_compiler_type(input_data, yaml_data)

    # Assert that the result is as expected
    assert result == expected_output

    input_data = "vitis_hls"

    expected_output = "vitis_hls"

    # Call the function with the input data
    result = get_hls_compiler_type(input_data, yaml_data)

    # Assert that the result is as expected
    assert result == expected_output


def test_split_input_file_string_into_sections():
    # Create a string that simulates the input data
    input_data = """
Makefile:35: block_fir-top.log fir-top.log matrix_vector_base-top.log matrix_vector_optimized-top.log matrix_vector_unroll_inner2-top.log video_2dfilter_boundary_condition-top.log video_2dfilter_linebuffer_extended_constant-top.log video_2dfilter_linebuffer_extended-top.log video_2dfilter_linebuffer-top.log video_2dfilter-top.log video_simple-top.log cordic_fixed-top.log cordic-top.log fft_stages_loop-top.log fft_stages-top.log fft_sw-top.log histogram_dependence-top.log histogram_opt1-top.log histogram_parallel-top.log insertion_cell_sort-top.log insertion_sort_parallel-top.log insertion_sort-top.log matrixmultiplication-top.log merge_sort_loop_merged-top.log merge_sort_parallel-top.log merge_sort_restructured-top.log merge_sort-top.log prefixsumBO-top.log prefixsumHW-top.log prefixsum_optimized-top.log prefixsumSW-top.log spmv2_restructured-top.log spmv2-top.log spmv_restructured-top.log spmv-top.log spmv_unrolled-top.log
/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/../scripts/gen_vivado_hls_csynth_script.py -c /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/__hls_config__.ini -i block_fir.c -o block_fir.tcl
INFO:root:Running: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/../scripts/gen_vivado_hls_csynth_script.py -c /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/__hls_config__.ini -i block_fir.c -o block_fir.tcl
vitis-run --mode hls --tcl  block_fir.tcl

****** vitis-run v2024.1 (64-bit)
  **** SW Build 5074859 on 2024-05-20-23:21:20
  **** Start of session at: Thu May 23 12:30:52 2024
    ** Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
    ** Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
INFO: [HLS 200-112] Total CPU user time: 7.08 seconds. Total CPU system time: 2.01 seconds. Total elapsed time: 16.53 seconds; peak allocated memory: 373.109 MB.
INFO: [vitis-run 60-791] Total elapsed time: 0h 0m 18s
INFO: [vitis-run 60-1662] Stopping dispatch session having empty uuid.
INFO:root:Running: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/../scripts/gen_vivado_hls_csynth_script.py -c /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/__hls_config__.ini -i fir.c -o fir.tcl
vitis-run --mode hls --tcl  fir.tcl

****** vitis-run v2024.1 (64-bit)
  **** SW Build 5074859 on 2024-05-20-23:21:20
  **** Start of session at: Thu May 23 12:31:12 2024
    ** Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
    ** Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.

INFO: [vitis-run 82-31] Launching vitis_hls: vitis_hls -nolog -run tcl -f /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.tcl -work_dir /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples
INFO: [HLS 200-2161] Finished Command csynth_design Elapsed time: 00:00:10; Allocated memory: 47.531 MB.
INFO: [HLS 200-112] Total CPU user time: 6.83 seconds. Total CPU system time: 1.86 seconds. Total elapsed time: 15.29 seconds; peak allocated memory: 381.781 MB.
INFO: [vitis-run 60-791] Total elapsed time: 0h 0m 16s
INFO: [vitis-run 60-1662] Stopping dispatch session having empty uuid.

****** Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
    """

    config_data = read_yaml_config(
        os.path.join(script_dir, "..", "__hls_csynth_log_data_extract__.yml")
    )

    # Use the function to split the input data into sections
    sections = split_input_file_string_into_sections(input_data, config_data)

    # Check that the sections are correct
    assert sections[0][0] == "block_fir"
    assert len(sections[0]) == 11
    assert sections[1][0] == "fir"
    assert len(sections[1]) == 14


def test_split_input_file_into_sections():
    """
    Test function for splitting an input file into sections.

    This function reads a "real" input file and a default csynth configuration file, and then splits
    the input file into sections based on the configuration data.  It asserts that the number of
    sections is equal to 47, and that each section has a length greater than 1.
    """
    input_file_string = read_input_file(os.path.join(script_dir, "make_hls.log"))
    config_data = read_yaml_config(
        os.path.join(script_dir, "..", "__hls_csynth_log_data_extract__.yml")
    )

    sections = split_input_file_string_into_sections(input_file_string, config_data)

    assert len(sections) == 47

    for each_section in sections:
        assert len(each_section) > 1


def test_extract_component_log_data():
    # input_file_string = read_input_file(os.path.join(script_dir, "make_hls.log"))
    input_file_string = """
/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/../scripts/gen_vivado_hls_csynth_script.py -c /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/__hls_config__.ini -i fir.c -o fir.tcl
INFO:root:Running: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/../scripts/gen_vivado_hls_csynth_script.py -c /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/__hls_config__.ini -i fir.c -o fir.tcl
vitis-run --mode hls --tcl  fir.tcl

****** vitis-run v2024.1 (64-bit)
  **** SW Build 5074859 on 2024-05-20-23:21:20
  **** Start of session at: Thu May 23 12:31:12 2024
    ** Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
    ** Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.

INFO: [vitis-run 82-31] Launching vitis_hls: vitis_hls -nolog -run tcl -f /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.tcl -work_dir /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples

****** Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.1 (64-bit)
  **** SW Build 5069499 on May 21 2024
  **** IP Build 5075265 on Wed May 22 21:45:21 MDT 2024
  **** SharedData Build 5076995 on Wed May 22 18:29:18 MDT 2024
  **** Start of session at: Thu May 23 12:31:14 2024
    ** Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
    ** Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.

source /proj/xbuilds/SWIP/2024.1_0522_2023/installs/lin64/Vitis_HLS/2024.1/scripts/vitis_hls/hls.tcl -notrace
INFO: [HLS 200-10] For user 'mpettigr' on host 'xsjapps59' (Linux_x86_64 version 5.15.0-83-generic) on Thu May 23 12:31:16 PDT 2024
INFO: [HLS 200-10] On os Ubuntu 22.04.3 LTS
INFO: [HLS 200-10] In directory '/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples'
Sourcing Tcl script '/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.tcl'
INFO: [HLS 200-1510] Running: open_project fir.proj -reset 
INFO: [HLS 200-10] Creating and opening project '/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj'.
INFO: [HLS 200-1510] Running: add_files fir.c 
INFO: [HLS 200-10] Adding design file 'fir.c' to the project
INFO: [HLS 200-1510] Running: add_files -tb fir-top.c 
INFO: [HLS 200-10] Adding test bench file 'fir-top.c' to the project
INFO: [HLS 200-1510] Running: set_top fir 
INFO: [HLS 200-1510] Running: open_solution solution -reset 
INFO: [HLS 200-10] Creating and opening solution '/proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution'.
INFO: [HLS 200-10] Cleaning up the solution database.
INFO: [HLS 200-1505] Using default flow_target 'vivado'
Resolution: For help on HLS 200-1505 see docs.xilinx.com/access/sources/dita/topic?Doc_Version=2024.1%20English&url=ug1448-hls-guidance&resourceid=200-1505.html
INFO: [HLS 200-1510] Running: set_part virtex7 
INFO: [HLS 200-1611] Setting target device to 'xc7v585t-ffg1761-2'
INFO: [HLS 200-1510] Running: create_clock -period 5 
INFO: [SYN 201-201] Setting up clock 'default' with a period of 5ns.
INFO: [HLS 200-1510] Running: csynth_design 
INFO: [HLS 200-111] Finished File checks and directory preparation: CPU user time: 0.08 seconds. CPU system time: 0 seconds. Elapsed time: 0.09 seconds; current allocated memory: 334.250 MB.
INFO: [HLS 200-10] Analyzing design file 'fir.c' ... 
INFO: [HLS 200-111] Finished Source Code Analysis and Preprocessing: CPU user time: 0.29 seconds. CPU system time: 0.65 seconds. Elapsed time: 1.47 seconds; current allocated memory: 335.816 MB.
INFO: [HLS 200-777] Using interface defaults for 'Vivado' flow target.
INFO: [HLS 200-1995] There were 37 instructions in the design after the 'Compile/Link' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 34 instructions in the design after the 'Unroll/Inline (step 1)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 27 instructions in the design after the 'Unroll/Inline (step 2)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Unroll/Inline (step 3)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Unroll/Inline (step 4)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Array/Struct (step 1)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Array/Struct (step 2)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Array/Struct (step 3)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Array/Struct (step 4)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 25 instructions in the design after the 'Array/Struct (step 5)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 25 instructions in the design after the 'Performance (step 1)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 24 instructions in the design after the 'Performance (step 2)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 37 instructions in the design after the 'Performance (step 3)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 36 instructions in the design after the 'Performance (step 4)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 42 instructions in the design after the 'HW Transforms (step 1)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 200-1995] There were 50 instructions in the design after the 'HW Transforms (step 2)' phase of compilation. See the Design Size Report for more details: /proj/xsjhdstaff2/mpettigr/projects/hls_book/pp4fpgas/examples/fir.proj/solution/syn/report/csynth_design_size.rpt
INFO: [HLS 214-376] automatically set the pipeline for Loop< VITIS_LOOP_8_1> at fir.c:8:18 
INFO: [HLS 214-376] automatically set the pipeline for Loop< VITIS_LOOP_13_2> at fir.c:13:19 
INFO: [HLS 214-421] Automatically partitioning small array 'fir.delay_line' completely based on array size. (fir.c:5:0)
INFO: [HLS 214-270] Inferring pragma 'array_partition type=complete dim=1' for array 'fir.delay_line' due to pipeline pragma (fir.c:5:0)
INFO: [HLS 214-248] Applying array_partition to 'fir.delay_line': Complete partitioning on dimension 1. (fir.c:5:0)
INFO: [HLS 200-111] Finished Compiling Optimization and Transform: CPU user time: 2.09 seconds. CPU system time: 0.5 seconds. Elapsed time: 7.3 seconds; current allocated memory: 345.379 MB.
INFO: [HLS 200-111] Finished Checking Pragmas: CPU user time: 0 seconds. CPU system time: 0 seconds. Elapsed time: 0 seconds; current allocated memory: 345.379 MB.
INFO: [HLS 200-10] Starting code transformations ...
INFO: [HLS 200-111] Finished Standard Transforms: CPU user time: 0.01 seconds. CPU system time: 0.01 seconds. Elapsed time: 0.02 seconds; current allocated memory: 345.496 MB.
INFO: [HLS 200-10] Checking synthesizability ...
INFO: [HLS 200-111] Finished Checking Synthesizability: CPU user time: 0.01 seconds. CPU system time: 0 seconds. Elapsed time: 0.01 seconds; current allocated memory: 345.496 MB.
INFO: [HLS 200-111] Finished Loop, function and other optimizations: CPU user time: 0.03 seconds. CPU system time: 0 seconds. Elapsed time: 0.03 seconds; current allocated memory: 367.074 MB.
INFO: [HLS 200-111] Finished Architecture Synthesis: CPU user time: 0.03 seconds. CPU system time: 0 seconds. Elapsed time: 0.03 seconds; current allocated memory: 376.492 MB.
INFO: [HLS 200-10] Starting hardware synthesis ...
INFO: [HLS 200-10] Synthesizing 'fir' ...
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-42] -- Implementing module 'fir_Pipeline_VITIS_LOOP_8_1' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [SCHED 204-11] Starting scheduling ...
INFO: [SCHED 204-61] Pipelining loop 'VITIS_LOOP_8_1'.
INFO: [HLS 200-1470] Pipelining result : Target II = NA, Final II = 1, Depth = 1, loop 'VITIS_LOOP_8_1'
INFO: [SCHED 204-11] Finished scheduling.
INFO: [HLS 200-111] Finished Scheduling: CPU user time: 0.03 seconds. CPU system time: 0.03 seconds. Elapsed time: 0.09 seconds; current allocated memory: 377.453 MB.
INFO: [BIND 205-100] Starting micro-architecture generation ...
INFO: [BIND 205-101] Performing variable lifetime analysis.
INFO: [BIND 205-101] Exploring resource sharing.
INFO: [BIND 205-101] Binding ...
INFO: [BIND 205-100] Finished micro-architecture generation.
INFO: [HLS 200-111] Finished Binding: CPU user time: 0.01 seconds. CPU system time: 0.01 seconds. Elapsed time: 0.03 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-42] -- Implementing module 'fir_Pipeline_VITIS_LOOP_13_2' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [SCHED 204-11] Starting scheduling ...
INFO: [SCHED 204-61] Pipelining loop 'VITIS_LOOP_13_2'.
INFO: [HLS 200-1470] Pipelining result : Target II = NA, Final II = 1, Depth = 8, loop 'VITIS_LOOP_13_2'
INFO: [SCHED 204-11] Finished scheduling.
INFO: [HLS 200-111] Finished Scheduling: CPU user time: 0.04 seconds. CPU system time: 0 seconds. Elapsed time: 0.06 seconds; current allocated memory: 377.453 MB.
INFO: [BIND 205-100] Starting micro-architecture generation ...
INFO: [BIND 205-101] Performing variable lifetime analysis.
INFO: [BIND 205-101] Exploring resource sharing.
INFO: [BIND 205-101] Binding ...
INFO: [BIND 205-100] Finished micro-architecture generation.
INFO: [HLS 200-111] Finished Binding: CPU user time: 0.02 seconds. CPU system time: 0.01 seconds. Elapsed time: 0.03 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-42] -- Implementing module 'fir' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [SCHED 204-11] Starting scheduling ...
INFO: [SCHED 204-11] Finished scheduling.
INFO: [HLS 200-111] Finished Scheduling: CPU user time: 0.03 seconds. CPU system time: 0 seconds. Elapsed time: 0.04 seconds; current allocated memory: 377.453 MB.
INFO: [BIND 205-100] Starting micro-architecture generation ...
INFO: [BIND 205-101] Performing variable lifetime analysis.
INFO: [BIND 205-101] Exploring resource sharing.
INFO: [BIND 205-101] Binding ...
INFO: [BIND 205-100] Finished micro-architecture generation.
INFO: [HLS 200-111] Finished Binding: CPU user time: 0.03 seconds. CPU system time: 0.05 seconds. Elapsed time: 0.09 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-10] -- Generating RTL for module 'fir_Pipeline_VITIS_LOOP_8_1' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [RTGEN 206-100] Generating core module 'sparsemux_7_2_32_1_1': 1 instance(s).
INFO: [RTGEN 206-100] Finished creating RTL model for 'fir_Pipeline_VITIS_LOOP_8_1'.
INFO: [HLS 200-111] Finished Creating RTL model: CPU user time: 0.03 seconds. CPU system time: 0 seconds. Elapsed time: 0.05 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-10] -- Generating RTL for module 'fir_Pipeline_VITIS_LOOP_13_2' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-1030] Apply Unified Pipeline Control on module 'fir_Pipeline_VITIS_LOOP_13_2' pipeline 'VITIS_LOOP_13_2' pipeline type 'loop pipeline'
INFO: [RTGEN 206-100] Generating core module 'mul_32s_32s_32_5_1': 1 instance(s).
INFO: [RTGEN 206-100] Generating core module 'sparsemux_9_2_32_1_1': 1 instance(s).
INFO: [RTGEN 206-100] Finished creating RTL model for 'fir_Pipeline_VITIS_LOOP_13_2'.
INFO: [HLS 200-111] Finished Creating RTL model: CPU user time: 0.05 seconds. CPU system time: 0.01 seconds. Elapsed time: 0.1 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [HLS 200-10] -- Generating RTL for module 'fir' 
INFO: [HLS 200-10] ----------------------------------------------------------------
INFO: [RTGEN 206-500] Setting interface mode on port 'fir/input_r' to 'ap_none'.
INFO: [RTGEN 206-500] Setting interface mode on port 'fir/output_r' to 'ap_vld'.
INFO: [RTGEN 206-500] Setting interface mode on port 'fir/taps' to 'ap_memory'.
INFO: [RTGEN 206-500] Setting interface mode on function 'fir' to 'ap_ctrl_hs'.
WARNING: [RTGEN 206-101] Register 'fir_delay_line_0' is power-on initialization.
WARNING: [RTGEN 206-101] Register 'fir_delay_line_1' is power-on initialization.
WARNING: [RTGEN 206-101] Register 'fir_delay_line_2' is power-on initialization.
WARNING: [RTGEN 206-101] Register 'fir_delay_line_3' is power-on initialization.
INFO: [RTGEN 206-100] Finished creating RTL model for 'fir'.
INFO: [HLS 200-111] Finished Creating RTL model: CPU user time: 0.06 seconds. CPU system time: 0.01 seconds. Elapsed time: 0.1 seconds; current allocated memory: 377.453 MB.
INFO: [HLS 200-111] Finished Generating all RTL models: CPU user time: 0.17 seconds. CPU system time: 0.03 seconds. Elapsed time: 0.32 seconds; current allocated memory: 380.082 MB.
INFO: [HLS 200-111] Finished Updating report files: CPU user time: 0.21 seconds. CPU system time: 0.03 seconds. Elapsed time: 0.31 seconds; current allocated memory: 381.656 MB.
INFO: [VHDL 208-304] Generating VHDL RTL for fir.
INFO: [VLOG 209-307] Generating Verilog RTL for fir.
INFO: [HLS 200-790] **** Loop Constraint Status: All loop constraints were satisfied.
INFO: [HLS 200-789] **** Estimated Fmax: 353.48 MHz
INFO: [HLS 200-2161] Finished Command csynth_design Elapsed time: 00:00:10; Allocated memory: 47.531 MB.
INFO: [HLS 200-112] Total CPU user time: 6.83 seconds. Total CPU system time: 1.86 seconds. Total elapsed time: 15.29 seconds; peak allocated memory: 381.781 MB.
INFO: [vitis-run 60-791] Total elapsed time: 0h 0m 16s
INFO: [vitis-run 60-1662] Stopping dispatch session having empty uuid.
"""
    config_data = read_yaml_config(
        os.path.join(script_dir, "..", "__hls_csynth_log_data_extract__.yml")
    )

    sections = split_input_file_string_into_sections(input_file_string, config_data)

    hls_compiler_type = get_hls_compiler_type(sections[0], config_data)
    logger.debug(f"hls_compiler_type: {hls_compiler_type}")
    result = extract_component_log_data(hls_compiler_type, sections[0], config_data)

    logger.debug(f"result: {result}")
    logger.debug(f"result['version']: {result['version']}")

    # Check if the function correctly extracted the data
    assert result["version"][0].__contains__("2024.1")
    assert result["command"][0].__contains__("vitis_hls")
