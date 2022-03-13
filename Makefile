# Compiler flags

CC := g++
CXXFLAGS += -Wall -g -Werror -pedantic #-Wextra

# Additions for WxWidgets

CXXFLAGS += `wx-config --cxxflags`
LDLIBS += `wx-config --libs`

.PHONY: clean clear try

# Executables and target management

T := tests/
S := src/
O := out/
EXE := $(O)test.out $(O)othello.out

# Explicit rules

%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS)

%.out:
	$(CC) $^ -o $@ $(LDLIBS)

# Compilation links

all: ${EXE}

$(S)grid.o: $(S)grid.cpp $(S)grid.h
$(S)game.o: $(S)game.cpp $(S)game.h $(S)grid.h
$(T)test.o: $(T)test.cpp $(S)game.h $(S)grid.h
$(S)othello.o: $(S)othello.cpp $(S)othello.h $(S)window.h
$(S)window.o: $(S)window.cpp $(S)window.h $(S)game.h $(S)grid.h

$(O)test.out: $(T)test.o $(S)grid.o $(S)game.o
$(O)othello.out: $(S)othello.o $(S)game.o $(S)grid.o $(S)window.o

# Utils

clean:
	rm -f */*.o

test: $(O)othello.out
	./$<

clear: clean
	rm -f $(EXE)
