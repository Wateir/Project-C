#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int input = open(argv[3], O_RDONLY);
  int output = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if ((input == -1) || (output == -1)) {
    perror("file");
    exit(EXIT_FAILURE);
  }

  if (dup2(input, STDIN_FILENO) == -1) {
    close(input);
    close(output);
    perror("Redirect STDIN");
    exit(EXIT_FAILURE);
  }
  if (dup2(output, STDOUT_FILENO) == -1) {
    close(input);
    close(output);
    perror("Redirect STDOUT");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  switch (pid) {
  case -1:
    perror("fork");
    close(input);
    close(output);
    exit(EXIT_FAILURE);
  case 0:
    execlp(argv[1], argv[1], NULL);
    close(input);
    close(output);
    exit(EXIT_FAILURE);
  }
  wait(NULL);
  close(input);
  close(output);
  exit(EXIT_SUCCESS);
}
