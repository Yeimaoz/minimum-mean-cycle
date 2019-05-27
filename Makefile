CC = gcc
CXX =g++
CXXFLAGS += -g -std=c++11 -Wall -Isrc/
VPATH = src:build
SRC ?= ./src
BUILD ?= ./build
TARGET ?= MMC

.PHONY: clean all

all: $(BUILD) $(TARGET)

$(BUILD)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILD):
	mkdir $@

$(TARGET): $(BUILD)/main.o $(BUILD)/parser.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) -rf $(BUILD) *.txt
