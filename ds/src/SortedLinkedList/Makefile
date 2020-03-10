gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

# -I tells the preprocessor to search at this path for the header files included in the c file
INCLUDES = -I ../../include

NAME = a.out
PRODUCTION = sorted_linked_list.o ../../obj/doubly_linked_list.o
OBJECTS = sorted_linked_list_test.o sorted_linked_list.o ../../obj/doubly_linked_list.o
DEPS = sorted_linked_list.h

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
