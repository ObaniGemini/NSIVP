CC=gcc
FLAGS=-lSDL2 -Wall -Wextra -g -lm

HEADERS=stb_image.h

FILES=sivpbase.c arrayutils.c
FILESOBJ=$(FILES:.c=.o)
FILESHEAD=$(FILES:.c=.h)




output	:	$(FILES) $(FILESHEAD) $(HEADERS)
		$(CC) $(FLAGS) $^ -o $@

%.o:	%.c
		$(CC) $(FLAGS) -c $<




clean	:
		rm -rf *.o *.out output