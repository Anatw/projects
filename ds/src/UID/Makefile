# General
# LINKFILES - .o files that are located in different directories (../../obj/file_name) shold be added to the receipe of '_test' and 'deploy'
NAME = uid
TEST = $(NAME)_test
LINKFILES = ;

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
	@ $(gd) $(OBJECTS) -o $(NAME)$@
	@ ./$(NAME)$@

# 4/ Deploying the files - sending %.o files to .obj
deploy: $(OBJECTS)
	@ $(gc) $(OBJECTS) -o $(NAME)$@
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


