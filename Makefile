CXX ?= g++
CXXFLAGS ?= -Wall -Werror -Wextra -pedantic -std=c++26 -g
DEPFLAGS = -MMD -MP

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEP)

.PHONY: clean

clean:
	rm -f main $(OBJ) $(DEP)