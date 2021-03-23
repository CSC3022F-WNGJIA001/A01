/**
* Tag.cpp source file for Tag.h
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tags.h"

namespace WNGJIA001{
    std::vector<TagStruct> TagVector();

    std::vector<TagStruct> readTagsFrom(char* filename){
        std::vector<TagStruct> result;

        ifstream inputFile(filename);
        if (!inputFile){
            std::cerr << "Invalid file name!" << endl;
        }
        while (!myfile.eof()) {
            myfile >> i >> ws;
            cout << "The next data item is :" <<
                i << endl;
        }
        inputFile.close();

        return result;
    }

    void printTags(){

    }

    void dumpTagsTo(char* filename){

    }

    void listTag(TagStruct tag){

    }
}
