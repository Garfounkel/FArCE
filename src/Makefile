## Simple SDL mini code

CC=clang

CPPFLAGS= `pkg-config --cflags sdl`
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -pedantic
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= SDL_operations/SDL_OPs.c ViolaJones/adaboost.c ViolaJones/haar.c ViolaJones/integral_image.c ViolaJones/pixel_operations.c ViolaJones/Ulong_tab.c ViolaJones/Haar_type.c Preprocessing/Image_OPs.c ViolaJones/cascade.c
OBJ= ${SRC:.c=.o}

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) main.c $(GTK_CFLAGS) $(LDLIBS) $(LDFLAGS) -o main

main:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) main.c $(GTK_CFLAGS) $(LDLIBS) $(LDFLAGS) -o main

graphical:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) new.c $(GTK_CFLAGS) $(LDLIBS) $(LDFLAGS) -o graphical

clean:
	rm -fr *~ *.o
	rm -fr SDL_operations/*~ SDL_operations/*.o
	rm -fr ViolaJones/*~ ViolaJones/*.o
	rm -fr Preprocessing/*~ Preprocessing/*.o
	rm -f main
# END
