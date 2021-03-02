""" test suit for the search tool """
import sys
import pytest
from unittest.mock import patch

import my_tool


def test_basic_usage(capsys) -> None:
    """ Basic test with a small file and a string that should provide 4
    matches """

    args = ["my_tool.py", "-ftest.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        assert captured.out == "test.txt:3:6:Dummy Line A Line\n" + \
               "test.txt:3:13:Dummy Line A Line\n" + \
               "test.txt:4:6:Dummy Line B\n" + \
               "test.txt:5:6:Dummy Line C\n"


def test_using_file_path(capsys) -> None:
    """ Test if the tool can accept a file given by full path: test with
    a small file which is given using a path, and a string that should
    provide 4 matches """

    args = ["my_tool.py", "-f/home/anat/Documents/test.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out ==\
               "/home/anat/Documents/test.txt:3:6:Dummy Line A Line\n" + \
               "/home/anat/Documents/test.txt:3:13:Dummy Line A Line\n" + \
               "/home/anat/Documents/test.txt:4:6:Dummy Line B\n" + \
               "/home/anat/Documents/test.txt:5:6:Dummy Line C\n"


def test_two_strings(capsys) -> None:
    """ Sending the tool two strings instead of one - the tool should
    search only for the last string given and ignore the rest """

    args = ["my_tool.py", "-ftest.txt",
            "-sDummy", "-sLine", "-mn"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out ==\
               "test.txt:3:6:Dummy Line A Line\n" + \
               "test.txt:3:13:Dummy Line A Line\n" + \
               "test.txt:4:6:Dummy Line B\n" + \
               "test.txt:5:6:Dummy Line C\n\n" \
               "Total matches for the file 'test.txt': 4\n" \
               "total matches for all files searched: 4\n"

def test_nmatches_print(capsys) -> None:
    """ Basic test for the nmatches (-n) option. Small file and a string
    that should provide 4 matches """

    args = ["my_tool.py", "-ftest.txt", "-sLine", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out ==\
               "test.txt:3:6:Dummy Line A Line\n" + \
               "test.txt:3:13:Dummy Line A Line\n" + \
               "test.txt:4:6:Dummy Line B\n" + \
               "test.txt:5:6:Dummy Line C\n\n" \
               "Total matches for the file 'test.txt': 4\n" \
               "total matches for all files searched: 4\n"


def test_empty_file(capsys) -> None:
    """ Sending the tool and empty file - should work and produce no
    matches """

    args = ["my_tool.py", "-fempty_file.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_no_options(capsys) -> None:
    """ Test valid file and string without providing any option (no
    flag) """

    args = ["my_tool.py", "-fempty_file.txt", "-sLine"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == 'Must enter output specification\n'


def test_no_matches(capsys) -> None:
    """ Test a file using a string that should provide no matches """

    args = ["my_tool.py", "-ftest.txt", "-sline", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


# test a non-existing file
def test_non_existing_file(capsys) -> None:
    """ Testing using a file name of a non-existing file - should print
     an informative massage """

    args = ["my_tool.py", "-fnon_existing_file.txt", "-sline", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "the file \"non_existing_file.txt\" cannot be " \
                               "found in current directory\n"


def test_non_valid_file() -> None:
    """ Sending the tool a non-valid file (image file) - should raise an
    exception """

    with pytest.raises(Exception) as e:
        args = ["my_tool.py", "-fimage.png", "-sline"]
        with patch.object(sys, 'argv', args):
            my_tool.SearchInFile.run()
    assert str(e.value) == "the search tool is meant to be used with text " \
                           "file ('.txt' extension) only."


def test_using_empty_string(capsys) -> None:
    """ Sending the tool a string flag without specifying a string to
    search """

    with pytest.raises(SystemExit) as e:
        args = ["-ftest.txt", "-s", "-m"]
        with patch.object(sys, 'argv', args):
            my_tool.SearchInFile.run()
            assert e.value.code == 2
            print(e.value.args)
    captured = capsys.readouterr()
    assert captured.err == 'usage: -ftest.txt [-h] [-m | -c] [-n] -f FILE ' \
                           '[FILE ...] -s STRING\n-ftest.txt: error: argument' \
                           ' -s/--string: expected one argument\n'


def test_using_no_file(capsys) -> None:
    """ Sending the tool a string flag without specifying a file to
    search inside. Result should be similar to the test without a string,
    so this test also send the -n option - to check that as well """

    with pytest.raises(SystemExit) as e:
        # pytest.raises(ValueError, mytool.SearchInFile.run)
        args = ["my_tool.py", "-f", r"-s\d{5}-\d{6}", "-nm"]
        with patch.object(sys, 'argv', args):
            my_tool.SearchInFile.run()
            assert e.value.code == 2
            print(e.value.args)
    captured = capsys.readouterr()
    assert captured.err == 'usage: my_tool.py [-h] [-m | -c] [-n] -f FILE [' \
                           'FILE ...] -s STRING\nmy_tool.py: error: ' \
                           'argument -f/--file: expected at least one ' \
                           'argument\n'


def test_long_file_500_lines(capsys) -> None:
    """ Testing a big file containing 500 lines, which include matches
    in several places, including first and last lines. Result for 500
    lines should be 1000 matches """

    args = ["my_tool.py", "-fbig_data_uk_500.txt", r"-s\d{5}-\d{6}", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) - 5:] == "1000\n"


# using regex expression is string to search
def test_very_ling_line(capsys) -> None:
    """ Testing a file that include a very long line. Matching string
    will be in different places within the line """

    args = ["my_tool.py", "-fbig_data_uk_very_long_line.txt",
            r"-s[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 4:] == "500\n"


# using regex expression is string to search
def test_multiple_files_with_matches_in_all(capsys) -> None:
    """ Test multiple files at one run, all of them contain matches to
    the given string """

    args = ["my_tool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-sine[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 3:] == "48\n"


# using regex expression is string to search
def test_multiple_files_with_partial_matches(capsys) -> None:
    """ Test multiple files at one run, only some of them contain
    matches to the given string """

    args = ["my_tool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-sLine[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 2:] == "4\n"


# using regex expression is string to search
def test_multiple_files_with_no_matches(capsys) -> None:
    """ Test multiple files at one run, none of them contain matches to
    the given string """

    args = ["my_tool.py", "-ftest.txt", "-fbig_data_uk_500.txt",
            "-fdata.txt", r"-s[^a-zA-Z]Batman[^a-zA-Z]", "-nm"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 2:] == "0\n"
