CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=-lSDL2 -lm

FILES=sivpbase.c arrayutils.c vectors.c
FILESOBJ=$(FILES:.c=.o)



output: $(FILESOBJ)
		$(CC) $(CFLAGS) $(FILESOBJ) -o $@ $(LIBS)
	


%.o:	%.c
		$(CC) $(CFLAGS) -c $<





clean	:
		rm -rf *.o *.out output