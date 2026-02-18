#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open(argv[1], O_RDONLY);
  off_t position = lseek(fd, atoi(argv[2]) * sizeof(int), SEEK_SET);
  read(fd, &position, sizeof(int));
  return position;
}
