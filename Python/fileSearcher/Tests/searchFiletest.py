""" test suit for the searchFile class"""

from searchFile import SearchInFile


#This is a test string for use in the different tests
string = "this"


class TestClass:
    def test_base_case(self) -> bool:
        """ test an empty file - result should be None"""
        global string
        anticipated_string = "Hello this is a sample file"
        line = SearchInFile.SearchString("test.txt", string)
        for char_result in line:
            for char_test in anticipated_string:
                if char_result != char_test:
                    return False

        return True


    def test_empty_file(self) -> None:
        """ test an empty file - result should be None"""
        global string
        assert SearchInFile.SearchString("emptyFile.txt", string) == None


    #test a non-existing file
    def test_nonexisting_file(self) -> None:
        """ Testing a non existing file - result should be None """
        global string
        assert SearchInFile.SearchString("nonExistingFile.txt", string) == None


    #test with only part of the searched string inside the file
    def test_nonexisting_string(self) -> None:
        """ Testing a file containing only the part of the string  - should
        return None """
        begining_str = "this if"
        assert SearchInFile.SearchString("test.txt", begining_str) == None


    #test with a an empty string
    def test_using_empty_string(self) -> None:
        """ Testing a file for an empty string  - should return the first raw in
        the file """
        empty_str = ""
        line =  SearchInFile.SearchString("test.txt", empty_str)
        anticipated_string = "Hello this is a sample file"
        for char_result in line:
            for char_test in anticipated_string:
                if char_result != char_test:
                    return False

        return True


    #test with a file that contain the string more than once
    def test_file_containing_multiple_string(self) -> None:
        """ Testing a file for an empty string  - should return None """
        mult_appear_str = "Line"
        line =  SearchInFile.SearchString("test.txt", mult_appear_str)
        anticipated_string = "Dummy Line A"
        for char_result in line:
            for char_test in anticipated_string:
                if char_result != char_test:
                    return False

        return True
