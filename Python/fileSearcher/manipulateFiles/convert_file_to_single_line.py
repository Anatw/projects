if __name__ == '__main__':
    f = open('big_data_uk_to_manipulate.txt', 'r')
    lines = f.readlines()
    pdatedFile = open("big_data_uk_long_line.txt", 'a')
    pdatedFile.write('\t'.join([line.strip() for line in lines]))
