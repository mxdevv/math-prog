MAIN=main
CC=gcc
FLAGS=-O2
LIBS=-lm

GTK_FLAGS=`pkg-config --cflags gtk+-2.0`
GTK_LIBS=`pkg-config --libs gtk+-2.0`

all:
	$(CC) $(FLAGS) $(MAIN).c -o $(MAIN) $(LIBS)

gtk:
	$(CC) $(GTK_FLAGS) $(FLAGS) gtk.c -o gtk $(GTK_LIBS) $(LIBS)

clean:
	rm main gtk
