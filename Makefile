IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
#LDIR =../lib

LIBS=-lm

_DEPS = ev3_all.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = lfoa.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lfoa: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
