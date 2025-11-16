CC = gcc
CFLAGS = -std=c11 -Wpedantic -Wall -Wextra -fsanitize=undefined,address -g #-DDEBUG
LDLIBS=-lm
RM = rm -f
OBJ = Exo2.o matrice.o image.o
EXE = prog

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)

Exo2.o: Exo2.c matrice.h image.h
	$(CC) $(CFLAGS) -c Exo2.c

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c matrice.c

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c

clean:
	$(RM) $(OBJ) $(EXE) chien2.pgm feep2.pgm
