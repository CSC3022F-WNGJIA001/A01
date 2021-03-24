/**
* Tag.h header file
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#ifndef _TAGS
#define _TAGS

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

namespace WNGJIA001 {
    // TagStruct to store information for each tag
    struct TagStruct {
        std::string name;
        int quantity;
        std::string text;
    };
    // Vector of TagStructs
    extern std::vector<TagStruct> TagVector;
    // Methods
    void readTagsFrom(std::string fn);
    void printTags();
    void dumpTags();
    void listTag(std::string tn);
    std::string getTagName(std::string s);
    std::string getContentAfterTag(std::string c);
    std::string getTextAfterTag(std::string s);
    void addTag(std::string tn, std::string tt);
}

#endif