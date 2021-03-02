# Function that receive a file and a string to search and
import re  # for using regular expressions (regex)
import argparse  # for parsing the argv

import op_factory


class SearchInFile:

    @staticmethod
    def run():
        args = SearchInFile.parse_arguments()
        SearchInFile.create_output_prints(args)

    @staticmethod
    def parse_arguments():
        parser = argparse.ArgumentParser(
            description='Define search result processing.')
        group = parser.add_mutually_exclusive_group()
        group.add_argument('-m', '--machine', action="store_true",
                           help='generate machine-readable output')
        group.add_argument('-c', '--color', action="store_true",
                           help='highlight matching text')
        parser.add_argument('-n', '--nmatches', action="store_true",
                            help='return number of matches')
        parser.add_argument('-f', '--file', required=True, nargs='+',
                            action='append',
                            help='<Required> file to search inside for a string')
        parser.add_argument('-s', '--string', type=str, required=True,
                            help='<Required> string to search for inside file/s')

        args = parser.parse_args()

        return args

    @staticmethod
    def create_output_prints(args):
        if args.nmatches:
            counter = True
            total_matches = 0
        else:
            counter = False
        for file_list in args.file:
            for file in file_list:
                if not file.lower().endswith('.txt'):
                    raise Exception("the search tool is meant to be used with "
                                    "text file ('.txt' extension) only.")
                list_of_matches = SearchInFile.search_string(file,
                                                             args.string)
                output = op_factory.OutputFactory.get_output(
                    args, list_of_matches, counter)
                if counter:
                    total_matches = total_matches + (len(list_of_matches)
                                                     - 1)

                output.print()
        if counter:
            print("total matches for all files searched: " + str(
                total_matches))

    @staticmethod
    def search_string(file_name: str, string_to_search: str) -> list:
        """ Search the file for the given string and return the line in
        which the string appears """

        # list_of_matches = [tuple()]
        list_of_matches = [{"file name": file_name,
                            "line number": int,
                            "start position": int,
                            "end position": int,
                            "line": str}]

        try:
            pattern = re.compile(r'{}'.format(string_to_search))
            for count, line in enumerate(open(file_name, 'r')):
                for match in re.finditer(pattern, line):
                    list_of_matches.append(
                        ({
                            "file name": file_name,
                            "line number": count+1,
                            "start position": match.start(),
                            "end position": match.end(),
                            "line": line}))

        except FileNotFoundError:
            print(f"the file \"{file_name}\" cannot be found in current "
                  f"directory")

        return list_of_matches
