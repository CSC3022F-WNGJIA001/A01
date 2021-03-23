/**
* Tag.h header file
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#ifndef _TAGS
#define _TAGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace WNGJIA001 {
    // TagStruct to store information for each tag
    struct TagStruct {
        std::string tagName;
        int quantity;
        std::string text;
    };
    // Vector of TagStructs
    extern std::vector<TagStruct> TagVector();
    // Methods
    std::vector<TagStruct> readTagsFrom(char* filename);
    void printTags();
    void dumpTagsTo(char* filename);
    void listTag(TagStruct tag);
}

#endif