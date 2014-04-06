# Hyde Makefile.


PROG	= hyde
SOURCES	= main.c jekyll.c hyde.c lanyon.c
########################################################################
LDFLAGS	= -lX11 -lncurses
CC		=gcc
CFLAGS	=-Wall
########################################################################
OBJECTS	=$(SOURCES:.c=.o)

all: $(SOURCES) $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	gcc $(CFLAGS) -c $< -o $@
clean:
	rm -f *~ $(OBJECTS) $(PROG)
