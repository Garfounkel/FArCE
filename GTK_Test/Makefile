#
# Variables:
#
CC = gcc
BIN = nom_prog
SRC = main.c
OBJ = main.o

#
# Flags d'erreurs:
#
ERROR_CFLAGS = -Wall -W -pedantic


#
# Flags pour le compilateur:
#
GLIB_CFLAGS = $$(pkg-config --cflags glib-2.0)
PANGO_CFLAGS = $$(pkg-config --cflags pango)
GTK_[C\LD]FLAGS = $$(pkg-config --cflags gtk+-2.0)

CFLAGS = $(ERROR_FLAGS) $(GLIB_CFLAGS) $(PANGO_CFLAGS) $(GTK_CFLAGS)


#
# Flags pour l'editeur de liens:
#
GLIB_LDFLAGS = $$(pkg-config --libs glib-2.0)
PANGO_LDFLAGS = $$(pkg-config --libs pango)
GTK_LDFLAGS = $$(pkg-config --libs gtk+-2.0)

LDFLAGS = $(ERROR_FLAGS) $(GLIB_LDFLAGS) $(PANGO_LDFLAGS) $(GTK_LDFLAGS)


#
# Construction du programme:
#
all: $(BIN) gtktest

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) -o $@ -c $< $(LDFLAGS)  

#
# Nettoyage:
#
clean:
	rm -f *.o *~ core $(BIN)
	rm -f main
