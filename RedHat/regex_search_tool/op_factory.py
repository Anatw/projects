from abc import ABCMeta, abstractmethod


# An abstract base class for printing file data. different printing
# options will inherit from it and will implement their specific
# print method:
class OutputFormat(metaclass=ABCMeta):
    @staticmethod
    @abstractmethod
    def print():
        """outputFormat interface"""


class BasicOutput(OutputFormat):
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    def print(self):
        print("Must enter output specification")


class ColorOutput(OutputFormat):
    # list_of_matches: list self.list_of_mathces = list_of_matches
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    def print(self):
        matches = [sub["line"] for sub in self.list_of_matches]
        for i in range(len(matches))[1:]:
            file_name = self.list_of_matches[i]["file name"]
            line_number = str(self.list_of_matches[i]["line number"])
            start_position = str(self.list_of_matches[i]["start position"])
            print(f"{file_name}:{line_number}:{start_position}:", end="")
            for count, character in enumerate(self.list_of_matches[i]["line"]):
                if self.list_of_matches[i]["start position"] <=\
                        count < self.list_of_matches[i]["end position"]:
                    print('\x1b[1;30;42m' + character, end='' + '\x1b[0m')
                else:
                    print(character, end='')

        if self.counter:
            print("\nTotal matches: " + str(len(self.list_of_matches) - 1))


class MachineOutput(OutputFormat):
    def __init__(self, list_of_matches: list, counter: bool):
        self.list_of_matches = list_of_matches
        self.counter = counter

    def print(self):
        matches = [sub["line"] for sub in self.list_of_matches]
        file_name = self.list_of_matches[0]["file name"]
        for i in range(len(matches))[1:]:
            line_number = str(self.list_of_matches[i]["line number"])
            start_pos = str(self.list_of_matches[i]["start position"])
            matched_text = self.list_of_matches[i]["line"]
            print(f"{file_name}:{line_number}:{start_pos}:{matched_text}",
                  end='')

        if self.counter:
            print(f"\nTotal matches for the file '{file_name}': " +
                  str(len(self.list_of_matches) - 1))


class OutputFactory:
    @staticmethod
    def get_output(args, list_of_matches: list, counter):
        try:
            if args.color:
                return ColorOutput(list_of_matches, counter)
            if args.machine:
                return MachineOutput(list_of_matches, counter)
            else:
                return BasicOutput(list_of_matches, counter)
        except AssertionError as _e:
            print(_e)
