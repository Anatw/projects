gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g
ag
NAME = stack_
PRODUCTION = stack_array.o
OBJECTS = stack_array_test.o stack_array.o
DEPS = stack_array.h

# when typing "make" the "bit_array" file will be created.
test: $(OBJECTS)git add-A
	$(gd) $(OBJECTS) -o $(NAME)

production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) -o $(NAME)$@

	
%.o: %.c $(DEPS)
	$(gd) -c -o $@ $<
	
	
# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
