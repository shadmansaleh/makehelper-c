
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
  printf("makehelper [OPTIONS]...\n"
          "makehelper a tool to create a simple Makefiles \nfor small c / cpp projects.\n(Version 1.0)\n\noptions : "
         "\n\t-o\tName of programe\n\t-L\tlanguage "
         "(c/cpp)\n\t-s\tSourcefiles\n\t-i\tHeader "
         "files\n\t-l\tLibrary files\n\t-f\tCompiler flags\n\t-F\tLinker "
         "flags\n\t-c\tCompiler\n\t-m\tModify current "
         "Makefile\n\t-a\tAdd\n\t-r\tRemove\n\t-u\tAutoditect\n\t-h\tShow "
         "this message\n\n");

}

int main(int argc, char *argv[]) {
    val inputData, avalableData;
    memset(&inputData, 0, sizeof(val));
    memset(&avalableData, 0, sizeof(val));
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
    assign(inputData.EXT, ".c");
    short ch;
    while ((ch = getopt(argc, argv, ":o:s:i:l:f:F:c:L:hmaru")) != -1) {
        switch (ch) {
        case 'o':
            assign(inputData.MAIN, optarg);
            break;
        case 's':
            strcat(inputData.SRCS, optarg);
            break;
        case 'i':
            strcat(inputData.INCLUDES, optarg);
            break;
        case 'l':
            strcat(inputData.LIBS, optarg);
            break;
        case 'f':
            strcat(inputData.CFLAGS, optarg);
            break;
        case 'F':
            strcat(inputData.LFLAGS, optarg);
            break;
        case 'c':
            assign(inputData.CC, optarg);
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
                assign(inputData.EXT, ".c");
                lang = 0;
            } else if (!strcmp(optarg, "cpp") || !strcmp(optarg, "CPP")) {
                assign(inputData.EXT, ".cpp");
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
      findfiles(inputData.SRCS, inputData.EXT);
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

  if (strlen(inputData.SRCS) == 0 && modify == 0 && help==0)
  {
    printHello();
    if (!strlen(inputData.SRCS) && modify ==0)
        puts("Error : Source files not found");
    return 0;
  }
  if (help) {
    printHello();
    return 0;
  }
  if (modify == 0) {
      if (!strcmp(inputData.MAIN, ""))
          assign(inputData.MAIN, "out");
      if (!strcmp(inputData.CFLAGS, "")) {
          assign(inputData.CFLAGS, "-Wall -O0 -gdwarf-4 -Wextra -pedantic-errors");
          if (lang == 1)
              strcat(inputData.CFLAGS, " -Weffc++ -std=c++17");
      }
      if (!strcmp(inputData.CC, "")) {
          if (lang == 0) {
              assign(inputData.CC, "clang");
          } else if (lang == 1) {
              assign(inputData.CC, "clang++");
          }

      }
      create_new(inputData);
  } else {
    //		puts("1");
    char flag = 'k';
    if (add == 1)
      flag = 'a';
    else if (remove == 1)
      flag = 'r';
    //		puts("2");
    readMakefile(&avalableData);
    //		puts("3");
    //		printf("%s\n%s\n%s\n%s\n",w.MAIN,w.INCLUDES,w.CC,w.CFLAGS);
    edit(&avalableData, &inputData, flag);
    create_new(avalableData);
    //		puts("4");
  }
  return 0;
}
