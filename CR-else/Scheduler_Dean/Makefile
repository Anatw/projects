gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g
valgrind = valgrind --leak-check=yes --track-origins=yes
# -I tells the preprocessor to search at this path for the header files included in the c file
INCLUDES = -I ../../include

NAME = scheduler_
PRODUCTION = scheduler.c 
OBJECTS = scheduler.o scheduler_test.o ../../obj/uid.o ../../obj/task.o ../../obj/pqueue.o ../../obj/sorted_linked_list.o ../../obj/doubly_linked_list.o 
DEPS = scheduler.h

test: $(OBJECTS)
	@$(gd) $(OBJECTS) $(INCLUDES) -o $(NAME)$@
		@./$(NAME)$@
	
production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) -o scheduler.o
		mv scheduler.o ../../obj

%.o: %.c $(DEPS)
	@$(gd) $(INCLUDES) -c -o $@ $<

vlg: scheduler_test
	@$(valgrind) ./$(TEST)
	
# Room Service
.PHONY: clean vlg
clean:
	rm -rf *.o *.out $(NAME) test

