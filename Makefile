CC = gcc
CXX = g++
CXXFLAGS += -g -std=c++11 -Wall -Isrc/
VPATH = src:build
SRC ?= ./src
BUILD ?= ./build
TARGET ?= Lab1

CASE ?= testcase/test.in

.PHONY: clean all test

all: $(BUILD) $(TARGET)

$(BUILD)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(BUILD):
	mkdir $@

$(TARGET): $(BUILD)/main.o $(BUILD)/parser.o $(BUILD)/Graph.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TARGET)
	./$(TARGET) $(CASE)

clean:
	$(RM) -rf $(TARGET) $(BUILD) *.txt 
