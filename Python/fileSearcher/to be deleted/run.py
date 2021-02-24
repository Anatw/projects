import pytest
import sys

def main():
    # extract your arg here
    print('Extracted arg[2] is ==> %s' % sys.argv[2])
    print('Extracted arg[3] is ==> %s' % sys.argv[3])
    pytest.main([sys.argv[1]])

if __name__ == '__main__':
    main()