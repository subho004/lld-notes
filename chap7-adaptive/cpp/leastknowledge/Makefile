CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
BUILD    := build
TARGETS  := $(BUILD)/CarTestDrive

all: $(TARGETS)

$(BUILD)/%: %.cpp $(wildcard *.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: all
	@for t in $(TARGETS); do echo "== $$t"; ./$$t; done

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
