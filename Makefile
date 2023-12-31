CC = gcc
# The weird BS is to link lncurses to the brew installed version, not the default
WEIRD_BS = -I/usr/local/opt/ncurses/include -L/usr/local/opt/ncurses/lib
CFLAGS = -lmenu -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
          $(SRCDIR)windows/*.c\
          $(SRCDIR)utils/*.c

all: rogue run clean

rogue: $(SOURCES)
	$(CC) $(SOURCES) $(WEIRD_BS) $(CFLAGS) -o $@

run:
	./rogue

clean:
	rm rogue
