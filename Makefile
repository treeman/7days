export CC=gcc
# For speed add -O3 -minline-all-stringops
export CFLAGS=-c -Wno-unused-value -Wall -I./include/
export LIBS=-lX11 -lGL -lXrandr -lfreetype -lsndfile -lopenal -lpthread\
 -lsfml-graphics-s -lsfml-audio -lsfml-window-s -lsfml-system-s -lboost_iostreams -llua

SRC=\
include/Tree/Game.cpp \
include/Tree/Util.cpp \
include/Tree/InputHandler.cpp \
include/Tree/Graphics.cpp \
include/Tree/Butler.cpp \
include/Tree/Sprite.cpp \
include/Tree/Timer.cpp \
include/Tree/Logo.cpp \
include/Tree/Tweaks.cpp \
include/Tree/Loghelper.cpp \
include/Tree/Rect.cpp \
include/Tree/VisualDebug.cpp \
include/Tree/Console.cpp \
include/Tree/Settings.cpp \
include/Tree/WindowManager.cpp \
include/Tree/GameDebug.cpp \
include/Tree/DrawnLazy.cpp \
include/Tree/VisualObject.cpp \
include/Tree/PixFont.cpp \
include/Tree/PixMap.cpp

OBJ=$(SRC:.cpp=.o)
LIB=./lib/lib7days.a

.PHONY: all clean lib remake examples

all: lib examples

examples:
	@(cd ./examples && $(MAKE) all)

lib: $(LIB)

$(LIB): $(OBJ)
	ar -rcs $(LIB) $(OBJ)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	@(cd ./examples && $(MAKE) $@)
	rm $(OBJ) $(LIB)

remake: clean all

