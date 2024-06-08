#!/usr/bin/env python3
#
# disable logging-fstring-interpolation / W1203
# pylint: disable=W1203

"""
Scrap HLS compiler log file and extract data specified with config yaml file to
generate HLS component compile status data yaml file.

This script reads a YAML config file and an input file, and based on the provided
configuration data, it splits the input file into sections and extracts the component
compile data from each section. The extracted data is then written to an output file
in YAML format.

Usage:
    python gen_hls_component_log_data.py -i <input_file> -o <output_file> -y <yaml_config_file>

Arguments:
    -i, --input_file: The input file containing the compiler log.
    -o, --output_file: The output file to write the component compile log data in YAML format.
    -y, --yaml_config_file: The YAML config file specifying the regex patterns for identifying
                            the start and end of each section, as well as the patterns for
                            extracting the required information.

Example YAML Config File:
    component_start:
        pattern: "START_PATTERN"
    component_end:
        pattern: "END_PATTERN"
    component:
        KEY1:
            pattern: "PATTERN1"
        KEY2:
            pattern: "PATTERN2"
            type: "counter"
        KEY3:
            pattern: "PATTERN3"
            type: "list"

Note:
    - The script assumes that the input file and the YAML config file exist.
    - The script requires the PyYAML library to be installed.

"""

import os
import sys
import argparse
import logging
import re
import yaml

logger = logging.getLogger(__name__)


def read_yaml_config(yaml_config_file):
    """
    Read YAML config file and load into a dictionary
    """
    with open(yaml_config_file, "r", encoding="utf-8") as stream:
        try:
            data = yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            print(exc)
            sys.exit(1)

    logger.debug(f"YAML data: {data}")
    return data


def read_input_file(input_file):
    """
    Read input file and load into a dictionary
    """

    with open(input_file, "r", encoding="utf-8") as f:
        data = f.read()
    return data


def get_hls_compiler_type(input_data, yaml_data):
    """
    Get HLS compiler type from input data
    """
    hls_compiler_type = None

    # if input_data is a list of strings do nothing otherwise split into a list of strings
    if not isinstance(input_data, list):
        input_data = input_data.splitlines()

    for line in input_data:
        if re.match(yaml_data["hls_compiler_type"]["vivado_hls"]["pattern"], line):
            hls_compiler_type = "vivado_hls"
            break
        elif re.match(yaml_data["hls_compiler_type"]["vitis_hls"]["pattern"], line):
            hls_compiler_type = "vitis_hls"
            break

    return hls_compiler_type


# Given input file string and config data, split input file string to list of strings
# where each string starts with the component_start and component_end config patterns
def split_input_file_string_into_sections(input_data, config_data):
    """
    Splits the input string into sections based on the provided configuration data.

    Args:
        input_data (str): The input file string to be split into sections.
        config_data (dict): The configuration data containing the regex patterns for identifying
        the start and end of each section.

    Returns:
        list: A list of sections, where each section is a string containing the lines between the
        start and end patterns.

    """

    sections = []

    hls_compiler_type = get_hls_compiler_type(input_data, config_data)

    logger.debug(
        f"component_start: {config_data['component_start'][hls_compiler_type]['pattern']}"
    )
    logger.debug(
        f"component_end: {config_data['component_end'][hls_compiler_type]['pattern']}"
    )
    match_start = re.compile(
        config_data["component_start"][hls_compiler_type]["pattern"]
    )
    match_end = re.compile(config_data["component_end"][hls_compiler_type]["pattern"])
    inside_section = 0

    for line in input_data.splitlines():
        logger.debug(f"inside_section: {inside_section} Line: {line}")
        # if line contains component_start regex pattern, add it to sections
        if match_start.search(line):
            logger.debug(f"Matched start pattern: {line}")
            match = match_start.search(line)
            list_start = [match.group(1)]
            sections.append(list_start)
            sections[-1].append(line)
            logger.debug(f"Sections: {sections}")
            inside_section = 1
        elif match_end.search(line) and inside_section == 1:
            sections[-1].append(line)
            inside_section = 0
        elif inside_section == 1:
            logger.debug(f"Inside section: {line}")
            sections[-1].append(line)

    logger.debug(f"Sections: {sections}")
    return sections


