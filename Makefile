CC=gcc -std=c99
FLAGS=-lSDL2 -lSDL2_image -Wall -Wextra -g

FILES=sivpbase.c arrayutils.c
FILESOBJ=$(FILES:.c=.o)
FILESHEAD=$(FILES:.c=.h)




output	:	$(FILES) $(FILESHEAD)
		$(CC) $(FLAGS) $^ -o $@

%.o:	%.c $(FILESHEAD)
		$(CC) $(FLAGS) -c $<




clean	:
		rm -rf *.o *.out output