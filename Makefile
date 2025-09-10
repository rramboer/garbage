CXX ?= g++
CXXFLAGS ?= -Wall -Werror -Wextra -pedantic -std=c++23 -g

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f main $(OBJ)