def extract_component_log_data(hls_compiler_type, log_file_string, config_data):
    """
    Extract the component compile data from log file string.

    Args:
        log_file_string (list): A list of strings containing the lines of the component compile log.
        config_data (dict): The configuration data containing the regex patterns for identifying
        the required information.

    Returns:
        dict: A dictionary containing the extracted information.

    """

    component_data = {}
    logger.debug(f"extract_component_log_data - log_file_string: {log_file_string}")
    for line in log_file_string:
        logger.debug(f"extract_component_log_data - Line: {line}")
        for key, value in config_data["component"].items():
            # skip the special type keys for now
            logger.debug(f"Key: {key} Value: {value}")
            logger.debug(f"value keys: {value.keys()}")
            logger.debug(
                f"hls_compiler_type: {hls_compiler_type} Key: {key} Value: {value} line: {line}"
            )
            if hls_compiler_type in value:
                logger.debug(
                    f"hls_compiler_type {hls_compiler_type} found!! - Value: {value}"
                )
                value = value[hls_compiler_type]
            logger.debug(f"Value: {value}")

            # iterate over the pattern list (ensure it is a list)
            for pattern in (
                value["pattern"]
                if isinstance(value["pattern"], list)
                else [value["pattern"]]
            ):
                logger.debug(f"Pattern: {pattern} - Line: {line}")
                match = re.search(pattern, line)
                if match:
                    logger.debug(f"Match: {match} -- line: {line}")
                    if "type" not in value:
                        # make a list of all of the group matches
                        component_data[key] = match.groups()
                        logger.debug(f"Component data {key}: {component_data[key]}")
                    else:
                        if value["type"] == "counter":
                            component_data[key] = component_data.get(key, 0) + 1
                        elif value["type"] == "list":
                            component_data[key] = component_data.get(key, [])
                            component_data[key].append(match.groups())
                        elif value["type"] == "dict":
                            component_data[key] = component_data.get(key, {})
                            component_data[key][match.group(1)] = match.group(2)

    return component_data


def main(args):
    """
    Main function for generating an HLS component compile report.

    Args:
        args (Namespace): Command-line arguments.

    Returns:
        None
    """

    yaml_data = read_yaml_config(args.yaml_config_file)
    input_data = read_input_file(args.input_file)

    hls_compiler_type = get_hls_compiler_type(input_data, yaml_data)

    sections = split_input_file_string_into_sections(input_data, yaml_data)

    components_data = {}

    for section in sections:
        component_data = extract_component_log_data(
            hls_compiler_type, section, yaml_data
        )
        logger.debug(f"Section: {section} Component data: {component_data}")
        component_data = {section[0]: component_data}

        logger.debug(f"Component data: {component_data}")

        components_data = components_data | component_data

    logger.debug(f"Components data: {components_data}")

    # write components_data dictionary out to a yaml file
    with open(args.output_file, "w", encoding="utf-8") as f:
        yaml.dump(components_data, f)

    logger.info(f"Generated HLS component compile yaml report: {args.output_file}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate HLS component compile status"
    )
    # add required argument with switches -i and --input_file to accept input file
    parser.add_argument("-i", "--input_file", help="Input file", required=True)
    # add required argument with switches -o and --output_file to accept output file
    parser.add_argument("-o", "--output_file", help="Output file", required=True)
    # add required argument with switches -y and --yaml_config_file to accept yaml config file
    parser.add_argument(
        "-y", "--yaml_config_file", help="YAML config file", required=True
    )

    parser.add_argument(
        "-v",
        "--verbose",
        help="Increase output verbosity",
        action="store_const",
        const=logging.DEBUG,
        default=logging.INFO,
    )

    args = parser.parse_args()

    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)
    else:
        logging.basicConfig(level=logging.INFO)

    # verify input file exists
    if not os.path.exists(args.input_file):
        print(f"Input file {args.input_file} does not exist")
        sys.exit(1)
    # verify yaml config file exists
    if not os.path.exists(args.yaml_config_file):
        print(f"YAML config file {args.yaml_config_file} does not exist")
        sys.exit(1)

    args = parser.parse_args()

    main(args)
