CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
BUILD    := build
TARGETS  := $(BUILD)/MenuTestDrive $(BUILD)/MenuTestDrive2 $(BUILD)/StlIterationDemo

all: $(TARGETS)

$(BUILD)/%: %.cpp $(wildcard *.h) | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: all
	@for t in $(TARGETS); do ./$$t; done

clean:
	rm -rf $(BUILD)

.PHONY: all run clean
