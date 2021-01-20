# Makefile - Version 4
NAME:=sem_manipulation
CC=gcc
CFLAGS=-pedantic-errors -Wall -Wextra -g#gd#
F_RELEASE:=-pedantic-errors -Wall -Wextra -DNDEBUG -O3#gc#
DEPS=#hash_table.h
INC_DIR:=-I ../../include

LIB := 
OBJ :=$(NAME).c utility.c#$(NAME)_test.c

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) -L$(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS) -lpthread

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
test: $(OBJ)
	@echo "new session:\n\n\n\n\n\n\n\n\n\n\n\n"
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out -lpthread
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out -lpthread

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile