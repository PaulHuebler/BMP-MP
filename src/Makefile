IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)
PACKAGE = `pkg-config --cflags --libs gtk+-3.0`

LIBS=

_DEPS = bitmap.h manipulations.h window.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = bitmap.o image.o manipulations.o
OBJ = $(patsubst %,%,$(_OBJ))

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PACKAGE)

bmp-mp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core $(INCDIR)/*~ bmp-mp
