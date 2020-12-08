gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

# -I tells the preprocessor to search at this path for the header files included in the c file
INCLUDES = -I ../../include

NAME = queue_
PRODUCTION = queue.o ../../obj/singly_linked_list.o
OBJECTS = queue_test.o queue.o ../../obj/singly_linked_list.o
DEPS = queue.h

test: $(OBJECTS)
	@$(gd) $(OBJECTS) -o $(NAME)$@

#bit_array_test.o
production: $(PRODUCTION)
	@$(gc) -c $(PRODUCTION) -o $(NAME)$@

%.o: %.c $(DEPS)
	@$(gd) $(INCLUDES) -c -o $@ $<

# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) $(NAME)test

# the costumer will receive the h files and the o files (in an archive)
