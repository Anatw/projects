gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

NAME = doubly_linked_list_
PRODUCTION = doubly_linked_list.o
OBJECTS = doubly_linked_list.o doubly_linked_list_test.o
DEPS = doubly_linked_list.h

test: $(OBJECTS)
	$(gd) $(OBJECTS) -o $(NAME)

production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) -o $(NAME)$@
	
%.o: %.c $(DEPS)
	$(gd) -c -o $@ $<


# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
