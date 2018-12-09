MAIN=main
CC=gcc
FLAGS=-O2
LIBS=-lm
all:
	$(CC) $(FLAGS) $(MAIN).c -o $(MAIN) $(LIBS)
