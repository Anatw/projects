# makefile - cpp
# Makefile - Version 4
NAME:=shapes_test#minion#master_communicator
CC=g++
CFLAGS=-std=c++11 -O3 -pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-std=c++11 -O3  -pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=#hash_table.h
INC_DIR:=-I ../include
OBJ_LIB:=#../lib/
OBJ_LIB_LIB:=-L../lib/lpoint -L ../lib/lglut_utils  #-L../lib/lshapes
LIB:=../src/circle.cpp ../src/color.cpp ../src/line.cpp ../src/rectangle.cpp ../src/shape.cpp ../src/square.cpp

LIBRARIES :=-lboost_system -lboost_chrono -lpthread -lboost_thread

OBJ :=$(NAME).cpp 

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) $(OBJ_LIB_LIB) $(LIB) -c -o $@ $< $(CFLAGS) $(LIBRARIES)

# -o $@ -> Tells make to put the output in a file named after the target
# all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) -L$(OBJ_LIB_LIB) $(LIB) -o a.out $(LIBRARIES)
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) -L$(OBJ_LIB_LIB) $(LIB) -o a.out $(LIBRARIES)

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile

