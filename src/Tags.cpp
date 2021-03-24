/**
* Tag.cpp source file for Tag.h
* CSC3022F Assignment 1 2021
* Author: WNGJIA001
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include "Tags.h"

namespace WNGJIA001{
    std::vector<TagStruct> TagVector;

    void readTagsFrom(std::string fn){
        std::cout << "Opening file " << fn << " ..."<< std::endl;

        // open file
        std::ifstream inputFile(fn);
        if (!inputFile){
            std::cerr << "Invalid file name!" << std::endl;
        }

        std::string line;
        std::string content;
        while (std::getline(inputFile, line)) {
            // read all lines into string content
            content = content + line;
        }        

        std::string tag_name;
        std::string tag_text;
        std::stack<std::string> nameStack;
        std::stack<std::string> textStack;
        do {
            tag_name = getTagName(content);
            content = getContentAfterTag(content);
            tag_text = getTextAfterTag(content);
            nameStack.push(tag_name);
            textStack.push(tag_text);
            do {
                tag_name = getTagName(content);
                if (tag_name == ("/"+nameStack.top())) { 
                    std::cout << "*****" << tag_name << std::endl;
                    // if next tag is a closing tag for namestack.top()
                    std::string tag_n = nameStack.top();
                    std::string tag_t = textStack.top();
                    std::cout << "****" << tag_n << std::endl;
                    std::cout << "***" << tag_t << std::endl;
                    // remove the top elements from namestack and textstack and add the tag to vector
                    nameStack.pop();
                    textStack.pop();
                    addTag(tag_n, tag_t);
                    content = getContentAfterTag(content);
                    tag_text = getTextAfterTag(content);
                    if (!tag_text.empty()) {
                        tag_t = textStack.top() + tag_text;
                        textStack.pop();
                        textStack.push(tag_t);
                    }
                } else {
                    content = getContentAfterTag(content);
                    tag_text = getTextAfterTag(content);
                    nameStack.push(tag_name);
                    textStack.push(tag_text);
                }
            } while (!nameStack.empty());
        } while (!content.empty());

        // close file
        inputFile.close();
    }

    void printTags() {
        if (TagVector.empty()) {
            std::cout << "No tags to print, select \"r\" in menu to start reading tags from a text file!" << std::endl;
        }
        else {
            std::cout << TagVector.size() << std::endl;
            for(auto tagIt = TagVector.begin(); tagIt != TagVector.end(); tagIt++ ) {
                std::cout << "\"" << (*tagIt).name << "\"";
                std::cout << "," << (*tagIt).quantity << ",";
                std::cout << "\"" << (*tagIt).text << "\"" << std::endl;
            }
        }
    }

    void dumpTagsTo(std::string fn) {
        std::cout << "Dump" << std::endl;
    }

    void listTag(std::string tn) {
        std::cout << "List" << std::endl;
    }

    std::string getTagName(std::string s) {
        std::string tagName;
        int start = s.find("<") + 1;
        int end = s.find(">");
        tagName = s.substr(start, end - start);
        return tagName;
    }

    std::string getContentAfterTag(std::string c) {
        std::string newContent;
        int start = c.find(">") + 1;
        newContent = c.substr(start);
        return newContent;
    }

    std::string getTextAfterTag(std::string s) {
        std::string tagText;
        int nextTagStart = s.find("<");
        tagText = s.substr(0, nextTagStart);
        return tagText;
    }

    void addTag(std::string tn, std::string tt) {
        if (TagVector.empty()) {
            TagVector.push_back({tn, 1, tt});
        } else {
            for(auto tagIt = TagVector.begin(); tagIt != TagVector.end(); tagIt++ ) {
                if((*tagIt).name == tn) { // compare tagname
                    (*tagIt).quantity += 1;
                    (*tagIt).text += ":";
                    (*tagIt).text += tt;
                }
            }
        }
    }
}
