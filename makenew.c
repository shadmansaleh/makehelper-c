#include <stdio.h>
#include "makehelper.h"

void create_new(val v){
	FILE *make=fopen("Makefile","w");
	fprintf(make,"MAIN = %s\n"\
            "SRCS = %s\nINCLUDES = %s\n"\
            "LIBS = %s\n"\
            "CFLAGS = %s\n"\
            "LFLAGS = %s\n"\
            "CC = %s\n"\
            "OBJS = $(SRCS:%s=.o)\n"\
            "\n"\
            "#End of variables\n"\
            "\n"\
            "",v.MAIN,v.SRCS,v.INCLUDES,v.LIBS,v.CFLAGS,v.LFLAGS,v.CC,v.EXT);
	fprintf(make,".PHONY: depend clean\n"\
            "all:\t$(MAIN)\n"\
               "\t@echo  $(MAIN) has been compiled\n"\
            "$(MAIN):\t$(OBJS)\n"\
                "\t$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)\n"\
            "%s.o:\n"\
                "\t$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@\n"\
            "clean:\n"\
                "\t$(RM) *.o *~ $(MAIN)\n"\
            "run :\t$(MAIN)\n"\
                "\t./$(MAIN)\n"\
            "install :\t$(MAIN)\n"\
                "\tcp $(MAIN) $(PREFIX)/local/bin\n"\
            "uninstall :\t$(PREFIX)/local/bin/$(MAIN)\n"\
                "\trm -i $(PREFIX)/local/bin/$(MAIN)\n"\
            "depend:\t$(SRCS)\n"\
                "\tmakedepend $(INCLUDES) $^\n"\
            "\n"\
            "# DO NOT DELETE THIS LINE -- make depend needs it\n"\
            "\n"\
           "",v.EXT);
	fclose(make);
	return;
}
