# Makefile - Version 4
NAME:=scheduler
CC=g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=#hash_table.h
INC_DIR:=-I ../../include
OBJ_LIB:=#../../obj/
 
LIB := #doubly_linked_list.o
OBJ :=$(NAME).cpp $(NAME)_test.cpp fdtimer.cpp ../Reactor/reactor.cpp
 
# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) -L$(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS)  -lpthread -pthread -fopenmp -lboost_system -lrt -lboost_chrono

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out -lpthread -pthread -fopenmp -lboost_system -lrt -lboost_chrono
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out -lpthread -pthread -fopenmp -lboost_system -lrt -lboost_chrono

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile
