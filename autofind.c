#include "makehelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void findfiles(char *OUT, char *PATERN) {
  char *files = getFiles(".", PATERN, 0);
  strcpy(OUT, files);
  free(files);
  return;
}
