# Convenience wrapper around the CMake build. See CMakePresets.json for the
# debug/release/asan presets; all artifacts land in build/<preset>/.
PRESET ?= release

SOURCES := $(wildcard src/*.cpp) $(wildcard include/*.h) $(wildcard tests/*.cpp)

.PHONY: all build test run sanitize format format-check lint install clean

all: build

build:
	cmake --preset $(PRESET)
	cmake --build --preset $(PRESET)

test: build
	ctest --preset $(PRESET)

run: build
	./build/$(PRESET)/garbage 2 10 true

sanitize:
	cmake --preset asan
	cmake --build --preset asan
	ctest --preset asan

format:
	clang-format -i $(SOURCES)

format-check:
	clang-format --dry-run --Werror $(SOURCES)

lint: build
	clang-tidy -p build/$(PRESET) $(wildcard src/*.cpp)

install: build
	cmake --install build/$(PRESET)

clean:
	rm -rf build
