#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "makehelper.h"

int main(int argc,char * argv[]){
	char *MAIN="out";
	char SRCS[3000]=" ";
	char INCLUDES[300]=" ";
	char LIBS[300]=" ";
	char *CFLAGS="-Wall -O2";
	char *LFLAGS="";
	char *CC="gcc";
	short help=0;
	short modify=0;
	short add=0;
	short remove=0;
	short au=0;
	short ch;
	while((ch=getopt(argc,argv,":n:s:i:l:f:F:c:hmaru"))!=-1){
		switch(ch){
			case 'n':
				MAIN=optarg;
				break;
			case 's':
				strcat(SRCS,optarg);
				break;
			case 'i':
				strcat(INCLUDES,optarg);
				break;
			case 'l':
				strcat(LIBS,optarg);
				break;
			case 'f':
				CFLAGS=optarg;
				break;
			case 'F':
				LFLAGS=optarg;
				break;
			case 'c':
				CC=optarg;
				break;
			case 'h':
				help=1;
				break;
			case 'm':
				modify=1;
				break;
			case 'a':
				add=1;
				break;
			case 'r':
				remove=1;
				break;
			case 'u':
				au=1;
				break;
			case ':':
				printf("some arguments are missing\n");
				help=1;
				break;
			case '?':
				printf("Unknown option %c",optopt);

		}	
	}
	argc-=optind;
	argv+=optind;
	if (au)	{
		findfiles(SRCS,".c");
	//	findfiles(INCLUDES,".h");
	//	findfiles(LIBS,".so");
	}

	if(strlen(SRCS)==0)	help=1;
	if(help){
		printf("makecreate a tool to create a simpke Makefile\n\noptions : \n\t-n\tName of programe\n\t-s\tSourcefiles\n\t-i\tHeader files\n\t-l\tLibrary files\n\t-f\tCompiler flags\n\t-F\tLinker flags\n\t-c\tCompiler\n\t-m\tModify current Makefile\n\t-a\tAdd\n\t-r\tRemove\n\t-u\tAutoditect\n\t-h\tShow this message\n\n");
		return 0;
	}

	if (modify==0){
		create_new(MAIN,SRCS,INCLUDES,LIBS,CFLAGS,LFLAGS,CC);
	}
	return 0;

}
