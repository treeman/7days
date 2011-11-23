export CC = gcc

export CFLAGS = -Wno-unused-value -Wall -I./src -I../../src/

export LIBS = -L../../lib -l7days -lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread\
 -lsfml-graphics-s -lsfml-audio -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC = $(wildcard src/*cpp)
export OBJDIR = obj
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

EXE = bin/startme
DEBUG_EXE = bin/startme-debug

.PHONY: all clean remake debug

all: $(SRC) $(EXE)

debug: $(SRC) $(DEBUG_EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(DEBUG_EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) -pg

$(OBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(EXE) $(DEBUG_EXE) $(OBJDIR)/* -rf

remake: clean all

