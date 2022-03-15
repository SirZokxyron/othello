# Compiler flags

CC := g++
CXXFLAGS += -Wall -g -Werror -pedantic # -Wextra (prevents WxWidget compilation)

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

$(S)grid.o:      $(S)grid.cpp                                                $(S)grid.hpp
$(S)game.o:      $(S)game.cpp                                   $(S)game.hpp $(S)grid.hpp
$(T)test.o:      $(T)test.cpp                                   $(S)game.hpp $(S)grid.hpp
$(S)othello.o:   $(S)othello.cpp $(S)othello.hpp $(S)window.hpp
$(S)window.o:    $(S)window.cpp                  $(S)window.hpp $(S)game.hpp $(S)grid.hpp

$(O)test.out:    $(T)test.o                                     $(S)game.o   $(S)grid.o
$(O)othello.out: $(S)othello.o                   $(S)window.o   $(S)game.o   $(S)grid.o 

# Utils

clean:
	rm -f */*.o

try: $(O)test.out
	./$<

test: $(O)othello.out
	./$<

clear: clean
	rm -f $(EXE)
