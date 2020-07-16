#include "makehelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int rL(int fd, char *data, int dsize);
void findfiles(char *OUT, char *PATERN) {
  pid_t pid;
  int pip[2];
  pipe(pip);
  char command[] = "find";
  char cond[20] = "*";
  char *arg[] = {"find", "-type", "f", "-name", strcat(cond, PATERN), NULL};
  if ((pid = fork()) == -1) {
    printf("Fork failed");
    exit(1);
  } else if (pid == 0) {
    // child process
    close(pip[0]);
    dup2(pip[1], 1);
    if (execvp(command, arg) == -1) {
      fprintf(stderr, "Execution faild");
      exit(1);
    }
  } else {
    //	parent
    close(pip[1]);
    char b[200];
    while (!rL(pip[0], b, 200)) {
      strcat(OUT, " ");
      strcat(OUT, b);
    }
    close(pip[0]);
  }
}

int rL(int fd, char *data, int dsize) {
  int i = 0;
  char chr;
  size_t s = 0;
  while (i < dsize) {
    s = read(fd, &chr, 1);
    if (chr == '\n' || chr == '\0' || s == -1 || s == 0) {
      break;
    }
    data[i] = chr;
    i++;
  }
  data[i] = '\0';
  if (s == 0 || s == -1)
    return -1;
  else
    return 0;
}
