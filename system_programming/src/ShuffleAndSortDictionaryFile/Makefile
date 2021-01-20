# Makefile - Version 4
NAME:=shuffle_and_sort_dictionary_file
CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g#gd#
F_RELEASE:=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3#gc#
DEPS=#hash_table.h
INC_DIR:=-I ../../include
OBJ_LIB:=../../lib/utility.c

OBJ :=$(NAME).c $(OBJ_LIB)#$(NAME)_test.c

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) sorts.c $(INC_DIR) -L$(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS)  -lpthread -pthread -fopenmp

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo "new session:\n\n\n\n\n\n\n\n\n\n\n\n"
	$(CC) $(CFLAGS) $(OBJ) sorts.c $(INC_DIR) $(OBJ_LIB) -o a.out -lpthread -pthread -fopenmp
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) sorts.c $(INC_DIR) $(OBJ_LIB) -o a.out -lpthread -pthread -fopenmp

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile