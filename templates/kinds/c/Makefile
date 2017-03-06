
LIB=-lc
INCLUDE=-I`pwd`/include
C_FLAGS=-std=c11 -Wall
VERSION=readfile a dear friend

EXEC=__exec__
OBJECTS=src/main.c

BUILD_DIR=build


.PHONY: build test version docs tests

all: build

build: $(OBJECTS)
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) -E $?

clean:
	rm -rf $(BUILD_DIR)

test:

docs:

version:
	@ echo $(VERSION)
