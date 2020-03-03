#files in thie folder: dynamic_vector.c  dynamic_vector.h  dynamic_vector_test.c

gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

NAME = dynamic_vector_
PRODUCTION = dynamic_vector.o
OBJECTS = dynamic_vector_test.o dynamic_vector.o
DEPS = dynamic_vector.h

# when typing "make" the "a.out" file will be created.
test: $(OBJECTS)
	$(gd) $(OBJECTS) -o $(NAME)

#bit_array.o
production: $(PRODUCTION)
	$(gc) -c $(PRODUCTION) -o $(NAME)$@

	
%.o: %.c $(DEPS)
	$(gd) -c -o $@ $<


# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
