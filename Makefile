CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=-lSDL2 -lm

STB=stb/stb_image.c stb/stb_image_write.c
NSIVP=sivpbase.c arrayutils.c vectors.c example.c $(STB)
NSIVPOBJ=$(NSIVP:.c=.o)
NSIVPOBJPATH=$(subst stb/, $(empty), $(NSIVPOBJ))


output: $(NSIVPOBJ)
		$(CC) $(CFLAGS) $(NSIVPOBJPATH) -o $@ $(LIBS)
	


%.o:	%.c
		$(CC) $(CFLAGS) -c $<





clean	:
		rm -rf *.o *.out output