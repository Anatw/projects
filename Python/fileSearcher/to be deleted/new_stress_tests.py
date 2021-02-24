""" test suit for stress-testing the search tool """
import sys

import mytool


try:
    from unittest.mock import patch
except ImportError:
    from mock import patch


# @pytest.fixture(scope="class")
# def create_file():
#     return "file created"

def create_file(num_lines: int) -> str:
    # make sure that the base file, containing 500 lines, can create the new
    # file according to the num_lines provided:
    assert (num_lines % 500) == 0

    base_file = "../tests/big_data_uk_500.txt"
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


def test_very_long_file_5000_lines_s1(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 5000 lines = 10000 matches """
    num_lines = 5000
    file_to_test = create_file(num_lines)
    print("new file name: " + file_to_test)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.parse_arguments(args)
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) -6:] == "10000\n"



