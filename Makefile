export CC = gcc

# Speed:
# export CFLAGS= -O3 -minline-all-stringops -Wno-unused-value -Wall -I$(SRCDIR)
# Plain compiling:
export CFLAGS= -Wno-unused-value -Wall -I$(SRCDIR)

export SRCDIR = src
# Bunch up all cpp files
SRC = $(wildcard $(SRCDIR)/Tree/*cpp)

export OBJDIR = obj
# Place object files in an object directory
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

# Output name of our static library
LIB = ./lib/lib7days.a

export EXAMPLEDIR = examples
_EXAMPLES = startup
EXAMPLES = $(patsubst %,$(EXAMPLEDIR)/%,$(_EXAMPLES))

.PHONY: all clean lib remake examples

all: lib examples

# Recursively call make all in the examples directories
examples:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) all)

lib: $(LIB)

$(LIB): $(OBJ)
	ar -rcs $(LIB) $(OBJ)

$(OBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(foreach path,$(EXAMPLES),cd $(path) && $(MAKE) $@)
	rm $(OBJDIR)/* $(LIB) -rf

remake: clean all

