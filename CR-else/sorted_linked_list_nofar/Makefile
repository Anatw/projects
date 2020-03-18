
CC = gcc
GD = -ansi -pedantic-errors -Wall -Wextra -g 
GC = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3

#object file before linker
GOBJ = -c

#object file after linker
GLINK = -o

#path for header files
INCLUDE_PATH = ../../include

#path for object files
OBJ_PATH = ../../obj

.PHONY: clean production test

production: sorted_linked_list.c sorted_linked_list.h
	$(CC) $(GD) -I $(INCLUDE_PATH) $(GOBJ) sorted_linked_list.c 
	
# this target will compile all file
test: sorted_linked_list.o sorted_linked_list_tests.o
	$(CC) $(GD) sorted_linked_list.o sorted_linked_list_tests.o $(OBJ_PATH)/doubly_linked_list.o $(GLINK) test
	./test
	
# header compile with utility.h
header: sorted_linked_list.h
	$(CC) $(GD) -I $(INCLUDE_PATH) $(GOBJ) sorted_linked_list.h $(GLINK) sorted_linked_list.gch
	
	
# header compile with utility.h
sorted_linked_list.gch: sorted_linked_list.h
	$(CC) $(GD) -I $(INCLUDE_PATH) $(GOBJ) sorted_linked_list.h $(GLINK) sorted_linked_list.gch
	
#the target depend on file after :. and the next line (with TAB!) - is the command/action
sorted_linked_list.o: sorted_linked_list.c sorted_linked_list.gch
	@echo hi
	$(CC) $(GD) -I $(INCLUDE_PATH) $(GOBJ) sorted_linked_list.c $(GLINK) sorted_linked_list.o
			
sorted_linked_list_tests.o: sorted_linked_list_tests.c sorted_linked_list.gch 
	@echo hi
	$(CC) $(GD) -I $(INCLUDE_PATH) $(GOBJ) sorted_linked_list_tests.c $(GLINK) sorted_linked_list_tests.o 
					
#clean all the object file we made				
clean:
	rm -rf *.o *.out *.gch
	
	
