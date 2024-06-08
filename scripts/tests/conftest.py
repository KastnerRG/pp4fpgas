import os
import sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import pytest


@pytest.fixture
def test_file():
    """Generate a test file for the test cases."""
    # Setup: create a test file
    with open("test_file.c", "w", encoding="utf-8") as file:
        file.write("void test_function() {}\n")
        file.write("int another_function() {}\n")
        file.write("void test_function2() {}\n")
    yield "test_file.c"
    # Teardown: remove the test file
    os.remove("test_file.c")
