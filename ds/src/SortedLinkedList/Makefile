# General
NAME = sorted_linked_list
TEST = $(NAME)_test
LINKFILES = ../../obj/doubly_linked_list.o

# Compiler Settings:
gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g
valgrind = valgrind --leak-check=yes --track-origins=yes
gdbtui = gdbtui
lldb = lldb

# Path for the header files
DEPS = ../../include/$(NAME).h	# Same directory header
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


