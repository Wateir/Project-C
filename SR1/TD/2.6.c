#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  pid_t process1 = fork();
  switch (process1) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    execlp("eza", "ls", "-l", NULL);
    perror("eza");
  default:
    wait(NULL);
    break;
  }

  pid_t process2 = fork();
  switch (process2) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    execlp("pwd", "pwd", NULL);
    perror("pwd");
  default:
    wait(NULL);
    break;
  }
  exit(EXIT_SUCCESS);
}
