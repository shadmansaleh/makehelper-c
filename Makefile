MAIN=makehelper
SRCS= ./modify.c ./main.c ./makenew.c ./strfr.c ./autofind.c ./readMakefile.c
INCLUDES=
LIBS=
CFLAGS=-Wall -O0 -g 
LFLAGS=
CC=clang
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
depend:	$(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

