#define _POSIX_C_SOURCE 200809L

#include "decoupe.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NBPARAMMAX 20

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    pid_t pid = fork();

    switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);

    case 0:
      printf("Je lance %s :\n", argv[i]);

      char *pCommand[NBPARAMMAX];
      Decoupe(argv[i], pCommand);
      execvp(pCommand[0], pCommand);

      exit(EXIT_SUCCESS);

    default:
      printf("J’ai délégué %s à %d. J’attends sa fin...\n", argv[i], pid);
      break;
    }
    wait(NULL);
    printf("%d terminé\n", pid);
  }
  exit(EXIT_SUCCESS);
}
