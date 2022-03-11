# Compiler flags

CC := g++
CXXFLAGS += -Wall -g -Werror -Wextra -pedantic

# Additions for WxWidgets

CXXFLAGS += `wx-config --cxxflags`
LDLIBS += `wx-config --libs`

.PHONY: clean clear try

# Executables and target management

T := tests/
S := src/
O := out/
EXE := test.out

# Explicit rules

%.o: %.cpp
	$(CC) -c $< $(CXXFLAGS)

%.out:
	$(CC) $(notdir $^) -o $(O)$@ $(CXXFLAGS)

# Compilation links

all: ${EXE}

$(S)grid.o: $(S)grid.cpp $(S)grid.h
$(S)game.o: $(S)game.cpp $(S)game.h $(S)grid.h
$(T)test.o: $(T)test.cpp $(S)game.h $(S)grid.h

test.out: $(T)test.o $(S)grid.o $(S)game.o

# Utils

clear:
	rm -f *.o

try: test
	./$(O)/test.out

clean: clear
	rm -f $(O)${EXE}
