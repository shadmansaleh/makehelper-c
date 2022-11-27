#include "makehelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void readMakefile(val *v) {
  FILE *make = fopen("Makefile", "r");
  if (make == NULL) {
    printf("Old Makefile doesn't exist");
    return;
  }
  char buffer[250];
  memset(buffer, 0, sizeof(buffer));
  char *p;
  while ((fgets(buffer, 250, make))) {
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';
    if (strstr(buffer, "MAIN =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->MAIN, p, strlen(p));
    } else if (strstr(buffer, "SRCS =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->SRCS, p, strlen(p));
    } else if (strstr(buffer, "INCLUDES =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->INCLUDES, p, strlen(p));
    } else if (strstr(buffer, "LIBS =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->LIBS, p, strlen(p));
    } else if (strstr(buffer, "CFLAGS =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->CFLAGS, p, strlen(p));
    } else if (strstr(buffer, "LFLAGS =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->LFLAGS, p, strlen(p));
    } else if (strstr(buffer, "CC =")) {
      p = strchr(buffer, '=') + 2;
      memmove(v->CC, p, strlen(p));
      if (!strcmp(v->CC, "clang"))
        assign(v->EXT, ".c");
      else if (!strcmp(v->CC, "clang++"))
        assign(v->EXT, ".cpp");
    } else if (strstr(buffer, "End of variables")) {
      fclose(make);
      break;
    }

    memset(buffer, 0, sizeof(buffer));
  }
}
