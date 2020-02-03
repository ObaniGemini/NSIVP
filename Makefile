CC=gcc
FLAGS=-lSDL2 -Wall -Wextra -g -lm

HEADERS=stb_image.h

FILES=sivpbase.c arrayutils.c
FILESOBJ=$(FILES:.c=.o)
FILESHEAD=$(FILES:.c=.h)



output:    $(FILESOBJ) $(FILESHEAD) $(HEADERS)
	$(CC) $(FLAGS) -o $@ $(FILESOBJ)
	


%.o:	%.c
	$(CC) -c $< $(FLAGS)





clean	:
		rm -rf *.o *.out output