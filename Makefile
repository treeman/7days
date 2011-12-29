export CC = gcc

# Speed:
# export CFLAGS= -O3 -minline-all-stringops -Wno-unused-value -Wall -I$(_SRCDIR)
# Plain compiling:
export CFLAGS= -Wno-unused-value -Wall -I$(_SRCDIR)

export LIBDIR = lib
export SRCDIR = src

export DESTDIR = /usr/local
export DESTINCDIR = $(DESTDIR)/include
export DESTLIBDIR = $(DESTDIR)/lib

export LIBNAME = lib7days.a

# We have our sources inside a subfolder for cleanliness
SUBSRCDIR = Tree
_SRCDIR = $(SRCDIR)/$(SUBSRCDIR)

# All buildable source files
SRC = $(wildcard $(_SRCDIR)/*cpp)

# Name of main include file which is outside our source subfolder
MAININC = Tree.hpp

HEADERS = $(wildcard $(_SRCDIR)/*hpp)

export OBJDIR = obj
# Place object files in an object directory
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

# Output for our static library
LIBOUT = $(LIBDIR)/$(LIBNAME)

export EXAMPLEDIR = examples
_EXAMPLES = hello-world log-n-debug timers-n-random
EXAMPLES = $(patsubst %,$(EXAMPLEDIR)/%,$(_EXAMPLES))

.PHONY: all clean clean_examples dev examples install lib remake remake_all remake_examples uninstall

all: lib dev examples

# Recursively call make in the examples directories
examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) all; cd ../../;)

clean_examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) clean; cd ../../;)

remake_examples: clean_examples examples

# Construct a static library
lib: $(LIBOUT)

$(LIBOUT): .depend $(OBJ)
	ar -rcs $(LIBOUT) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

# Generate dependency information for all source files
.depend: $(SRC)
	@(rm -f ./.depend)
# Generate dependency information
	@($(CC) $(CFLAGS) -MM $^ >> ./.depend)
# Set correct directory for object files
	@(sed -i 's|\(^.*:\)|$(OBJDIR)/$(_SRCDIR)/\1|g' ./.depend)

install: lib
	@(mkdir -p $(DESTINCDIR)/$(SUBSRCDIR))
	@(mkdir -p $(DESTLIBDIR))
	cp $(LIBDIR)/* $(DESTLIBDIR)
# Install header files
	cp $(SRCDIR)/$(MAININC) $(DESTINCDIR)
	cp -r $(HEADERS) $(DESTINCDIR)/$(SUBSRCDIR)

uninstall:
	rm $(DESTLIBDIR)/$(LIBNAME)
	rm -r $(DESTINCDIR)/$(SUBSRCDIR) $(DESTINCDIR)/$(MAININC)

# Insert object file rules into Makefile so we can keep track of their dependencies
include .depend

# Dev configurations, done here so we get a clean separation from lib and dev
export DEVLIBS = -lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread\
 -lsfml-graphics-s -lsfml-audio -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

export DEVDIR = dev

export DEVSRCDIR = $(DEVDIR)/src
DEVSRC = $(wildcard $(DEVSRCDIR)/*cpp)

export DEVCFLAGS = $(CFLAGS) -I./$(DEVSRCDIR)

export DEVOBJDIR = $(DEVDIR)/obj
DEVOBJ = $(patsubst %,$(DEVOBJDIR)/%,$(DEVSRC:.cpp=.o))

DEVEXE = $(DEVDIR)/bin/startme

dev: $(DEVEXE)

# Dev exe depends on both dev specific and library files
$(DEVEXE): .depend dev/.depend $(OBJ) $(DEVOBJ)
	$(CC) $(OBJ) $(DEVOBJ) -o $@ $(DEVLIBS)

$(DEVOBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(DEVCFLAGS)

# Dependency information for dev specific files
dev/.depend: $(DEVSRC)
	@(rm -f ./dev/.depend)
	@($(CC) $(DEVCFLAGS) -MM $^ >> ./dev/.depend)
	@(sed -i 's|\(^.*:\)|$(DEVOBJDIR)/$(DEVSRCDIR)/\1|g' ./dev/.depend)

include dev/.depend

clean_dev:
	rm $(DEVOBJDIR)/* $(DEVEXE) dev/.depend -rf

clean: clean_dev clean_examples
	rm $(OBJDIR)/* $(LIBOUT) .depend -rf

remake: clean all

remake_all: remake remake_examples

