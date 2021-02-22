""" test suit for stress-testing the search tool """

import MyTool
# import conftest
import sys


try:
    # python 3.4+ should use builtin unittest.mock not mock package
    from unittest.mock import patch
except ImportError:
    from mock import patch


def test_very_long_file_5000_lines_s1(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 5000 lines = 10000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_5000.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) -6:] == "10000\n"


def test_very_long_file_50000_lines_s2(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 5000 lines = 10000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_50000.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) -7:] == "100000\n"


def test_very_long_file_250000_lines_s3(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 25000 lines = 500000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_250000.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -7:] == "500000\n"



def test_very_long_file_500000_lines_s4(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 500,000 lines = 1,000,000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_500000.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "1000000\n"


def test_very_long_file_750000_lines_s5(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 750,000 lines = 1,500,000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_750000.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "1500000\n"


def test_very_long_file_900000_lines_s6(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 900,000 lines = 1,800,00 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_900000.txt", r"-s\d{5}-\d{6}",
                "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "1800000\n"


def test_very_long_file_100000_lines_s7(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,000,000 lines = 2,000,000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_1000000.txt", r"-s\d{5}-\d{6}",
                "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "2000000\n"


def test_very_long_file_1250000_lines_s8(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,250,000 lines = 2,500,000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_1250000.txt", r"-s\d{5}-\d{6}",
    "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "2500000\n"


def test_very_long_file_1500000_lines_s9(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 1,500,000 lines = 3,000,000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_1500000.txt", r"-s\d{5}-\d{6}",
    "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        # print("6: " + str(captured))
        assert captured.out[len(captured.out) -8:] == "3000000\n"