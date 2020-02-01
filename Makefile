CC=gcc -std=c99
FLAGS=`sdl2-config --cflags` -Wall -Wextra
CFLAGS=`sdl-config --libs` -lSDL_image


output	:	*.o *.h
		$(CC) $(FLAGS) $(CFLAGS) $< -o $@

*.o:	*.c
		$(CC) $(FLAGS) -c $<

clean	:
		rm -rf *.o *.out output