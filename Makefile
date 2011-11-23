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
LIB = ./lib/lib7days.a

export EXAMPLEDIR = examples
_EXAMPLES = hello-world startup
EXAMPLES = $(patsubst %,$(EXAMPLEDIR)/%,$(_EXAMPLES))

.PHONY: all clean lib remake examples

all: lib

# Recursively call make in the examples directories
examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) all; cd ../../;)

clean_examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) clean; cd ../../;)

remake_examples: clean_examples examples

# Construct a static library
lib: $(LIB)

$(LIB): .depend $(OBJ)
	ar -rcs $(LIB) $(OBJ)

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

clean:
	rm $(OBJDIR)/* $(LIB) -rf

remake: clean all

remake_all: remake remake_examples

