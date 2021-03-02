import sys
from unittest.mock import patch

from src import my_tool


def test_run_stress_tests_1(capsys) -> None:
    args = ["my_tool.py", "-ftest.txt", "-sLine", "-m"]
    with patch.object(sys, 'argv', args):
        my_tool.SearchInFile.run()
        captured = capsys.readouterr()
        assert captured.out == "test.txt:3:6:Dummy Line"