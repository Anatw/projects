gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

NAME = uid_
PRODUCTION = uid.o
OBJECTS = uid.o uid_test.o
DEPS = uid.h

test: $(OBJECTS)
	@ $(gd) $(OBJECTS) -o $(NAME)

production: $(PRODUCTION)
	@ $(gc) -c $(PRODUCTION) -o $(NAME)$@
	
%.o: %.c $(DEPS)
	@ $(gd) -c -o $@ $<


# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
