""" test suit for stress-testing the search tool """
import os  # to remove files
import sys  # for use with patch.object
from unittest.mock import patch

from src import my_tool


def create_file(num_lines: int) -> str:
    # make sure that the base file, containing 500 lines, can create the new
    # file according to the num_lines provided:
    assert (num_lines % 500) == 0

    base_file = "big_data_uk_500.txt"
    new_file = f"file_containing_{num_lines}_lines.txt"
    try:
        open(new_file, 'r')
    except IOError:
        num_duplications = num_lines / 500
        for i in range(int(num_duplications)):
            with open(base_file, 'r') as file, open(new_file, 'a') as n_file:
                for line in file:
                    n_file.write(line)
    else:
        print(f"file with the name {new_file} already exists in folder.")

    return new_file


def delete_file(file_to_delete: str) -> None:
    try:
        os.remove(file_to_delete)
    except OSError as e:  # name the Exception `e`
        print("Failed with: ", e.strerror)
        print("Error code:", e.errno)


def test_n_lines(capsys, nlines) -> None:
    """ Dynamic stress test for the number of lines given by the user.
    The test file is a long file which include two matches in every
    line for the string specified in the test - including first and last
    lines. The output printed to the user is not tested - only the total
    sum of matches. """

    num_lines = nlines
    num_duplications = num_lines*2
    chars_from_end = len(str(num_duplications)) + 1
    file_to_test = create_file(num_lines)
    args = ["my_tool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(str(captured))

        assert captured.out[len(captured.out) - chars_from_end:] == str(str(
               num_duplications) + "\n")

    delete_file(file_to_test)
