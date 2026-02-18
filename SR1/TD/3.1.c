#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_BLOC 512

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage : %s [fichier source] [fichier destination]\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  int Src, Dest;
  int NbLus = 0, NbEcris = 0;
  char Bloc[TAILLE_BLOC];

  Src = open(argv[1], O_RDONLY);
  if (Src == -1) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  Dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IRGRP);
  if (Dest == -1) {
    perror(argv[2]);
    close(Src);
    exit(EXIT_FAILURE);
  }

  while ((NbEcris == NbLus) && (NbLus = read(Src, Bloc, sizeof(Bloc)) > 0))
    NbEcris = write(Dest, Bloc, NbLus);

  int ExitStatus = 0;
  if (NbLus < 0) {
    perror(argv[1]);
    ExitStatus = 4;
  } else if ((NbEcris < 0) || (NbEcris < NbLus)) {
    if (NbEcris < 0)
      perror(argv[2]);
    else
      fprintf(stderr, "Erreur : Ecriture interrompue dans %s ! \n", argv[2]);
    ExitStatus = 5;
  }

  close(Src);
  if (close(Dest) == -1) {
    perror(argv[2]);
  }

  exit(EXIT_SUCCESS);
}
