#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>

int strcomp(char string1[], char string2[]) {
  int i = 0;
  while (string1[i] != '\0' && string2[i] != '\0') {
    string1[i] = string2[i];
    i++;
  }
  return 1;
}

int main(void) {
  if (getenv("LOGNAME") != NULL) {
    char logname[128] = "0";
    int l = strcomp(logname, getenv("LOGNAME"));
    printf("l = %d", l);
    write(1, logname, l);
    write(1, "\n", 1);
  }
  exit(0);
}
