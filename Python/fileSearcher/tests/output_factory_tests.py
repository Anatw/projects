""" test suit for the search tool """
import sys
import pytest
from unittest.mock import patch

from src import mytool


def test_parse_args(capsys) -> None:
    """ basic test with a small file and 4 matches """
    args = ["mytool.py", "-ftest.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        assert captured.out == "file name: test.txt, line number: 2, " + \
               "start position: 6, line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 2, start position: 13, " + \
               "line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 3, start position: 6, " + \
               "line: Dummy Line B\n" + \
               "file name: test.txt, line number: 4, start position: 6, " + \
               "line: Dummy Line C\n"


def test_parse_args_using_file_path(capsys) -> None:
    """ basic test with a small file and 4 matches """
    args = ["mytool.py", "-f/home/anat/Documents/test.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "file name: /home/anat/Documents/test.txt, " \
                               "line number: 2, " + \
               "start position: 6, line: Dummy Line A Line\n" + \
               "file name: /home/anat/Documents/test.txt, line number: 2, " \
               "start position: 13, " + \
               "line: Dummy Line A Line\n" + \
               "file name: /home/anat/Documents/test.txt, line number: 3, " \
               "start position: 6, " + \
               "line: Dummy Line B\n" + \
               "file name: /home/anat/Documents/test.txt, line number: 4, " \
               "start position: 6, " + \
               "line: Dummy Line C\n"


def test_total_matches_print(capsys) -> None:
    """ basic test with a small file and 4 matches  with total matches print"""
    args = ["mytool.py", "-ftest.txt", "-sLine", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "file name: test.txt, line number: 2, " + \
               "start position: 6, line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 2, start position: 13, " + \
               "line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 3, start position: 6, " + \
               "line: Dummy Line B\n" + \
               "file name: test.txt, line number: 4, start position: 6, " + \
               "line: Dummy Line C\n" \
               "\nTotal matches for the file 'test.txt': 4\ntotal matches " \
               "for all files searched: 4\n"


def test_empty_file(capsys) -> None:
    """ test an empty file - result should be an empty string """
    args = ["mytool.py", "-fempty_file.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_no_options(capsys) -> None:
    """ test using no option (no flag) """
    args = ["mytool.py", "-fempty_file.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_no_string_match(capsys) -> None:
    """ Test a file that doesn't contain the string """
    args = ["mytool.py", "-ftest.txt", "-sline", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_total_match_for_no_string_match(capsys) -> None:
    """ Test a file that doesn't contain the string """
    args = ["mytool.py", "-ftest.txt", "-sLine"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "Must enter output specification\n"


# test a non-existing file
def test_nonexisting_file(capsys) -> None:
    """ Testing a non existing file - result should be None """
    args = ["mytool.py", "-fnon_existing_file.txt", "-sline", "-m"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "the file \"non_existing_file.txt\" cannot be " \
                               "found in current directory\n"


def test_non_valid_file(capsys) -> None:
    """ Testing a non valid file - should raise an exception """
    with pytest.raises(Exception) as e:
        args = ["mytool.py", "-fimage.png", "-sline"]
        with patch.object(sys, 'argv', args):
            mytool.SearchInFile.run()
    assert str(e.value) == "the search tool is meant to be used with text " \
                           "file ('.txt' extension) only."



def test_using_empty_string(capsys) -> None:
    """ Running the tool without specifying a string to search """
    with pytest.raises(SystemExit) as e:
        args = ["-ftest.txt", "-s", "-m"]
        with patch.object(sys, 'argv', args):
            mytool.SearchInFile.run()
            assert e.value.code == 2
            print(e.value.args)
    captured = capsys.readouterr()
    assert captured.err == 'usage: -ftest.txt [-h] [-m | -c] [-n] -f FILE ' \
                           '[FILE ...] -s STRING\n-ftest.txt: error: argument' \
                           ' -s/--string: expected one argument\n'


def test_using_no_file(capsys) -> None:
    """ Running the tool without specifying a file """
    with pytest.raises(SystemExit) as e:
        # pytest.raises(ValueError, mytool.SearchInFile.run)
        args = ["mytool.py", "-f", r"-s\d{5}-\d{6}", "-nm"]
        with patch.object(sys, 'argv', args):
            mytool.SearchInFile.run()
            assert e.value.code == 2
            print(e.value.args)
    captured = capsys.readouterr()
    assert captured.err == 'usage: mytool.py [-h] [-m | -c] [-n] -f FILE [' \
                           'FILE ...] -s STRING\nmytool.py: error: ' \
                           'argument -f/--file: expected at least one ' \
                           'argument\n'


def test_very_long_file_500_lines(capsys) -> None:
    """ Testing a very long file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 500 lines = 1000 matches """
    args = ["mytool.py", "-fbig_data_uk_500.txt", r"-s\d{5}-\d{6}", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) - 5:] == "1000\n"


# using regex expression is string to search
def test_very_ling_line(capsys) -> None:
    """ Testing a file that include a very long line. Matching string
    will be in different places within the line """
    args = ["mytool.py", "-fbig_data_uk_very_long_line.txt",
            r"-s[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 4:] == "500\n"


# using regex expression is string to search
def test_multiple_files_all_matches(capsys) -> None:
    """ Test multiple files at one run with matches in all of them """
    args = ["mytool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-sine[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 3:] == "48\n"


# using regex expression is string to search
def test_multiple_files_partial_matches(capsys) -> None:
    """ Test multiple files at one run with matches in some of them """
    args = ["mytool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-sLine[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 2:] == "4\n"


# using regex expression is string to search
def test_multiple_files_no_matches(capsys) -> None:
    """ Test multiple files at one run with matches in none of them """
    args = ["mytool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-s[^a-zA-Z]Batman[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        mytool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 2:] == "0\n"
