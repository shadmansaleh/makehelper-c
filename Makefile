MAIN = makehelper
SRCS = main.c modify.c makenew.c strfr.c autofind.c find.c readMakefile.c 
INCLUDES = 
LIBS = 
CFLAGS = -Wall -Wextra -pedantic-errors -O3
LFLAGS = 
CC = clang
OBJS = $(SRCS:.c=.o)

#End of variables

.PHONY: depend clean
all:	$(MAIN)
	@echo  $(MAIN) has been compiled
$(MAIN):	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
clean:
	$(RM) *.o *~ $(MAIN)
run :	$(MAIN)
	./$(MAIN)
install :	$(MAIN)
	cp $(MAIN) $(PREFIX)/local/bin
uninstall :	$(PREFIX)/local/bin/$(MAIN)
	rm -i $(PREFIX)/local/bin/$(MAIN)
depend:	$(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

