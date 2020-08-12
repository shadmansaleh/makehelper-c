#include <stdio.h>
#include "makehelper.h"

void create_new(val v){
	FILE *make=fopen("Makefile","w");
	fprintf(make,"MAIN = %s\nSRCS = %s\nINCLUDES = %s\nLIBS = %s\nCFLAGS = %s\nLFLAGS = %s\nCC = %s\nOBJS = $(SRCS:%s=.o)\n\n#End of variables\n\n",v.MAIN,v.SRCS,v.INCLUDES,v.LIBS,v.CFLAGS,v.LFLAGS,v.CC,v.EXT);
	fprintf(make,".PHONY: depend clean\nall:\t$(MAIN)\n\t@echo  $(MAIN) has been compiled\n$(MAIN):\t$(OBJS)\n\t$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)\n%s.o:\n\t$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@\nclean:\n\t$(RM) *.o *~ $(MAIN)\nrun :\t$(MAIN)\n\t./$(MAIN)\ndepend:\t$(SRCS)\n\tmakedepend $(INCLUDES) $^\n\n# DO NOT DELETE THIS LINE -- make depend needs it\n\n",v.EXT);
	fclose(make);
	return;
}
