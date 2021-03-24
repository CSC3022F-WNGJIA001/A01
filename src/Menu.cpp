/**
* Menu.cpp to display menu to the output console
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tags.h"


namespace WNGJIA001 {
    void welcome() {
        // welcome message
        std::cout << "++++++++++ Welcome to XML Text Parser ++++++++++" << std::endl << std::endl;
    }
    void toContinue() {
        // to continue or to quit
        // displayed after performing an action or the welcome message
        std::cout << '\n' << "Please enter 'c' to continue or 'q' to quit." << std::endl;
    }
    void displayMenu() {
        // display options of the menu
        std::cout << "Please select an option from below by entering the corresponding letter:" << std::endl << std::endl;
        std::cout << "r: Read and parse an input file" << std::endl;
        std::cout << "p: Print all tags" << std::endl;
        std::cout << "d: Dump/write tags and data to an output file" << std::endl;
        std::cout << "l: List data for a specific tag" << std::endl;
        std::cout << "q: Quit" << std::endl;
    }
    void clearTerm(void) {
        // clear the terminal window
        system("clear");
    } 
}