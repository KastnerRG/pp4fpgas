#!/usr/bin/env python3
#
# disable logging-fstring-interpolation / W1203
# pylint: disable=W1203
#
#
"""
This script reads a yaml file and jinja2 template that accesses the data specified in the
yaml file and generates a file with the rendered version of the template.  

The jinja2 template file should access the data in the yaml file as a dictionary with the 
keyword data, so, for example,

{{ data.key }}

in the jinja2 template file would access the value of the key in the yaml file specified as
key: value

resulting in the rendered file containing

value

"""

import os
import sys
import re
import argparse
import logging
import yaml


from jinja2 import Environment, FileSystemLoader

logger = logging.getLogger(__name__)


def read_yaml_file(yaml_config_file):
    """
    Read YAML config file and load into a dictionary
    """
    with open(yaml_config_file, "r", encoding="utf-8") as stream:
        try:
            # data = yaml.safe_load(stream)
            data = yaml.load(stream, Loader=yaml.FullLoader)
        except yaml.YAMLError as exc:
            print(exc)
            sys.exit(1)

    logger.debug(f"YAML data: {data}")
    return data


def get_asciidoc_report(data, template_jinja2_file):
    """
    Generate ASCIIDOC report using Jinja2 template
    """
    logger.debug(f"data: {data}")
    env = Environment(loader=FileSystemLoader(os.path.dirname(template_jinja2_file)))
    env.filters["default"] = lambda value, default: value if value else default
    env.filters["first_item"] = lambda value, default: value[0] if value else default
    env.filters["basename"] = lambda value: os.path.basename(value)
    env.filters["dirname"] = lambda value: os.path.dirname(value)
    env.filters["regex"] = lambda value, pattern, group=1: (
        re.search(pattern, value).group(group) if re.search(pattern, value) else ""
    )
    template = env.get_template(os.path.basename(template_jinja2_file))

    # dump contents of template file
    # get contents of template file
    with open(template_jinja2_file, "r", encoding="utf-8") as f:
        template_contents = f.read()

    logger.debug(f"Jinja2 template file: {template_contents}")

    asciidoc_report = template.render(data=data)
    logger.debug(f"ASCIIDOC report: {asciidoc_report}")
    return asciidoc_report


def get_asciidoc_summary_all_header_file(data, filename="___summary_all_header.adoc"):
    """
    Generate the header of the summary report in ASCIIDOC format.

    Parameters:
    - data: The data dictionary containing the component information.
    - filename: The name of the temporary file to store the header.

    Returns:
    - The filename of the temporary file.
    """
    # Create a temporary file to store the header of the summary report
    with open(f"{filename}", "w", encoding="utf-8") as f:
        f.write(
            """
:toc: preamble
= HLS Component Status Report

|===
|Component Name | Errors | Warnings
{%- for key, value in data.items() %}
{%- set command = value.command[0] %}
{%- set script_name = command | regex('.*?(\\S+\\.tcl)') | basename %}
{%- set report_name = script_name | regex('(\\S+)\\.tcl') %}
| <<{{ report_name }}>> | {{ value.errors_count | default("0") }} | {{ value.warnings_count | default("0") }}
{%- endfor %}
|===

toc::[]

"""
        )
    return filename


def main(arg):
    """
    Main function
    """
    # read yaml config file
    data = read_yaml_file(arg.input_file)
    logger.debug(f"YAML data: {data}")

    logger.debug(f"Jinja2 template file: {arg.template_jinja2_file}")

    if arg.key == "all":
        asciidoc_reports = []
        if arg.header:
            asciidoc_reports.append(get_asciidoc_summary_all_header_file(data))
        for key in data:
            data_key = data[key]
            logger.debug(f"Data key: {data_key}")

            # generate ASCIIDOC report
            asciidoc_report = get_asciidoc_report(data_key, arg.template_jinja2_file)
            logger.debug(f"ASCIIDOC report: {asciidoc_report}")

            asciidoc_reports.append(asciidoc_report)

        asciidoc_report = "\n".join(asciidoc_reports)
    else:
        data_key = data[arg.key]
        logger.debug(f"Data key: {data_key}")
        # generate ASCIIDOC report
        asciidoc_report = get_asciidoc_report(data_key, arg.template_jinja2_file)
        logger.debug(f"ASCIIDOC report: {asciidoc_report}")

    # write ASCIIDOC report to output file
    with open(arg.output_file, "w", encoding="utf-8") as f:
        f.write(asciidoc_report)

    logger.info(f"ASCIIDOC report written to {arg.output_file}")
    logger.debug(f"ASCIIDOC report: {asciidoc_report}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate HLS component status report")
    # add required argument with switches -i and --input_file to accept input file
    parser.add_argument(
        "-i", "--input_file", help="Input yaml data file", required=True
    )
    # add required argument with switches -o and --output_file to accept output file
    parser.add_argument(
        "-o", "--output_file", help="Output ASCIIDOC file", required=True
    )
    # add required argument with switches -y and --yaml_config_file to accept yaml config file
    parser.add_argument(
        "-j",
        "--template_jinja2_file",
        help="Jinja2 report template file",
        required=True,
    )
    # add argument with switches -y and --yaml_config_file to accept yaml config file
    parser.add_argument(
        "-k",
        "--key",
        help="generate report for component",
        default="all",
    )
    # add optional verbose argument
    parser.add_argument(
        "-v",
        "--verbose",
        help="Increase output verbosity",
        action="store_const",
        const=logging.DEBUG,
        default=logging.INFO,
    )
    # add optional boolean header argument to include header.  If not specified, default to true
    parser.add_argument(
        "-hd",
        "--header",
        help="Include header",
        type=bool,
        default=False,
        const=True,
        nargs="?",
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
    # verify template file exists
    if not os.path.exists(args.template_jinja2_file):
        print(f"Template file {args.template_jinja2_file} does not exist")
        sys.exit(1)

    args = parser.parse_args()

    main(args)
