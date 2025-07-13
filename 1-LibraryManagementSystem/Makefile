# Makefile for Library Management System

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
INCLUDES = -Iinclude

# Source and object files
SRCS = src/Book.cpp \
       src/Library.cpp \
       src/Student.cpp \
       src/Utils.cpp \
       src/Admin.cpp \
       src/main.cpp

TARGET = build/libraryApp

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

# Run the app
run: $(TARGET)
	./$(TARGET)

# Clean compiled files
clean:
	rm -f $(TARGET)
