# makefile - cpp
# Makefile - Version 4
NAME:=dlloader
CC=g++
CFLAGS=-std=c++98 -pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-std=c++98 -pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=#hash_table.h
INC_DIR:=-I ../../../include -I /home/anat/git/anat-wax/cpp/src/Shapes/include
OBJ_LIB:=-L../../../../Shapes/lib/

SYS_LIB:=-lboost_system -lboost_chrono -lpthread -lboost_thread -ldl -lglut_utils -lpoint -lboost_filesystem
 
LIB := 
OBJ :=$(NAME).cpp  $(NAME)_test.cpp /home/anat/git/anat-wax/cpp/src/project/src/Logger/logger.cpp ../SharedObject/shared_object.cpp ../Dirmonitor/dirmonitor.cpp /home/anat/git/anat-wax/cpp/src/Shapes/src/shape.cpp /home/anat/git/anat-wax/cpp/src/Shapes/src/rectangle.cpp /home/anat/git/anat-wax/cpp/src/Shapes/src/circle.cpp
 
# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) $(OBJ_LIB) $(LIB)  -c -o $@ $< $(CFLAGS) $(SYS_LIB)

# -o $@ -> Tells make to put the output in a file named after the target
# $^ 	-> all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
# -ldl for linker to be able to load the #include <dlfcn.h> (dlopen(), dlclose(), dlsym()) to work
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out $(SYS_LIB)
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out  $(SYS_LIB)

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile
 
 
 