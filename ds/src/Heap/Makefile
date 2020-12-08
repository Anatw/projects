# Makefile - Version 4
NAME:=heap
DEPS=heap.h

CLEAR=@echo clear
CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g#gd#
F_RELEASE:=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3#gc#
valgrind:=valgrind --leak-check=yes --track-origins=yes
#INC_DIR:=-I /home/anat/git/anat-wax/ds/include/#
INC_UTIL:=-I /home/anat/git/anat-wax/utility/
C_UTIL:=/home/anat/git/anat-wax/utility/
#OBJ_LIB:=/home/anat/git/anat-wax/ds/obj/#


# LIB - the object files my code is depend on inside the obj folder. #
#LIB := dynamic_vector.o#
LIB_TWO := utility.c
OBJ := $(NAME)_test.c $(NAME).c

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(NAME).h
	$(CC) $(OBJ) dynamic_vector.c $(INC_UTIL) -c -o $@ $< $(CFLAGS) -lm
	#	$(CC) $(OBJ) $(INC_DIR) $(INC_UTIL) $(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS) -lm


# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
test: $(OBJ) echo
	$(CC) $(CFLAGS) $(OBJ) dynamic_vector.c $(C_UTIL)$(LIB_TWO) $(INC_UTIL) -o a.out -lm
	./a.out
#	$(CC) $(CFLAGS) $(OBJ) $(C_UTIL)$(LIB_TWO) $(INC_DIR) $(INC_UTIL) $(OBJ_LIB)$(LIB) -o a.out -lm

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) dynamic_vector.c $(C_UTIL)$(LIB_TWO) $(INC_UTIL) -o a.out -lm
#	$(CC) $(CFLAGS) $(OBJ) $(C_UTIL)$(LIB_TWO) $(INC_DIR) $(INC_UTIL) $(OBJ_LIB)$(LIB) -o a.out -lm

echo: 
	@echo "new session:\n\n\n\n\n\n\n\n\n\n\n\n"

vlg: echo
	@$(valgrind) ./a.out

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile