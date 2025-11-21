CC = gcc
CFLAGS = -std=c11 -Wpedantic -Wall -Wextra -fsanitize=undefined,address -g #-DDEBUG
LDLIBS=-lm
RM = rm -f
OBJ = Exo1.o matrice.o image.o ti.o
EXE = prog

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)

Exo1.o: Exo1.c matrice.h image.h ti.h
	$(CC) $(CFLAGS) -c Exo1.c

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c matrice.c

image.o: image.c image.h matrice.h
	$(CC) $(CFLAGS) -c image.c

ti.o: ti.c image.h
	$(CC) $(CFLAGS) -c ti.c

clean:
	$(RM) $(OBJ) $(EXE)
