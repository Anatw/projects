# makefile - cpp
# Makefile - Version 4
NAME:=serializer
CC=g++
CFLAGS=-std=c++11 -pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=./include/*.hpp
INC_DIR:=-I ../../include 
OBJ_LIB:=
 
LIB:=# /home/anat/git/anat-wax/cpp/src/Shapes/src/point.cpp
OBJ :=$(NAME).cpp shape.cpp circle.cpp color.cpp# $(NAME)_test.cpp
 
# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -L shapes.so ./ -c -o $@ $< $(CFLAGS) libpoint.a libglut_utils.so -lboost_system -lboost_chrono  -lboost_system -lboost_chrono -lpthread -lboost_thread

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) libpoint.a libglut_utils.so -o a.out -lboost_system -lboost_chrono  -lboost_system -lboost_chrono -lpthread -lboost_thread
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) libpoint.a libglut_utils.so -o a.out -lboost_system -lboost_chrono  -lboost_system -lboost_chrono -lpthread -lboost_thread

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile
 
 