UNAME_S = $(shell uname -s)

SHELL = /bin/sh

CC = gcc
CFLAGS = -std=c11 -g -Wall
CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include -Ilib/stb -Ilib/noise -Ilib/glfw/deps -Isrc

#glfw contains glad2 so therefore to use it remove glad.o as that is the glad library, causes linker errors
#LDFLAGS +=  lib/cglm/build/libcglm.a lib/glfw/build/src/libglfw3.a lib/noise/libnoise.a -lm
LDFLAGS +=  lib/glad/src/glad.o lib/cglm/build/libcglm.a lib/glfw/build/src/libglfw3.a lib/noise/libnoise.a -lm

LDFLAGS +=  -lgdi32 -lopengl32
HOME = C:/Users/mater/OneDrive/Documents/3DGameInCUsingOpenGL

#lib/glad/src/glad.o lib/cglm/.libs/libcglm.a lib/glfw/src/libglfw3.a

SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c) 
OBJ = $(SRC:.c=.o)
BIN = build/Win_Build

.PHONY: all clean

all: dirs libs game

libs:

	echo $(SHELL); echo "YEet"
#	echo $(PATH)
	echo $(HOME)
	
	cd lib/cglm && cmake -S . -B build -DCGLM_STATIC=ON && cd build && make
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	cd lib/glfw && cmake -S . -B build && cd build && mingw32-make
	cd lib/noise && mingw32-make

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/game

game: $(OBJ)
#	echo "SECOND YEET"
	$(CC) -o $(BIN)/game $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)