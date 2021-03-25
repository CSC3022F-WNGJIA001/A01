/**
* TagDriver.cpp: display text menu and host event loop
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tags.h"
#include "Menu.h"


int main(int argc, char* argv[])
{
    using namespace WNGJIA001;
    
    // scope variable declaration
    std::string option;
    std::string filename;
    std::string tagname;

    clearTerm();
    welcome(); 
    toContinue();
    for(;;) { //infinite loop
        std::cin >> option;
        clearTerm();
        if (option == "c") { // continue to menu
            displayMenu();
            std::cin >> option;
            clearTerm();
            if (option == "r") { // read and parse a specied input file
                std::cout << "Enter the name of the input file (including .txt): " << std::endl;
                std::cin >> filename;
                readTagsFrom(filename);
            } else if (option == "p") { // print all tags
                printTags();
            } else if (option == "d") { // dump/write tags and data to a file called tag.txt
                dumpTags();
            } else if (option == "l") { // list/print tag data for given tag
                std::cout << "Enter the name of the tag (case sensitive): " << std::endl;
                std::cin >> tagname;
                listTag(tagname);
            } else if (option == "q") { // quit
                exit(0);
            } else { // other inputs
                std::cout << "Not an option!" << std::endl;
            }
        } else if (option == "q") { // quit
                exit(0);
        } else { // other invalid option
                std::cout << "Invalid option!" << std::endl;  
        }
        toContinue();
    }
    return 0;
}