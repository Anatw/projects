# Function to add "\n" in the beginning of every line - not working yet...

if __name__ == '__main__':
    appendText = '\n'
    file = open("big_data_uk_to_manipulate.txt", 'r')
    text = file.readlines()
    updatedFile = open("big_data_uk_manipulated.txt", 'a')
    for line in text:
        updatedFile.write(r"\n"+ line[:-1])
    updatedFile.close()