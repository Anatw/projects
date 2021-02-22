import argparse

def fib(n):
    a = 0
    b = 1

    for i in range(n):
        c = a+b
        a = b
        b = c

    return a

def Main():
    parser = argparse.ArgumentParser()

    group = parser.add_mutually_exclusive_group()
    group.add_argument("-v", "--verbose", action="store_true")
    group.add_argument("-q", "--quiet", action="store_true")

    parser.add_argument("num", help="The fibonacci number you wish to "
                                    "calculate.", type=int)
    parser.add_argument("-o", "--output", help="Output result to a file.",
                        action="store_true")

    # the next line will parse the arguments from the command line
    args = parser.parse_args()

    result = fib(args.num)
    if args.verbose:
        print("The " + str(args.num)+"th fib number is "+str(result))
    elif args.quiet:
        print(result)
    else:
        print("Fib(" + str(args.num)+") = "+str(result))

    if args.output:
        with open("fibonacci.txt", "a") as file:
            file.write(str(result)+'\n')


if __name__ == '__main__':
    Main()