""" test suit for stress-testing the search tool """
import os  # to remove files
import sys  # for use with patch.object
from unittest.mock import patch

from src import mytool


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
        print("Error code:", e.code)


def test_very_long_file_5000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 5000 lines = 10000 matches """
    num_lines = 5000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(str(captured))
        assert captured.out[len(captured.out) - 6:] == "10000\n"

    delete_file(file_to_test)


def test_very_long_file_50000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 5000 lines = 10000 matches """
    num_lines = 50000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) - 7:] == "100000\n"

    delete_file(file_to_test)


def test_very_long_file_250000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 25000 lines = 500000 matches """
    num_lines = 250000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 7:] == "500000\n"

    delete_file(file_to_test)


def test_very_long_file_500000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 500,000 lines = 1,000,000 matches """
    num_lines = 500000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 8:] == "1000000\n"

    delete_file(file_to_test)


def test_very_long_file_750000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 750,000 lines = 1,500,000 matches """
    num_lines = 750000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 8:] == "1500000\n"

    delete_file(file_to_test)


def test_very_long_file_1000000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,000,000 lines = 2,000,000 matches """
    num_lines = 1000000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}",
            "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 8:] == "2000000\n"

    delete_file(file_to_test)


def test_very_long_file_1250000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,250,000 lines = 2,500,000 matches """
    num_lines = 1250000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}",
            "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 8:] == "2500000\n"

    delete_file(file_to_test)


def test_very_long_file_1500000_lines(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,500,000 lines = 3,000,000 matches """
    num_lines = 1500000
    file_to_test = create_file(num_lines)
    args = ["mytool.py", str("-f" + file_to_test), r"-s\d{5}-\d{6}",
            "-n"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) - 8:] == "3000000\n"

    delete_file(file_to_test)
