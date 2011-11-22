
export CC=gcc

export CFLAGS= -Wno-unused-value -Wall -I./ -I../../../src/

export LIBS=-L../../../lib -l7days -lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread\
 -lsfml-graphics-s -lsfml-audio -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC = $(wildcard *cpp)
export OBJDIR = obj
OBJ = $(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

EXE = ../bin/startme
DEBUG_EXE = ../bin/startme-debug

.PHONY: all clean remake mrproper debug

all: $(SRC) $(EXE)

debug: $(SRC) $(DEBUG_EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(DEBUG_EXE): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS) -pg

#.cpp.o:
	#$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: %.cpp
	@(mkdir -p $(@D))
	$(CC) -c -o $@ $< $(CFLAGS)

remake: clean all

clean:
	rm -rf $(EXE) $(OBJ) $(DEBUG_EXE)

mrproper: clean
	rm -rf $(OBJ)

