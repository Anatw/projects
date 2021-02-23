""" test suit for the search tool """
import sys

import pytest

import mytool

try:
    from unittest.mock import patch
except ImportError:
    from mock import patch


def test_parse_args_1(capsys) -> None:
    """ basic test with a small file and 4 matches """
    testargs = ["mytool.py", "-ftest.txt", "-sLine"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "file name: test.txt, line number: 2, " + \
               "start position: 6, line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 2, start position: 13, " + \
               "line: Dummy Line A Line\n" + \
               "file name: test.txt, line number: 3, start position: 6, " + \
               "line: Dummy Line B\n" + \
               "file name: test.txt, line number: 4, start position: 6, " + \
               "line: Dummy Line C\n"


def test_parse_args_using_file_path_2(capsys) -> None:
    """ basic test with a small file and 4 matches """
    testargs = ["mytool.py", "-f/home/anat/Documents/test.txt", "-sLine"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
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


def test_total_matches_print_3(capsys) -> None:
    """ basic test with a small file and 4 matches  with total matches print"""
    testargs = ["mytool.py", "-ftest.txt", "-sLine", "-n"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
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
               "\nTotal matches for the file 'test.txt': 4\ntotal matches for " \
               "all files searched: 4\n"


def test_empty_file_4(capsys) -> None:
    """ test an empty file - result should be an empty string """
    testargs = ["mytool.py", "-fempty_file.txt", "-sLine"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_no_string_match_5(capsys) -> None:
    """ Test a file that doesn't contain the string """
    testargs = ["mytool.py", "-ftest.txt", "-sline"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_total_match_for_no_string_match_6(capsys) -> None:
    """ Test a file that doesn't contain the string """
    testargs = ["mytool.py", "-ftest.txt", "-sline", "-n"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "\nTotal matches for the file 'test.txt': 0\n" \
                               "total matches for " \
                               "all files searched: 0\n"


# test a non-existing file
def test_nonexisting_file_7(capsys) -> None:
    """ Testing a non existing file - result should be None """
    testargs = ["mytool.py", "-fnonExistingFile.txt", "-sline"]
    with patch.object(sys, 'argv', testargs):
        mytool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "the file \"nonExistingFile.txt\" cannot be " \
                               "found in " \
                               "current directory\n"


def test_non_valid_file_8(capsys) -> None:
    """ Testing a non existing file - result should be None """
    with pytest.raises(Exception) as e:
        testargs = ["mytool.py", "-fimage.png", "-sline"]
        with patch.object(sys, 'argv', testargs):
            mytool.SearchInFile.parse_arguments(testargs)
            captured = capsys.readouterr()
            # assert e.value == "the search tool is meant to be used with text" \
            #                        " file ('.txt' extension') only.\n"
            print(e.value)
            # assert captured.out == "the search tool is meant to be used with text" \
            #                        " file ('.txt' extension') only.\n"


def test_using_empty_string_9(capsys) -> None:
    with pytest.raises(SystemExit) as e:
        testargs = ["-ftest.txt", "-s"]
        pytest.raises(ValueError, mytool.SearchInFile.parse_arguments, testargs)
        assert e.value.code == 2
    captured = capsys.readouterr()
    print(captured)
    assert captured.err != ''
    assert captured.err == 'usage: pytest [-h] [-m | -c] [-n] -f FILE ' \
                           '[FILE ...] -s STRING\npytest: error: argument ' \
                           '-s/--string: expected one argument\n'


def test_using_no_file_10(capsys) -> None:
    with pytest.raises(SystemExit) as e:
        pytest.raises(ValueError, mytool.SearchInFile.parse_arguments,
                      "-sLine")
        assert e.value.code == 2
    captured = capsys.readouterr()
    print(captured)
    assert captured.err != ''
    assert captured.err == 'usage: pytest [-h] [-m | -c] [-n] -f FILE ' \
                           '[FILE ...] -s STRING\npytest: error: the' \
                           ' following arguments are required: -f/--file,' \
                           ' -s/--string\n'


# def test_very_long_file_500_lines_11(capsys) -> None:
#     """ Testing a very ling file which include a match in several places -
#     including first and last lines. Testing only that the total sum of
#     matches is correct. 500 lines = 1000 matches """
#     testargs = ["mytool.py", "-fbig_data_UK_500.txt", r"-s\d{5}-\d{6}", "-n"]
#     with patch.object(sys, 'argv', testargs):
#         mytool.SearchInFile.parse_arguments(testargs)
#         captured = capsys.readouterr()
#         print("6: " + str(captured))
#         assert captured.out[len(captured.out) - 5:] == "1000\n"
#
#
# # using regex expression is string to search
# def test_very_ling_line_12(capsys) -> None:
#     """ Testing a file that include a very long line. Matching string
#     will be in different places within the line """
#     testargs = ["mytool.py", "-fbig_data_UK_very_long_line.txt",
#                 r"-s[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+", "-n"]
#     with patch.object(sys, 'argv', testargs):
#         mytool.SearchInFile.parse_arguments(testargs)
#         captured = capsys.readouterr()
#         print(captured)
#         assert captured.out[len(captured.out) - 4:] == "500\n"


# # using regex expression is string to search
# def test_multiple_files_all_matches_13(capsys) -> None:
#     """ Test multiple files at one run with matches in all of them """
#     testargs = ["mytool.py", "-ftest.txt", "-fbig_data_UK_500.txt",
#                 "-fdata.txt", r"-sine[^a-zA-Z]", "-n"]
#     with patch.object(sys, 'argv', testargs):
#         mytool.SearchInFile.parse_arguments(testargs)
#         captured = capsys.readouterr()
#         print(captured)
#         assert captured.out[len(captured.out) - 3:] == "48\n"
#
#
# # using regex expression is string to search
# def test_multiple_files_partial_matches_14(capsys) -> None:
#     """ Test multiple files at one run with matches in some of them """
#     testargs = ["mytool.py", "-ftest.txt", "-fbig_data_UK_500.txt",
#                 "-fdata.txt", r"-sLine[^a-zA-Z]", "-n"]
#     with patch.object(sys, 'argv', testargs):
#         mytool.SearchInFile.parse_arguments(testargs)
#         captured = capsys.readouterr()
#         print(captured)
#         assert captured.out[len(captured.out) - 2:] == "4\n"
#
#
# # using regex expression is string to search
# def test_multiple_files_no_matches_15(capsys) -> None:
#     """ Test multiple files at one run with matches in none of them """
#     testargs = ["mytool.py", "-ftest.txt", "-fbig_data_UK_500.txt",
#                 "-fdata.txt", r"-s[^a-zA-Z]Batman[^a-zA-Z]", "-n"]
#     with patch.object(sys, 'argv', testargs):
#         mytool.SearchInFile.parse_arguments(testargs)
#         captured = capsys.readouterr()
#         print(captured)
#         assert captured.out[len(captured.out) - 2:] == "0\n"
