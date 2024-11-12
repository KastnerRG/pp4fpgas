import os
import textwrap
from gen_hls_csynth_script import *

import tempfile
from configparser import ConfigParser

import logging

logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)


def test_read_config_file():
    """
    Test the read_config_file function.
    """
    # Create a temporary configuration file
    with tempfile.NamedTemporaryFile(mode="w", delete=False) as tmpfile:
        config_content = "[DEFAULTS]\npart = xc7z010clg400-1\nperiod = 10\n"
        tmpfile.write(config_content)
        tmpfile.flush()

        # Call the function with the temporary file
        config = read_config_file(tmpfile.name)

    # Check that the config object has the expected content
    assert config.get("DEFAULTS", "part") == "xc7z010clg400-1"
    assert config.get("DEFAULTS", "period") == "10"


def test_write_csynth_script():
    """
    Test the write_csynth_script function.
    """
    # Define parameters
    input_file = "test_input.cpp"
    params = {
        "top": "test_top",
        "part": "xc7z010clg400-1",
        "period": "10",
        "files": "test_input.cpp",
        "tb_files": "none",
    }

    # Create a temporary output file
    with tempfile.NamedTemporaryFile(mode="w", delete=False) as tmpfile:
        output_file = tmpfile.name

    # Call the function with the parameters and temporary output file
    write_csynth_script(input_file, output_file, "", params)

    # Read the content of the output file
    with open(output_file, "r") as file:
        content = file.read()

    logger.debug(content)
    # Define the expected script content
    expected_content = """\
                    open_project test_input.proj -reset
                    add_files [list test_input.cpp]
                    
                    set_top test_top
                    puts "Running: set_top test_top"
                    open_solution solution -reset
                    set_part xc7z010clg400-1
                    puts "Running: set_part xc7z010clg400-1"
                    create_clock -period 10
                    csynth_design
                    exit"""
    # Check that the content matches the expected script
    assert content.strip() == textwrap.dedent(expected_content)
