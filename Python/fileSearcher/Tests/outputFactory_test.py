""" test suit for the search tool """

import MyTool
# import conftest
import sys


try:
    from unittest.mock import patch
except ImportError:
    from mock import patch


def test_parse_args_1(capsys) -> None:
    """ basic test with a small file and 4 matches """
    testargs = ["MyTool.py", "-ftest.txt", "-sLine"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "file name: test.txt, line number: 2, " +\
                "start position: 6, line: Dummy Line A Line\n" +\
                "file name: test.txt, line number: 2, start position: 13, " +\
                "line: Dummy Line A Line\n" +\
                "file name: test.txt, line number: 3, start position: 6, " +\
                "line: Dummy Line B\n" +\
                "file name: test.txt, line number: 4, start position: 6, " +\
                "line: Dummy Line C\n"


def test_total_matches_print_2(capsys) -> None:
    """ basic test with a small file and 4 matches  with total matches print"""
    testargs = ["MyTool.py", "-ftest.txt", "-sLine", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "file name: test.txt, line number: 2, " +\
                "start position: 6, line: Dummy Line A Line\n" +\
                "file name: test.txt, line number: 2, start position: 13, " +\
                "line: Dummy Line A Line\n" +\
                "file name: test.txt, line number: 3, start position: 6, " +\
                "line: Dummy Line B\n" +\
                "file name: test.txt, line number: 4, start position: 6, " +\
                "line: Dummy Line C\n" \
                "\nTotal matches: 4\n"


def test_empty_file_2(capsys) -> None:
    """ test an empty file - result should be an empty string """
    testargs = ["MyTool.py", "-fempty_file.txt", "-sLine"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''


def test_no_string_match_3(capsys) -> None:
    """ Test a file that doesn't contain the string """
    testargs = ["MyTool.py", "-ftest.txt", "-sline"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == ''



def test_total_match_for_no_string_match_4(capsys) -> None:
    """ Test a file that doesn't contain the string """
    testargs = ["MyTool.py", "-ftest.txt", "-sline", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "\nTotal matches: 0\n"


# test a non-existing file
def test_nonexisting_file_4(capsys) -> None:
    """ Testing a non existing file - result should be None """
    testargs = ["MyTool.py", "-fnonExistingFile.txt", "-sline"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out == "the file \"nonExistingFile.txt\" cannot be found in "\
                  "current directory\n"
#
#
# #### NEED TO find a way to capture the error massage from argparse
# # #test with a an empty string
# # def test_using_empty_string_5(capfd) -> None:
# #     """ Testing a file for an empty string  - should return the first raw in
# #     the file """
# #     testargs = ["MyTool.py", "-ftest.txt", "-s\"\""]
# #     with patch.object(sys, 'argv', testargs):
# #         MyTool.SearchInFile.parse_arguments(testargs)
# #         captured = capfd.readouterr()
# #         print(captured)
# #         assert captured.out == ''
# #         assert captured.err == ''
#
# # test with a an empty string
# # def test_using_empty_string_5(capfd) -> None:
# #     """ Testing a file for an empty string  - should return the first raw in
# #     the file """
# #     # with pytest.raises(SystemExit) as pytest_wrapped_e:
# #     # mymodule.will_exit_somewhere_down_the_stack()
# #     try:
# #         testargs = ["MyTool.py", "-ftest.txt", "-s\"\""]
# #         with patch.object(sys, 'argv', testargs):
# #             MyTool.SearchInFile.parse_arguments(testargs)
# #             captured = capfd.readouterr()
# #             print(captured)
# #             # print(pytest_wrapped_e.value.args)
# #             # assert pytest_wrapped_e. == "argument -s/--string: " \
# #             #                                  "expected one argument"
# #
# #             assert captured.out == ''
# #             assert captured.err == ''
# #             # assert sys.stderr.read(20) == "argument -s/--string: expected " \
# #             #                                 "one argument"
# #
# #     except SystemExit as e:
# #         print("testush")
# #         assert isinstance(e.__context__, argparse.ArgumentError)
# #     except sys.stderr as e:
# #         print("testush")
# #         assert isinstance(e.__context__, argparse.ArgumentError)
# #     else:
# #         raise ValueError("Exception not raised")
#
# using regex expresion as string to search


def test_very_long_file_500_lines_6(capsys) -> None:
    """ Testing a very ling file which include a match in several places -
    including first and last lines. Testing only that the total sum of
    matches is correct. 500 lines = 1000 matches """
    testargs = ["MyTool.py", "-fbig_data_UK_500.txt", r"-s\d{5}-\d{6}", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print("6: " + str(captured))
        assert captured.out[len(captured.out) - 5:] == "1000\n"


def test_very_ling_line_7(capsys) -> None:
    """ Testing a file that include a very long line. Matching string
    will be in different places within the line """
    testargs = ["MyTool.py", "-fbig_data_UK_very_long_line.txt",
                r"-s[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+", "-n"]
    with patch.object(sys, 'argv', testargs):
        MyTool.SearchInFile.parse_arguments(testargs)
        captured = capsys.readouterr()
        print(captured)
        assert captured.out[len(captured.out) - 4:] == "500\n"


# def test_multuple_files_8(capsys) -> None:
#     """ Test multiple files at one run """
#     assert False