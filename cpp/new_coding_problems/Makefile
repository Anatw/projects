# makefile - cpp
# Makefile - Version 4
NAME:=num_add_to_k#minion#master_communicator
CC=g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=#hash_table.h
INC_DIR:=#-I ../../include
OBJ_LIB:=#../../obj/

LIB :=-lboost_system -lboost_chrono -lpthread -lboost_thread
OBJ :=$(NAME).cpp #$(NAME)_test.cpp master_communicator.cpp ../Reactor/reactor.
#cpp 

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) -L$(OBJ_LIB) -c -o $@ $< $(CFLAGS) $(LIB)


# -o $@ -> Tells make to put the output in a file named after the target
# all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB) -o a.out $(LIB)
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB) -o a.out $(LIB)

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile

