import os
import subprocess
import pytest
from jinja2 import Environment, FileSystemLoader

from gen_template_report import get_asciidoc_report

# get script directory
script_dir = os.path.dirname(os.path.realpath(__file__))


def test_get_asciidoc_report():
    """
    Test the get_asciidoc_report function.

    This function tests the functionality of the get_asciidoc_report function by
    creating a mock jinja2 environment and template, generating a template
    file using the mock data, and then calling the get_asciidoc_report function
    with the mock data and template. The result is then asserted to be equal to
    the expected value.
    """

    # Mock data and template
    data = {"key": "value"}
    template_file = "template.jinja2"

    # Create a mock jinja2 environment and template
    env = Environment(loader=FileSystemLoader("."))
    template = env.from_string("{{ key }}")
    template.stream(data).dump(template_file)

    # Call the function with the mock data and template
    result = get_asciidoc_report(data, template_file)

    # Assert the result is as expected
    assert result == "value"

    # Cleanup
    os.remove(template_file)


def test_cli():
    """
    Test the command-line interface of the gen_template_report script.

    This function performs the following steps:
    1. Creates a temporary test input yaml file.
    2. Creates a temporary jinja2 template file to render from the input yaml file data.
    3. Runs the gen_template_report script with some input.
    4. Checks the exit code of the script.
    5. Verifies that the output file contains the expected content.
    6. Cleans up the temporary files.

    Raises:
        AssertionError: If the exit code is not 0 or the output file does not contain
        the expected content.
    """
    # create a temporary test input yaml file
    with open("input.yaml", "w", encoding="utf-8") as f:
        f.write("foo:\n")
        f.write("  key: value")

    # create a temporary jinja2 template file
    # to render from the input yaml file data
    with open("template.j2", "w", encoding="utf-8") as f:
        f.write("{{ data.key }}")

    # Run the script with some input
    result = subprocess.run(
        [
            "python3",
            os.path.join(script_dir, "..", "gen_template_report.py"),
            "-i",
            "input.yaml",
            "-o",
            "output.adoc",
            "-j",
            "template.j2",
            "-v",
        ],
        capture_output=True,
        text=True,
        check=True,  # Add the check argument
    )

    # Check the exit code
    assert result.returncode == 0

    # check the contents of the output file
    # verify that the output file contains the expected content
    with open("output.adoc", encoding="utf-8") as f:
        assert f.read() == "value"

    # Cleanup
    os.remove("input.yaml")
    os.remove("template.j2")
    os.remove("output.adoc")
