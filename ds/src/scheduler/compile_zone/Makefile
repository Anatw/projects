# Debbugers - for testing and for deployment
gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

# Path for the header files
INCLUDES = -I ../../../include

# General defenitions
NAME = scheduler_
PRODUCTION = scheduler.o task.o ../../../obj/%.o
OBJECTS = scheduler_test.o \
		  scheduler.o \
		  task.o \
		  ../../../obj/doubly_linked_list.o \
		  ../../../obj/sorted_linked_list.o \
		  ../../../obj/priority_queue.o \
		  ../../../obj/uid.o
		  
DEPS = scheduler.h task.h
TASKOBJ = task.o task_test.o uid.o 

# Checking that it works
test: $(OBJECTS)
	$(gd) $(OBJECTS) -o $(NAME)$@
	#./$(NAME)$@

task: $(TASKOBJ)
	$(gd) $(TASKOBJ) -o $(NAME)$@
	#./$(NAME)$@

# Deploying the files - sending %.o files to .obj
deploy: $(OBJECTS)
	$(gc) $(OBJECTS) -o $(NAME)$@
	mv $(OBJECTS) ../../../obj

%.o: %.c $(DEPS)
	$(gd) $(INCLUDES) -c -o $@ $<

# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME)test

# how to work with this makefile:
#1. make (for the time you work on the files)
#2. make clean
#3. make deploy (that also create the o files)
