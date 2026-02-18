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
    execlp("ls", "ls", "-al", NULL);
    perror("ls");
    exit(EXIT_SUCCESS);
  }
  wait(NULL);
  execlp("date", "date", NULL);

  exit(EXIT_SUCCESS);
}
