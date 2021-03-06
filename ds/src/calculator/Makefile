# General
NAME := $(patsubst %.c, %.o, $(shell find . -name '*.c' -a ! -name '*test.c')) #object files defenition
TEST = $(NAME)_test #the test file
LINKFILES = ../../obj;


# Compiler Settings:
cc = gcc
gc = $(cc) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = $(cc) -ansi -pedantic-errors -Wall -Wextra -g
valgrind = valgrind --leak-check=yes --track-origins=yes #check valgring
gdbtui = gdb -tui #use gdb tui as debbugger
lldb = lldb #use lldb tui as debbugger

# Path for the header files
INCLUDES = -I ../../include		# Other directories headers

# General defenitions
OBJECTS = $(NAME)_test.o $(NAME).o

# 1/ Compiling with debuger option and running the executable
_test: $(OBJECTS)
	@ $(gd) $(OBJECTS) $(LINKFILES) -o $(NAME)$@
	./$(NAME)$@

# 4/ Deploying the files - sending %.o files to .obj
deploy: $(OBJECTS)
	@ $(gc) $(OBJECTS) $(LINKFILES) -o $(NAME)$@
	mv $(OBJECTS) ../../obj

%.o: %.c $(DEPS)
	@ $(gd) $(INCLUDES) -c -o $@ $<

# 2/ Compiling with everything and valgrind after
vlg: $(TEST)
	@ $(valgrind) ./$(TEST)
	
gt: $(TEST)
	@ $(gdbtui) ./$(TEST)

# make ll
ll: $(TEST) 
	@ $(lldb) ./$(TEST) 

# 3/ Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME)test $(NAME)deploy


