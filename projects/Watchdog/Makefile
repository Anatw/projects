.PHONEY: client test clean

#gd Watchdog.c Watchdog_test.c -L. -lsched -pthread

#gd Watchdog_prog.c Watchdog.c -L. -lsched -pthread

# gd  Watchdog_prog.c  Watchdog.c scheduler.o doubly_linked_list.o priority_queue.o uid.o task.o sorted_linked_list.o -L. -lsched -l pthread

# File name #
NAME:=Watchdog
NAME_P:=Watchdog_prog
# Compiler & Flags: #
CC:= gcc
# -ansi flag causes implicit declarations #
F_RELEASE:= -pedantic-errors -Wall -Wextra -DNDEBUG -O3
F_DEBUG:= -pedantic-errors -Wall -Wextra -g
WNO:= -Wno-unused-variable -Wno-unused-parameter -Wunused-but-set-variable

# Directories: #
INC_DIR:= -I.
#LIB_DIR:= ./

OBJ:= -lsched

all:test

#watchdog_prog
#watchdog_test
test:
	@$(CC) $(F_DEBUG) $(NAME_P).c $(NAME).c scheduler.c $(INC_DIR) -o $(NAME_P)  -pthread
	@$(CC) $(F_DEBUG) $(NAME)_$@.c $(NAME).c scheduler.c $(INC_DIR) -o a.out  -pthread
	@./a.out

# Room Service #
clean:
	@rm -f *.out *.o *.so