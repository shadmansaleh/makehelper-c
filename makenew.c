#include <stdio.h>
#include "makehelper.h"

void create_new(char * MAIN,char * SRCS,char * INCLUDES,char * LIBS,char * CFLAGS,char * LFLAGS,char * CC){
	FILE *make=fopen("Makefile","w");
	fprintf(make,"MAIN = %s\nSRCS = %s\nINCLUDES = %s\nLIBS = %s\nCFLAGS = %s\nLFLAGS = %s\nCC = %s\nOBJS = $(SRCS:.c=.o)\n",MAIN,SRCS,INCLUDES,LIBS,CFLAGS,LFLAGS,CC);
	fprintf(make,".PHONY: depend clean\nall:\t$(MAIN)\n\t@echo  $(MAIN) has been compiled\n$(MAIN):\t$(OBJS)\n\t$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)\n.c.o:\n\t$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@\nclean:\n\t$(RM) *.o *~ $(MAIN)\nrun :\t$(MAIN)\n\t./$(MAIN)\ndepend:\t$(SRCS)\n\tmakedepend $(INCLUDES) $^\n\n# DO NOT DELETE THIS LINE -- make depend needs it\n\n");
	fclose(make);
	return;
}
