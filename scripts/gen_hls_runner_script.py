#!/usr/bin/env python3
#
# disable logging-fstring-interpolation / W1203
# pylint: disable=W1203
#

"""
This script generates a HLS flow Tcl script based on the provided input file and configuration.

Usage:
    python gen_hls_runner_script.py -i <input_file> 
                                           -o <output_file> 
                                           [-v] [-c <config_file>] [-id <id_tag>]

Arguments:
    -i, --input: Input file name (required)
    -o, --output: Output file name (required)
    -v, --verbose: Increase output verbosity (optional)
    -c, --config: Config file name (default: __hls_config__.ini)
    -id, --id: ID tag when accessing multiple versions (optional)
    -imp, --impl: include implementation run (optional)

The script reads the provided input file and configuration file, and generates an
HLS Tcl script based on the specified parameters. The  HLS Tcl script is then written 
to the output file.  The HLS flow can optionally include running the implementation as well.

The input file should be a C/C++ file containing void functions. The configuration 
file should be in INI format, and should contain the modified values for the HLS Tcl 
script parameters. The HLS Tcl script parameters can be overridden for specific sections.
Different configurations for same top-level HLS C++ can be selected 
using the ID tag.  For example,

[huffman_encoding.cpp]
top = huffman_encoding
files = huffman_encoding.cpp \
               huffman_canonize_tree.cpp \
               huffman_compute_bit_length.cpp \
               huffman_create_codeword.cpp \
               huffman_create_tree.cpp \
               huffman_filter.cpp \
               huffman_sort.cpp
tb_files = huffman_encoding_test.cpp

[huffman_encoding.cpp:test2]
top = huffman_encoding.cpp:top
files = huffman_encoding.cpp:files
tb_files = huffman_encoding_test2.cpp

You can select huffman_coding.cpp:test2 with "-i huffman_encoding.cpp -id test2"

Note also: You can use the colon separator to reference another value in the config file.

Example:
    python gen_vivado_hls_runner_script.py -i input_file.cpp 
                                           -o output_file.tcl -v -c config.ini -id version1
"""

from pathlib import Path
import sys
import argparse
import logging
import re
import configparser
import textwrap

logger = logging.getLogger(__name__)


def read_config_file(config_file):
    """Read the config file and return the config object"""
    config = configparser.ConfigParser()
    config.read(config_file)
    return config


def write_script(
    input_file,
    output_file,
    impl,
    params,
):
    "Write the HLS script to the output file"

    file_root = input_file.split(".")[0]

    # get the HLS Tcl script parameters
    top = params["top"]
    part = params["part"]
    period = params["period"]
    files = params["files"]
    tb_files = params["tb_files"]

    # if tb_files in ini file is defined tb_files = none then don't
    # add tb_files in the Tcl script
    if tb_files in ("none", "{}"):
        tb_add_files = ""
    else:
        tb_add_files = f"add_files -tb [list {tb_files}]"

    # if impl is true then add the implementation flow to the script
    if impl:
        impl_flow = f"""\
            export_design -description "{file_root}" -display_name "{file_root}" -flow impl -format syn_dcp -ipname {file_root} -library user -taxonomy user -vendor amd -version 1.0.0 -rtl verilog
        """
    else:
        impl_flow = ""

    with open(output_file, "w", encoding="utf-8") as file:
        script_text = f"""\
                    open_component {file_root}.comp -reset
                    add_files [list {files}]
                    {tb_add_files}
                    set_top {top}
                    puts "Running: set_top {top}"
                    set_part {part}
                    puts "Running: set_part {part}"
                    create_clock -period {period}
                    csynth_design
                    {impl_flow}
                    exit"""
        logger.debug(f"Script text: {textwrap.dedent(script_text)}")
        file.write(textwrap.dedent(script_text))

    logging.debug(f"HLS Tcl script written to {output_file}")


def get_script_parameters(input_file, config, id_tag=None):
    """
    Get the HLS script parameters from the config file.

    Args:
        input_file (str): The path to the input file.
        config (ConfigParser): The configuration object containing the script parameters.
        id_tag (str, optional): An optional tag to identify the specific section in the config file.
        Defaults to None.

    Returns:
        dict: A dictionary containing the HLS Tcl script parameters.

    """
    # get the basename of the input file
    file_basename = Path(input_file).name
    logger.debug(f"basename Input file: {file_basename}")

    # get the base name of the input file without extension
    file_rootname = input_file.split(".")[0]
    logger.debug(f"Rootname Input file: {file_rootname}")

    # get the extension of the input file
    file_suffix = input_file.split(".")[1]
    logger.debug(f"Suffix Input file: {file_suffix}")

    config_dict = {section: dict(config[section]) for section in config.sections()}
    logger.debug(f"config: {config_dict}")
    # set the parameters for the Tcl script using default values
    parameters = {
        "top": file_rootname,
        "part": config["DEFAULTS"]["part"],
        "period": config["DEFAULTS"]["period"],
        "files": file_basename,
        "tb_files": f"{file_rootname}-top.{file_suffix}",
    }

    # update each parameter if it is defined in the config file and
    # its option exists
    if id_tag is not None:
        file_basename_id = f"{file_basename}:{id_tag}"
    else:
        file_basename_id = file_basename

    # handle the case where a value in the config file references another
    # value using a colon separator.
    if config.has_section(file_basename_id):
        for key in parameters:
            if config.has_option(file_basename_id, key):
                # if value contains colon found with regex then use the referenced value
                if re.search(r":", config[file_basename_id][key]):
                    referenced_value = config[file_basename_id][key].split(":")
                    parameters[key] = config[referenced_value[0]][referenced_value[1]]
                else:
                    parameters[key] = config[file_basename][key]

    return parameters


def main(input_file, output_file, config_file, id_tag=None, impl=False):
    """Main function to process input file and write to output file"""

    logging.debug(
        f"Processing input file {input_file} and writing to output file {output_file}"
    )

    # assert that the input and config files exists
    input_file_path = Path(input_file)
    assert input_file_path.exists(), f"Input file {input_file} not found"

    config_file_path = Path(config_file)
    assert config_file_path.exists(), f"Config file {config_file} not found"

    # read the config file
    config = read_config_file(config_file)

    # get the script parameters
    params = get_script_parameters(input_file, config, id_tag)

    write_script(
        input_file,
        output_file,
        impl,
        params,
    )

    output_file = Path(output_file)
    assert output_file.exists(), f"Output file {output_file} not found"


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process some files.")
    parser.add_argument("-i", "--input", help="Input file name", required=True)
    parser.add_argument("-o", "--output", help="Output file name", required=True)
    # add optional verbose flag for logging with default value INFO and set to DEBUG if enabled.
    parser.add_argument(
        "-v",
        "--verbose",
        help="Increase output verbosity",
        action="store_const",
        const=logging.DEBUG,
        default=logging.INFO,
    )
    # add optional config ini file
    parser.add_argument(
        "-c",
        "--config",
        help="Config file name",
        default="__hls_config__.ini",
    )
    # add optional argument to specify id
    parser.add_argument(
        "-id", "--id", help="ID tag when accessing multiple versions", required=False
    )
    # add optional argument to specify adding implementation to flow in Tcl script
    parser.add_argument(
        "-imp",
        "--impl",
        help="Include implementation in flow when generating Tcl script",
        action="store_true",
        default=False,
        required=False,
    )

    args = parser.parse_args()

    logging.basicConfig(level=args.verbose)

    # add info log message of the python command line
    logging.info(f"Running: {' '.join(sys.argv)}")

    main(args.input, args.output, args.config, args.id, args.impl)
