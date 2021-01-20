gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

NAME = bit_array_
PRODUCTION = bit_array.o
OBJECTS = bit_array_test.o bit_array.o
DEPS = bit_array.h

# when typing "make" the "bit_array" file will be created.
test: $(OBJECTS)
	$(gd) $(OBJECTS) -o $(NAME)

#bit_array_test.o
production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) -o $(NAME)$@

	
%.o: %.c $(DEPS)
	$(gd) -c -o $@ $<

# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
	

# the costumer will receive the h files and the o files (in an archive)
