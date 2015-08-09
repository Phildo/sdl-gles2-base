CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/src
BINDIR = $(CURDIR)/bin
OUTFILE = $(BINDIR)/dotest.out

CC = g++
DEBUGFLAGS = -ggdb3 -O0
DEBUGGER = gdb -q
CFLAGS = -Wall -std=c++11 `sdl2-config --cflags`
LFLAGS = -Wall `sdl2-config --libs` -lSDL2_image

PLATFORM_DEF=DO_PLATFORM_PC

HEADERS=$(wildcard $(SRCDIR)/*.h)
SOURCES=$(wildcard $(SRCDIR)/*.cpp)

b: build
	

define:
	@if sed -i .bak 's/DO_PLATFORM DO_PLATFORM_.*$$/DO_PLATFORM $(PLATFORM_DEF)/' $(SRCDIR)/defines.h; then rm $(SRCDIR)/defines.h.bak; fi

$(OUTFILE): define $(HEADERS) $(SOURCES)
	@$(CC) $(CFLAGS) $(LFLAGS) $(SOURCES) -o $(OUTFILE)

build: $(OUTFILE)
	@

run: $(OUTFILE)
	@$(OUTFILE)

$(OUTFILE).dSYM: $(HEADERS) $(SOURCES)
	@$(CC) $(DEBUGFLAGS) $(CFLAGS) $(LFLAGS) $(SOURCES) -o $(OUTFILE)

debug: $(OUTFILE).dSYM
	@$(DEBUGGER) $(OUTFILE)

clean:
	@for f in $(OUTFILE) $(OUTFILE).dSYM ; do if [ -d $$f ] ; then rm -r $$f ; elif [ -f $$f ] ; then rm $$f ; fi ; done

kill:
	@killAll $(OUTFILE)

