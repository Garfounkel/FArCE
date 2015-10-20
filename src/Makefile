## Simple SDL mini code

CC=clang

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= ViolaJones/haar.c ViolaJones/integral_image.c ViolaJones/pixel_operations.c ViolaJones/Ulong_tab.c ViolaJones/Haar_type.c main.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -fr *~ *.o
	rm -fr ViolaJones/*~ ViolaJones/*.o
	rm -f main
# END
