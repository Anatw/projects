# Function that receieve a file and a string to search and

class SearchInFile:
    def SearchString(file_name: str, string_to_search: str) -> str:
        """ Search the file for the given string and return the line in
        which the string appears """


        try:
            with open(file_name, 'r') as fd:
                for line in fd:
                    if string_to_search in line:
                        return line
        except FileNotFoundError:
            print(f"the file \"{file_name}\" cannot be found in current "
                  f"directory")
        return None

