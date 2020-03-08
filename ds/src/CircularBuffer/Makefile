gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

NAME = circular_buffer_
PRODUCTION = circular_buffer.o
OBJECTS = circular_buffer_test.o circular_buffer.o
DEPS = circular_buffer.h

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
