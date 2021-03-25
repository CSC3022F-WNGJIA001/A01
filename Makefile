# Makefile for Assignment 1 CSC3022F 2021
# Author: WNGJIA001

# variable definition
CC = g++
BINDIR = bin/
SRCDIR = src/
BUILDDIR = build/
CFLAGS = -c -Wall -Iinclude
rm = rm -f
# target and objects declaration
TARGET = $(BUILDDIR)TagDriver.exe
OBJECTS = $(BINDIR)Tags.o $(BINDIR)Menu.o $(BINDIR)TagDriver.o

# link object files Tags.o Menu.o TagDriver.o to create executable file TagDriver.exe
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ -std=c++2a
# compile source files to create object files
$(BINDIR)%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++2a

# run the executable file
run: $(TARGET)
	chmod 700 $(TARGET)
	./$(TARGET)

# remove all the object binary files and executable file
clean:
	$(rm) $(BINDIR)*.o $(BINDIR)*.txt
	$(rm) $(BUILDDIR)*.exe
