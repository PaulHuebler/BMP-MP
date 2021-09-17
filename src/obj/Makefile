IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)
PACKAGE = `pkg-config --cflags --libs gtk+-3.0`

ODIR=obj

LIBS=

_DEPS = bitmap.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = bitmap.o image.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PACKAGE)

bmp-mp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 