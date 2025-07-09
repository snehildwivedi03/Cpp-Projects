# Makefile for Library Management System

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Source files and output binary
SRC = src/Book.cpp src/Library.cpp src/Student.cpp src/main.cpp
TARGET = build/libraryApp

SRC = src/Book.cpp src/Library.cpp src/Student.cpp src/Utils.cpp src/main.cpp


# Default target
all: $(TARGET)

# How to build the final program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run the app
run: $(TARGET)
	./$(TARGET)

# Clean the compiled binary
clean:
	rm -f $(TARGET)
