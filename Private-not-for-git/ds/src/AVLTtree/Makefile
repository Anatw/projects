gc = gcc -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
gd = gcc -ansi -pedantic-errors -Wall -Wextra -g

PRODUCTION = avl_tree.o
OBJECTS = avl_tree_test.o avl_tree.o
DEPS = avl_tree.h


test: $(OBJECTS)
	@ $(gd) $(OBJECTS) -o a.out

production: $(PRODUCTION)
	@ $(gc) -c $(PRODUCTION) -o avl_tree

	
%.o: %.c $(DEPS)
	@ $(gd) -c -o $@ $<
	
	
# Room Service
.PHONY: clean
clean:
	rm -rf *.o *.out $(NAME) test
