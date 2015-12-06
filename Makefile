CC =clang
CPPFLAGS = `pkg-config --cflags sdl`
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS = -Wall -Wextra  -Werror -O2 -std=c99 -O3 -pedantic
LDLIBS = `pkg-config --libs sdl` -lSDL_image
LDFLAGS= -lm
SRC = N_GTK/Try_Image_GTK/new.c src/yolo.c src/SDL_operations/SDL_OPs.c src/ViolaJones/adaboost.c src/ViolaJones/haar.c src/ViolaJones/integral_image.c src/ViolaJones/pixel_operations.c src/ViolaJones/Ulong_tab.c src/ViolaJones/Haar_type.c src/Preprocessing/Image_OPs.c src/ViolaJones/cascade.c

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) $(GTK_CFLAGS) $(LDLIBS) $(LDFLAGS) -o new
clean: 
	rm -rf *.o *~
