gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g
valgrind = valgrind --leak-check=yes --track-origins=yes
# -I tells the preprocessor to search at this path for the header files included in the c file
INCLUDES = -I ../../../include

NAME = task_
TEST = task_test
PRODUCTION = task.c 
PRODUCT_NAME = task.o
OBJECTS = task.o task_test.o ../../../obj/uid.o
DEPS = ../../../include/task.h

test: $(OBJECTS)
	@$(gd) $(OBJECTS) -o $(NAME)$@
		@./$(NAME)$@
	
production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) $(INCLUDES) -o $(PRODUCT_NAME)
		mv $(PRODUCT_NAME) ../../../obj

%.o: %.c $(DEPS)
	@$(gd) $(INCLUDES) -c -o $@ $<

vlg: $(TEST)
	@$(valgrind) ./$(TEST)
	
# Room Service
.PHONY: clean vlg
clean:
	rm -rf *.o *.out $(NAME) test

# the costumer will receive the h files and the o files (in an archive)
