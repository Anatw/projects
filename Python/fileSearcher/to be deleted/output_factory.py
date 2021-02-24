from abc import ABCMeta, abstractmethod
import re # for using regular expressions (regex)


# An abstract base class for printing file data. different printing options
# will inherit from it and will implement their specific implementation:
class OutputFormat(metaclass=ABCMeta):
    @staticmethod
    @abstractmethod
    def print():
        """outputFormat interface"""


class BasicOutput(OutputFormat):
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    # @staticmethod
    # def search_string(file_name: str, string_to_search: str) -> list:
    #     """ Search the file for the given string and return the line in
    #     which the string appears """
    #
    #     # list_of_matches = [tuple()]
    #     list_of_matches = [{
    #                            "file name": file_name,
    #                            "line number": int,
    #                            "start position": int}]
    #
    #     try:
    #         with open(file_name, 'r') as fd:
    #             contents = fd.read()
    #             pattern = re.compile(r'{}'.format(string_to_search))
    #             for count, line in enumerate(open(file_name, 'r')):
    #                 for match in re.finditer(pattern, line):
    #                     list_of_matches.append(
    #                         ({
    #                             "file name": file_name,
    #                             "line number": count,
    #                             "start position": match.start()}))
    #                     break
    #
    #     except FileNotFoundError:
    #         print(f"the file \"{file_name}\" cannot be found in current "
    #               f"directory")
    #
    #     return list_of_matches

    def print(self):
        # for match in self.list_of_matches:
        #     print(match)
        matches = [sub["line"] for sub in self.list_of_matches]
        for i in range(len(matches))[1:]:
            print("file name: " + self.list_of_matches[i]["file name"]
                  + ", line number: " + str(self.list_of_matches[i]
                                        ["line number"])
                  + ", start position: " + str(self.list_of_matches[i]
                                        ["start position"])
                  + ", line: " + self.list_of_matches[i]["line"], end='')

        if self.counter:
            print("\nTotal matches: " + str(len(self.list_of_matches) -
                                                  1))


class ColorOutput(OutputFormat):
    # list_of_matches: list self.list_of_mathces = list_of_matches
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    def print(self):
        matches = [sub["line"] for sub in self.list_of_matches]
        for i in range(len(matches))[1:]:
            print("file name: " + self.list_of_matches[i]["file name"]
                  + ", "
                  + "line number: " + str(self.list_of_matches[i]
                                        ["line number"]) + ", "
                  + "start position: " + str(self.list_of_matches[i]
                                        ["start position"]))
            for count, character in enumerate(self.list_of_matches[i][
                                                  "line"]):
                if self.list_of_matches[i]["start position"] <= count < \
                        self.list_of_matches[i]["end position"]:
                    print('\x1b[6;30;42m' + character, end='' + '\x1b[0m')
                else:
                    print(character, end='')

        if self.counter:
            print("\nTotal matches: " + str(len(self.list_of_matches) -
                                                  1))


class MachineOutput(OutputFormat):
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    def print(self):
        print("machine print")


# class OutputFactory():
#     @staticmethod
#     def get_output(outputtype, list_of_matches: list):
#         try:
#             if outputtype == "BasicOutput":
#                 return BasicOutput(list_of_matches)
#             if outputtype == "ColorOutput":
#                 return ColorOutput(list_of_matches)
#             if outputtype == "MachineOutput":
#                 return MachineOutput(list_of_matches)
#             raise AssertionError("output not found")
#         except AssertionError as _e:
#             print(_e)
