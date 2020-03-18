.PHONEY: client test clean

NAME = doubly_linked_list

# Copmiler Settings:
CC = gcc
RFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
INCLUDES = -I ../../include


# File names: 
RELEASE_OBJ = $(NAME).c
OBJ = $(NAME)_tests.o $(NAME).o $(LINKFILES)

all: tests

client: $(RELEASE_OBJ)
	$(CC) $(RFLAGS) $(INCLUDES) -c $(RELEASE_OBJ) -o $(NAME).o
	@ar cr ../../obj/$(NAME)$@.a $(NAME).o $(LINKFILES)

tests: $(OBJ)					
	@$(CC) $(DFLAGS) $(OBJ) -o $(NAME)_$@.out
	@./$(NAME)_$@.out

%.o: %.c 
	@$(CC) $(DFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f *.out *.o 
	
