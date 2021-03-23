/**
* Menu.cpp to display text menu
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <string>
#include "Tags.h"


namespace WNGJIA001 {
    void welcome() {
        std::cout << "Welcome to XML Text Parser" << std::endl;
    }
    void displayMenu(){
        std::cout << "Please select " << std::endl;
        std::cout << "XML Text Parser" << std::endl;
    }
}