
#include "makehelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void assign(char* to, char* from)
{
    int i = 0;
    while (i < (int)strlen(from)) {
        *(to + i) = *(from + i);
        ++i;
    }
}
void printHello() {
  printf("makecreate a tool to create a simple Makefile\n\noptions : "
         "\n\t-o\tName of programe\n\t-L\tlanguage "
         "(c/cpp)\n\t-s\tSourcefiles\n\t-i\tHeader "
         "files\n\t-l\tLibrary files\n\t-f\tCompiler flags\n\t-F\tLinker "
         "flags\n\t-c\tCompiler\n\t-m\tModify current "
         "Makefile\n\t-a\tAdd\n\t-r\tRemove\n\t-u\tAutoditect\n\t-h\tShow "
         "this message\n\n");

}

int main(int argc, char *argv[]) {
  val v, w;
  memset(&v, 0, sizeof(val));
  memset(&w, 0, sizeof(val));
  /*	memset(v.MAIN,0,80);
          memset(w.MAIN,0,80);
          memset(v.SRCS,0,3000);
          memset(v.INCLUDES,0,300);
          memset(v.LIBS,0,300);
          memset(v.CFLAGS,0,300);
          memset(v.LFLAGS,0,300);
          memset(v.CC,0,80);*/
  /*
   *assign(v.MAIN, "");
   *assign(v.SRCS, "");
   *assign(v.INCLUDES, "");
   *assign(v.LIBS, "");
   *assign(v.CFLAGS, "");
   *assign(v.LFLAGS, "");
   *assign(v.CC, "");
   *assign(w.MAIN, "");
   *assign(w.SRCS, "");
   *assign(w.INCLUDES, "");
   *assign(w.LIBS, "");
   *assign(w.CFLAGS, "");
   *assign(w.LFLAGS, "");
   *assign(w.CC, "");
   */
  short help = 0;
  short modify = 0;
  short add = 0;
  short remove = 0;
  short au = 0;
  short lang = 0; // 0=C , 1=cpp
  assign(v.EXT,".c");
  short ch;
  while ((ch = getopt(argc, argv, ":o:s:i:l:f:F:c:L:hmaru")) != -1) {
    switch (ch) {
    case 'o':
      assign(v.MAIN, optarg);
      break;
    case 's':
      strcat(v.SRCS, optarg);
      break;
    case 'i':
      strcat(v.INCLUDES, optarg);
      break;
    case 'l':
      strcat(v.LIBS, optarg);
      break;
    case 'f':
      strcat(v.CFLAGS, optarg);
      break;
    case 'F':
      strcat(v.LFLAGS, optarg);
      break;
    case 'c':
      assign(v.CC, optarg);
      break;
    case 'h':
      help = 1;
      break;
    case 'm':
      modify = 1;
      break;
    case 'a':
      add = 1;
      break;
    case 'r':
      remove = 1;
      break;
    case 'u':
      au = 1;
      break;
    case 'L':
      if (!strcmp(optarg, "c") || !strcmp(optarg, "C")) {
        assign(v.EXT, ".c");
        lang = 0;
      } else if (!strcmp(optarg, "cpp") || !strcmp(optarg, "CPP")) {
        assign(v.EXT, ".cpp");
        lang = 1;
      }
      break;
    case ':':
      printf("some arguments are missing\n");
      help = 1;
      break;
    case '?':
      printf("Unknown option %c", optopt);
    }
  }
  argc -= optind;
  argv += optind;
  if (au) {
      findfiles(v.SRCS,v.EXT);
    /*
     *if (lang == 0)
     *  findfiles(v.SRCS, ".c");
     *else if (lang == 1) {
     *  findfiles(v.SRCS, ".cpp");
     *  findfiles(v.SRCS, ".cc");
     *  findfiles(v.SRCS".cxx");
     *}
     */
    //	findfiles(INCLUDES,".h");
    //	findfiles(LIBS,".so");
  }

  if (strlen(v.SRCS) == 0 && modify == 0)
    help = 1;
  if (help) {
    printHello();
    if (!strlen(v.SRCS))
      puts("Error : Source files not found");
    return 0;
  }
  if (modify == 0) {
    if (!strcmp(v.MAIN, ""))
      assign(v.MAIN, "out");
    if (!strcmp(v.CFLAGS, "")){
      assign(v.CFLAGS, "-Wall -O0 -gdwarf-4 -Wextra -pedantic-errors");
        if(lang == 1)
            strcat(v.CFLAGS," -Weffc++ -std=c++17");
    }
    if (!strcmp(v.CC, "")) {
      if (lang == 0) {
        assign(v.CC, "clang");
      } else if (lang == 1) {
        assign(v.CC, "clang++");
      }
    }
    create_new(v);
  } else {
    //		puts("1");
    char flag = 'k';
    if (add == 1)
      flag = 'a';
    else if (remove == 1)
      flag = 'r';
    //		puts("2");
    readMakefile(&w);
    //		puts("3");
    //		printf("%s\n%s\n%s\n%s\n",w.MAIN,w.INCLUDES,w.CC,w.CFLAGS);
    edit(&w, &v, flag);
    create_new(w);
    //		puts("4");
  }
  return 0;
}
