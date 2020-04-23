# General
NAME := hash_table#object files defenition
TEST := $(NAME)_test#the test file
LINKFILES := ../../obj/doubly_linked_list.o


# Compiler Settings:
cc = gcc
gc = $(cc) -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = $(cc) -ansi -pedantic-errors -Wall -Wextra -g
valgrind = valgrind --leak-check=yes --track-origins=yes#check valgring
gdbtui = gdb -tui#use gdb tui as debbugger
lldb = lldb#use lldb tui as debbugger

# Path for the header files - Other directories headers
INCLUDES = -I../../include

# General defenitions
OBJECTS = $(NAME)_test.o $(NAME).o

# 1/ Compiling with debuger option and running the executable
_test: $(OBJECTS)
	@ $(gd) $(OBJECTS) $(LINKFILES) -lm -o a.out
	./a.out

testwithoutrun: $(OBJECTS)
	@ $(gd) $(OBJECTS) $(LINKFILES) -lm -o a.out

# 4/ Deploying the files - sending %.o files to .obj
deploy: $(OBJECTS)
	@ $(gc) $(OBJECTS) $(LINKFILES) -o $(NAME)
	mv $(OBJECTS) ../../obj

%.o: %.c 
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
.PHONY: clean, testwithoutrun
clean:
	rm -rf *.o *.out $(NAME)test $(NAME)deploy
