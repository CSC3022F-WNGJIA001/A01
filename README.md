# Assignment 1 CSC3022F, 2021

## Makefile

```sh
$ make clean
```
Removes binary object files and tag.txt from bin/ and executable file from build/

```sh
$ make
```
Compiles source files and store object files as bin/%.o
Links object files and store the executable file as build/TagDriver.exe

```sh
$ make run
```
Execute the executable file TagDriver.exe inside build/

## Source Files

### Menu.cpp
Menu contains functions to display the text menu and other messages based on the feedback from the event loop.

### Tags.cpp
Tags contains the TagStruct definition to store the data of tags; the vector of TagStructs is also defined in this file.
Tags source also define the functions to manipulate the data in the vector based on the user's command input.

### TagDriver.cpp
TagDriver source file contains the main() function to control the event loop.

## Code Structure
TagDriver uses functions from Menu to provide information for user and prompt for user input.
Based on user input, TagDriver then calls functions defined in Tags to process and manipulate data of the vector. 
