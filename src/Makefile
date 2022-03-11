CC := g++
CXXFLAGS :=-Wall -g -Werror -pedantic
EXE := test

all: ${EXE}

.PHONY: clean clear try

grid.o: grid.cpp grid.h

game.o: game.cpp game.h grid.h

test: test.o grid.o game.o

clear:
	rm -f *.o

try: test
	./test

clean: clear
	rm -f ${EXE}
