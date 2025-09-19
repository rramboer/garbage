CXX ?= g++
CXXFLAGS ?= -Wall -Werror -Wextra -pedantic -std=c++26 -g -Iinclude
DEPFLAGS = -MMD -MP

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC))
DEP := $(OBJ:.o=.d)

all: main


main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^


build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

build:
	@mkdir -p build

-include $(DEP)

.PHONY: clean

clean:
	rm -rf build