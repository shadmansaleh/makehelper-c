#include "makehelper.h"
#include <stdio.h>
#include <string.h>

void modify(char *m, char *mod, char flag) {
  char *s;
  char *k = mod;
  char *tok;
  tok = strtok(k, " ");
  if (flag == 'a') {
    //	tok=strtok(k," ");
    while (tok != NULL) {
      if (!strstr(m, tok)) {
        strcat(m, " ");
        strcat(m, tok);
      }
      //	printf(" %s %s ",tok,m);
      tok = strtok(NULL, " ");
      //			puts("stuck");
    }
  } else if (flag == 'r') {
    while (tok != NULL) {
      if (strstr(m, mod)) {
        s = strfr(m, tok, "");
        memset(m, 0, strlen(m));
        memmove(m, s, strlen(s));
        free(s);
      }
      printf(" %s |  %s \n", tok, m);
      tok = strtok(NULL, " ");
      //		puts("stuck");
    }
  }
}

void edit(val *v, val *w, char flag) {
  if (strcmp(w->SRCS, "")) {
    modify(v->SRCS, w->SRCS, flag);
    //	puts("changed SRCS");
  }
  if (strcmp(w->INCLUDES, "")) {
    modify(v->INCLUDES, w->INCLUDES, flag);
    //	 puts("changed INCLUDES");
  }
  if (strcmp(w->LIBS, "")) {
    modify(v->LIBS, w->LIBS, flag);
    //	 puts("changed LIBS");
  }
  if (strcmp(w->CFLAGS, "")) {
    modify(v->CFLAGS, w->CFLAGS, flag);
    //	 puts("changed CFLAGS");
  }
  if (strcmp(w->LFLAGS, "")) {
    modify(v->LFLAGS, w->LFLAGS, flag);
    //	 puts("changed LFLAGS");
  }
  if (strcmp(w->MAIN, "")) {
    modify(v->MAIN, w->MAIN, flag);
    //	 puts("changed MAIN");
  }
  if (strcmp(w->CC, "")) {
    modify(v->CC, w->CC, flag);
    //	 puts("changed CC");
  }
}
