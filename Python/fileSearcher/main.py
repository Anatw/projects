#!/usr/bin/env python3

import sys

from MyTool import SearchInFile


if __name__ == '__main__':
    # The next line work with this command:
    #    python3 MyTool.py -f"test.txt" -s"Line"
    SearchInFile.parse_arguments(sys.argv[1:])

    # The next line work with this command (for example):
    #    python3 MyTool.py "test.txt" "Line"
    # SearchInFile.SearchString(sys.argv[1], sys.argv[2])

    # SearchInFile.SearchString("test.txt", "Line")
