##all:
##	gcc -Wall main.c -o main `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
#benoit:
#	gcc -Wall test.c -o menu `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
#toto:
#gcc -Wall new.c -o new `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

# Simple SDL mini code
CC = gcc
CPPFLAGS = `pkg-config --cflags sdl`
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS = -Wall -Wextra  -Werror -O2 -std=c99 -O3 -pedantic
LDLIBS = `pkg-config --libs sdl` -lSDL_image
LDFLAGS= -lm
SRC = new.c

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) $(GTK_CFLAGS) $(LDLIBS) $(LDFLAGS) -o new
clean: 
	rm -rf *.o *~

