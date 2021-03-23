# Makefile for Assignment 1 CSC3022F 2021
# Author: WNGJIA001

# variable definition
CC=g++         # the compiler
BIN=bin/
SRC=src/
BUILD=build/
CFLAGS = -c -Wall -Iinclude

# link object files Tags.o Menu.o TagDriver.o to create executable file TagDriver.exe
TagDriver.exe: $(BIN) Tags.o Menu.o TagDriver.o
	$(CC) $(BIN) Tags.o Menu.o TagDriver.o -o $(BUILD) TagDriver.exe -std=c++2a

# compile source file Tags.cpp to create object file Tags.o 
Tags.o: $(SRC) Tags.cpp 
	$(CC) $(CFLAGS) $(SRC) Tags.cpp -o $(BIN) Tags.o -std=c++2a

# compile source file Menu.cpp to create object file Menu.o 
Menu.o: $(SRC) Menu.cpp 
	$(CC) $(CFLAGS) $(SRC) Menu.cpp -o $(BIN) Menu.o -std=c++2a

# compile source file TagDriver.cpp to create object file TagDriver.o 
TagDriver.o: $(SRC) TagDriver.cpp
	$(CC) $(CFLAGS) $(SRC) TagDriver.cpp -o $(BIN) TagDriver.o -std=c++2a

# deletes all the object code files
clean:
	rm $(BIN) *
	rm $(BUILD) *
