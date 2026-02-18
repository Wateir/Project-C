#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void ShowInfo(void) {
  printf("pid : %d, pid parent : %d,\nuser grp : %d, user name : %s,\nid user "
         ": %d, id user group : %d\n",
         getpid(), getppid(), getpgrp(), getlogin(), getuid(), getgid());
}

int main(void) {
  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    printf("[Fils]  : \n");
    ShowInfo();
    exit(EXIT_SUCCESS);
  default:
    printf("[Père] : \n");
    ShowInfo();
    break;
  }
  int retour_fils;
  pid_t pid_fils = wait(&retour_fils);
  printf("[Père] mon fils %d est terminé avec le code %d.\n", pid_fils,
         WEXITSTATUS(retour_fils));
  exit(EXIT_SUCCESS);
}
