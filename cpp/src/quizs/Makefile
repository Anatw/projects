# makefile - cpp
# Makefile - Version 4
NAME:=hotel-7.1.21#Anat_Wax-23.11.20#minion#master_communicator
CC=g++
# add to CFLAGS and F_RELEASE: -std=c++98
CFLAGS=-pedantic-errors -Wall -Wextra -g#pd#
F_RELEASE:=-pedantic-errors -Wall -Wextra -DNDEBUG -O3#pc#
DEPS=#hash_table.h
INC_DIR:=-I ../../include
OBJ_LIB:=#../../obj/
LIBRARIES:=-lboost_system -lboost_chrono -lpthread -lboost_thread

LIB := #doubly_linked_list.o 
OBJ :=$(NAME).cpp #$(NAME)_test.cpp master_communicator.cpp ../Reactor/reactor.
#cpp ../Logger/logger.cpp ../derived_listener.cpp command.cpp udp_connector.
#cpp 

# $@ -> the file name of the target of the rule
# $< -> the first item in the Dependencies list
# Compiles each of the object files as separate targets
%.o: %.c $(DEPS)
	$(CC) $(OBJ) $(INC_DIR) -L$(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS) $(LIBRARIES)


# -o $@ -> Tells make to put the output in a file named after the target
# all of the file names in $(OBJ) separated by a space
# -pthread added for the # -pthread added for the posix threads API.
# -fopenmp added for pragme in openmp
test: $(OBJ)
	@echo 
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out
	./a.out

testwithoutrun: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out

.PHONY: clean

# Target to clean files created during compilation
clean:
	rm -f *.o hellomake Makefile
	mv Makefile.orig Makefile


# makefile - c
# Makefile - Version 4
# NAME:=hotel-7.1.21#TicTacToe-Roi#Anat_Wax-17.11.20
# CC=gcc
# CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g#gd#
# F_RELEASE:=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3#gc#
# DEPS=#hash_table.h
# INC_DIR:=#-I ../../include
# OBJ_LIB:=#../../obj/

# LIB := #doubly_linked_list.o
# OBJ :=$(NAME).c #$(NAME)_test.c
# LIBRARIES :=#-lpthread -pthread -fopenmp

# # $@ -> the file name of the target of the rule
# # $< -> the first item in the Dependencies list
# # Compiles each of the object files as separate targets
# %.o: %.c $(DEPS)
# 	$(CC) $(OBJ) $(INC_DIR) -L$(OBJ_LIB)$(LIB) -c -o $@ $< $(CFLAGS) $(LIBRARIES)

# # -o $@ -> Tells make to put the output in a file named after the target
# # $^ 	-> all of the file names in $(OBJ) separated by a space
# # -pthread added for the # -pthread added for the posix threads API.
# # -fopenmp added for pragme in openmp
# test: $(OBJ)
# 	@echo 
# 	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out $(LIBRARIES)
# 	./a.out

# testwithoutrun: $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) $(INC_DIR) $(OBJ_LIB)$(LIB) -o a.out $(LIBRARIES)

# .PHONY: clean

# # Target to clean files created during compilation
# clean:
# 	rm -f *.o hellomake Makefile
# 	mv Makefile.orig Makefile