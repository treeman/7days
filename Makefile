export CC = gcc

# Speed:
# export CFLAGS= -O3 -minline-all-stringops -Wno-unused-value -Wall -I$(SRCDIR)
# Plain compiling:
export CFLAGS= -Wno-unused-value -Wall -I$(SRCDIR)

export SRCDIR = src/Tree
# Bunch up all cpp files
SRC = $(wildcard $(SRCDIR)/*cpp)

export OBJDIR = obj
# Place object files in an object directory
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

# Output name of our static library
OUTPUT = ./lib/lib7days.a

export EXAMPLEDIR = examples
_EXAMPLES = hello-world
EXAMPLES = $(patsubst %,$(EXAMPLEDIR)/%,$(_EXAMPLES))

.PHONY: all clean lib remake remake_all examples clean_examples remake_examples dev

all: lib dev examples

# Recursively call make in the examples directories
examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) all; cd ../../;)

clean_examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) clean; cd ../../;)

remake_examples: clean_examples examples

# Construct a static library
lib: $(OUTPUT)

$(OUTPUT): .depend $(OBJ)
	ar -rcs $(OUTPUT) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

# Generate dependency information for all source files
.depend: $(SRC)
	rm -f ./.depend
# Generate dependency information
	$(CC) $(CFLAGS) -MM $^ >> ./.depend
# Set correct directory for object files
	sed -i 's|\(^.*:\)|$(OBJDIR)/$(SRCDIR)/\1|g' ./.depend

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
	rm -f ./dev/.depend
	$(CC) $(DEVCFLAGS) -MM $^ >> ./dev/.depend
	sed -i 's|\(^.*:\)|$(DEVOBJDIR)/$(DEVSRCDIR)/\1|g' ./dev/.depend

include dev/.depend

clean_dev:
	rm $(DEVOBJDIR)/* $(DEVEXE) dev/.depend -rf

clean: clean_dev clean_examples
	rm $(OBJDIR)/* $(OUTPUT) .depend -rf

remake: clean all

remake_all: remake remake_examples

