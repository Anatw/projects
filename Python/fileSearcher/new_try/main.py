#!/usr/bin/env python3
from my_tool import SearchInFile

if __name__ == '__main__':
    # The next line work with this command:
    #    python3 my_tool.py -f"test.txt" -s"Line"
    SearchInFile.run()

    # The next line work with this command (for example):
    #    python3 my_tool.py "test.txt" "Line"
    # SearchInFile.SearchString(sys.argv[1], sys.argv[2])

    # SearchInFile.SearchString("test.txt", "Line")
