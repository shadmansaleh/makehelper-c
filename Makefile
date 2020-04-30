MAIN = makehelper
SRCS =   ./main.c ./makenew.c ./autofind.c
INCLUDES =  
LIBS =  
CFLAGS = -Wall -O2
LFLAGS = 
CC = gcc
OBJS = $(SRCS:.c=.o)
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

